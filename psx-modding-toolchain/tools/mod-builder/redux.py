from syms import Syms
from compile_list import CompileList, free_sections
from common import COMPILE_LIST, ISO_PATH, REDUX_MAP_FILE, SETTINGS_PATH, OUTPUT_FOLDER, BACKUP_FOLDER, TEXTURES_OUTPUT_FOLDER, MOD_NAME, request_user_input, get_build_id, check_compile_list, cli_pause
from image import get_image_list
from clut import get_clut_list
from game_options import game_options

import os
from subprocess import Popen, DETACHED_PROCESS

import json
import requests as r

REDUX_EXES = ["pcsx-redux", "pcsx-redux.exe", "PCSX-Redux.app"]

class Redux:
    def __init__(self) -> None:
        pass

    def load_config(self) -> bool:
        with open(SETTINGS_PATH) as file:
            data = json.load(file)["redux"]
            self.port = str(data["port"])
            self.url = "http://127.0.0.1:" + str(self.port)
            self.found_redux = False
            self.path = data["path"].replace("\\", "/")
            if self.path[-1] != "/":
                self.path += "/"
            if not os.path.isdir(self.path):
                print("\n[Redux-py] WARNING: Invalid redux directory: " + self.path)
                return False
            self.command = str()
            for exe in REDUX_EXES:
                cmd = self.path + exe
                if os.path.isfile(cmd):
                    self.command = cmd
                    self.found_redux = True
                    return True
            return False

    def get_game_name(self) -> str:
        names = game_options.get_version_names()
        intro_msg = "Select the game version:\n"
        for i in range(len(names)):
            intro_msg += str(i + 1) + " - " + names[i] + "\n"
        error_msg = "ERROR: Invalid version. Please select a number from 1-" + str(len(names)) +"."
        version = request_user_input(first_option=1, last_option=len(names), intro_msg=intro_msg, error_msg=error_msg)
        return game_options.get_gv_by_name(names[version - 1]).rom_name

    def start_emulation(self) -> None:
        if not self.found_redux:
            while not self.load_config():
                print("\n[Redux-py] Could not find a valid path to PCSX-Redux emulator.")
                print("Please check your settings.json and provide a valid path to redux.\n")
                cli_pause()
            print("\n[Redux-py] Found PCSX-Redux executable at " + self.command + "\n")
        curr_dir = os.getcwd() + "/"
        game_name = self.get_game_name()
        mod_name = game_name.split(".")[0] + "_" + MOD_NAME + ".bin"
        generic_path = curr_dir + ISO_PATH
        game_path = generic_path + mod_name
        if not os.path.isfile(game_path):
            # if modded game not found, fallback to original game
            game_path = generic_path + game_name
            if not os.path.isfile(game_path):
                print("\n[Redux-py] WARNING: game file not found at " + game_path)
                print("PCSX-Redux will start without booting the iso.")
        os.chdir(self.path)
        Popen(self.command + " -run -loadiso " + game_path, shell=True, start_new_session=True, close_fds=True, creationflags=DETACHED_PROCESS)
        os.chdir(curr_dir)
        self.load_map(warnings=False)

    def flush_cache(self) -> None:
        response = r.post(self.url + "/api/v1/cpu/cache?function=flush")
        if response.status_code == 200:
            print("Cache flushed.")
        else:
            print("\n[Redux - Web Server] error flushing cache.\n")

    def get_emulation_running_state(self) -> bool:
        response = r.get(self.url + "/api/v1/execution-flow")
        if response.status_code == 200:
            print("Retrieved emulation state.")
        else:
            print("\n[Redux - Web Server] error retrieving the emulation state.\n")
            return False
        return response.json()["running"]

    def pause_emulation(self) -> None:
        response = r.post(self.url + "/api/v1/execution-flow?function=pause")
        if response.status_code == 200:
            print("Paused the emulator.")
        else:
            print("\n[Redux - Web Server] error pausing the emulator.\n")

    def resume_emulation(self) -> None:
        response = r.post(self.url + "/api/v1/execution-flow?function=resume")
        if response.status_code == 200:
            print("Resumed the emulation.")
        else:
            print("\n[Redux - Web Server] error resuming the emulation.\n")

    def reset_map(self) -> None:
        response = r.post(self.url + "/api/v1/assembly/symbols?function=reset")
        if response.status_code == 200:
            print("Successfully reset redux map symbols.")
        else:
            print("\n[Redux - Web Server] error resetting the map file.\n")

    def load_map(self, warnings=True) -> None:
        self.reset_map()
        if not os.path.isfile(REDUX_MAP_FILE):
            if warnings:
                print("\n[Redux-py] ERROR: No map file found. Make sure you have compiled your mod before trying to hot reload.\n")
            return
        file = open(REDUX_MAP_FILE, "rb")
        files = {"file": file}
        response = r.post(self.url + "/api/v1/assembly/symbols?function=upload", files=files)
        if response.status_code == 200:
            print("Successfully loaded " + REDUX_MAP_FILE)
        else:
            print("\n[Redux - Web Server] error loading " + REDUX_MAP_FILE + "\n")

    def inject(self, backup: bool, restore: bool) -> None:
        build_id = get_build_id()
        if build_id is None:
            print("\n[Redux-py] ERROR: No output files found. Make sure that you have compiled your mod before trying to hot reload.\n")
            return
        sym = Syms(get_build_id())
        url = self.url + "/api/v1/cpu/ram/raw"
        psx_ram = bytearray()
        if backup:
            response = r.get(url)
            if response.status_code == 200:
                psx_ram = response.content
                print("Successfully retrieved a backup of the RAM.")
            else:
                print("\n[Redux - Web Server] error backing up the RAM.\n")
        build_lists = ["./"]
        while build_lists:
            prefix = build_lists.pop(0)
            bl = prefix + COMPILE_LIST
            free_sections()
            with open(bl, "r") as file:
                for line in file:
                    cl = CompileList(line, sym, prefix)
                    if cl.is_cl():
                        build_lists.append(cl.bl_path)
                    if not cl.should_build():
                        continue
                    bin = cl.get_output_name()
                    backup_bin = prefix + BACKUP_FOLDER + "redux_" + cl.section_name + ".bin"
                    offset = cl.address & 0xFFFFFFF
                    if not os.path.isfile(bin):
                        print("\n[Redux-py] ERROR: " + bin + " not found.\n")
                        continue
                    size = os.path.getsize(bin)
                    if backup:
                        section = psx_ram[offset : (offset + size)]
                        with open(backup_bin, "wb") as file:
                            file.write(section)
                    if restore:
                        bin = backup_bin
                        if not os.path.isfile(bin):
                            print("\n[Redux-py] ERROR: backup file " + bin + " not found.\n")
                            continue
                        size = os.path.getsize(bin)
                    file = open(bin, "rb")
                    files = {"file": file}
                    response = r.post(url + "?offset=" + str(offset) + "&size=" + str(size), files=files)
                    if response.status_code == 200:
                        if restore:
                            print(bin + " successfully restored.")
                        else:
                            print(bin + " successfully injected.")
                    else:
                        print("\n[Redux - Web Server] error injecting " + bin + "\n")
                    file.close()

    def inject_textures(self, backup: bool, restore: bool) -> None:
        url = self.url + "/api/v1/gpu/vram/raw"
        vram_path = TEXTURES_OUTPUT_FOLDER + "vram.bin"
        if backup:
            response = r.get(url)
            if response.status_code == 200:
                vram = response.content
                print("Successfully retrieved a backup of the VRAM.")
            else:
                print("\n[Redux - Web Server] Error backing up the VRAM.\n")
            with open(vram_path, "wb") as file:
                file.write(vram)
        if restore:
            if os.path.isfile(vram_path):
                vram_width = 1024
                vram_height = 512
                file = open(vram_path, "rb")
                files = {"file": file}
                response = r.post(url + "?x=" + str(0) + "&y=" + str(0) + "&width=" + str(vram_width) + "&height=" + str(vram_height), files=files)
                if response.status_code == 200:
                    print(vram_path + " successfully restored.")
                else:
                    print("\n[Redux - Web Server] Error restoring the VRAM.\n")
                file.close()
            else:
                print("\n[Redux - Web Server] ERROR: backup file " + vram_path + "not found.\n")
            return
        imgs = get_image_list()
        cluts = get_clut_list()
        data = [imgs, cluts]
        for textures in data:
            for img in textures:
                path = img.get_path()
                if path is not None:
                    file = open(path, "rb")
                    files = {"file": file}
                    response = r.post(url + "?x=" + str(img.x) + "&y=" + str(img.y) + "&width=" + str(img.w) + "&height=" + str(img.h), files=files)
                    if response.status_code == 200:
                        print(path + " successfully injected.")
                    else:
                        print("\n[Redux - Web Server] error injecting " + path + "\n")
                    file.close()

    def hot_reload(self) -> None:
        if not check_compile_list():
            print("\n[Redux-py] ERROR: " + COMPILE_LIST + " not found.\n")
            return
        is_running = bool()
        try:
            is_running = self.get_emulation_running_state()
        except Exception:
            print("\n[Redux - Web Server] ERROR: Couldn't start a connection with redux.")
            print("Make sure that redux is running, its web server is active, and")
            print("the port configuration saved in settings.json is correct.\n")
            return
        intro_msg = (
            "Would you like to backup the RAM?\n"
            "1 - Yes\n"
            "2 - No\n"
            "Note: this option is required if you want to uninstall the mod.\n"
            "By selecting yes you'll overwrite the current backup.\n"
        )
        error_msg = "ERROR: Invalid input. Please enter 1 for Yes or 2 for No."
        backup = request_user_input(first_option=1, last_option=2, intro_msg=intro_msg, error_msg=error_msg) == 1
        self.pause_emulation()
        self.inject(backup, False)
        self.load_map()
        self.flush_cache()
        if is_running:
            self.resume_emulation()

    def restore(self) -> None:
        if not check_compile_list():
            print("\n[Redux-py] ERROR: " + COMPILE_LIST + " not found.\n")
            return
        is_running = bool()
        try:
            is_running = self.get_emulation_running_state()
        except Exception:
            print("\n[Redux - Web Server] ERROR: Couldn't start a connection with redux.")
            print("Make sure that redux is running, its web server is active, and")
            print("the port configuration saved in settings.json is correct.\n")
            return
        self.pause_emulation()
        self.inject(False, True)
        self.flush_cache()
        if is_running:
            self.resume_emulation()

    def replace_textures(self) -> None:
        print("[Redux-py] Replacing textures...\n")
        is_running = bool()
        try:
            is_running = self.get_emulation_running_state()
        except Exception:
            print("\n[Redux - Web Server] ERROR: Couldn't start a connection with redux.")
            print("Make sure that redux is running, its web server is active, and")
            print("the port configuration saved in settings.json is correct.\n")
            return

        intro_msg = (
            "Would you like to backup the VRAM?\n"
            "1 - Yes\n"
            "2 - No\n"
            "Note: this option is required if you want to restore the original textures.\n"
            "By selecting yes you'll overwrite the current backup.\n"
        )
        error_msg = "ERROR: Invalid input. Please enter 1 for Yes or 2 for No."
        backup = request_user_input(first_option=1, last_option=2, intro_msg=intro_msg, error_msg=error_msg) == 1

        self.pause_emulation()
        self.inject_textures(backup, False)
        if is_running:
            self.resume_emulation()

    def restore_textures(self) -> None:
        print("\n[Redux-py] Restoring textures...\n")
        is_running = bool()
        try:
            is_running = self.get_emulation_running_state()
        except Exception:
            print("\n[Redux - Web Server] ERROR: Couldn't start a connection with redux.")
            print("Make sure that redux is running, its web server is active, and")
            print("the port configuration saved in settings.json is correct.\n")
            return
        self.pause_emulation()
        self.inject_textures(False, True)
        if is_running:
            self.resume_emulation()