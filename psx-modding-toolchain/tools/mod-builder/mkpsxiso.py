from common import ISO_PATH, MOD_NAME, OUTPUT_FOLDER, COMPILE_LIST, PLUGIN_PATH, TOOLS_PATH, request_user_input, create_directory, cli_pause, check_compile_list, delete_directory, delete_file
from game_options import game_options
from disc import Disc
from compile_list import CompileList, free_sections
from syms import Syms

import xml.etree.ElementTree as et
import shutil
import os
import importlib

MB = 1024 * 1024

def _copyfileobj_patched(fsrc, fdst, length=64*MB):
    """Patches shutil method to hugely improve copy speed"""
    while True:
        buf = fsrc.read(length)
        if not buf:
            break
        fdst.write(buf)

shutil.copyfileobj = _copyfileobj_patched

class Mkpsxiso:
    def __init__(self) -> None:
        path = os.path.abspath(PLUGIN_PATH + "plugin.py")
        spec = importlib.util.spec_from_file_location("plugin", path)
        self.plugin = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.plugin)
        self.python_path = os.getcwd().replace("\\", "/") + "/"

    def find_iso(self, gv) -> bool:
        if (not os.path.isfile(ISO_PATH + gv.rom_name)):
            print("ERROR:")
            print(ISO_PATH + gv.rom_name + " not found.")
            print("Please insert your " + gv.version + " game in the " + ISO_PATH + " directory,")
            print("and rename it to " + gv.rom_name)
            return False
        return True

    def ask_user_for_version(self):
        names = game_options.get_version_names()
        intro_msg = "Select the game version:\n"
        for i in range(len(names)):
            intro_msg += str(i + 1) + " - " + names[i] + "\n"
        error_msg = "ERROR: Invalid version. Please select a number from 1-" + str(len(names)) +"."
        version = request_user_input(first_option=1, last_option=len(names), intro_msg=intro_msg, error_msg=error_msg)
        return game_options.get_gv_by_name(names[version - 1])

    def extract(self, gv, extract_folder: str, xml: str) -> None:
        has_iso = self.find_iso(gv)
        while not has_iso:
            cli_pause()
            has_iso = self.find_iso(gv)
        rom_path = ISO_PATH + gv.rom_name
        create_directory(extract_folder)
        os.system("dumpsxiso -x " + extract_folder + " -s " + xml + " " + rom_path)
        self.plugin.extract(self.python_path + PLUGIN_PATH, self.python_path + extract_folder + "/")

    def abort_build_request(self) -> bool:
        intro_msg = (
            "Abort iso build?\n"
            "1 - Yes\n"
            "2 - No\n"
        )
        error_msg = "Invalid input. Please type a number from 1-2."
        return request_user_input(first_option=1, last_option=2, intro_msg=intro_msg, error_msg=error_msg) == 1

    def patch_iso(self, version: str, build_id: int, build_files_folder: str, modified_rom_name: str, xml: str) -> bool:
        disc = Disc(version)
        sym = Syms(build_id)
        modded_files = dict()
        iso_changed = False
        build_files_folder += "/"
        xml_tree = et.parse(xml)
        dir_tree = xml_tree.findall(".//directory_tree")[0]
        with open(COMPILE_LIST, "r") as file:
            for line in file:
                cl = CompileList(line, sym)
                if not cl.should_build():
                    continue

                # if it's a file to be replaced in the game
                df = disc.get_df(cl.game_file)
                if df is not None:
                    # Checking file start boundaries
                    if (cl.address - df.address) < 0:
                        error_msg = (
                            "\n[ISO-py] ERROR: Cannot overwrite " + df.physical_file + "\n"
                            "Base address " + hex(df.address) + " is bigger than the requested address " + hex(cl.address) + "\n"
                            "At line: " + cl.original_line + "\n\n"
                        )
                        print(error_msg)
                        if self.abort_build_request():
                            return False
                        continue

                    # checking whether the original file exists and retrieving its size
                    game_file = build_files_folder + df.physical_file
                    if not os.path.isfile(game_file):
                        print("\n[ISO-py] ERROR: " + game_file + " not found.\n")
                        if self.abort_build_request():
                            return False
                        continue
                    game_file_size = os.path.getsize(game_file)

                    # checking whether the modded file exists and retrieving its size
                    mod_file = str()
                    if cl.is_bin:
                        mod_file = cl.source[0]
                    else:
                        mod_file = OUTPUT_FOLDER + cl.section_name + ".bin"
                    if not os.path.isfile(mod_file):
                        print("\n[ISO-py] ERROR: " + mod_file + " not found.\n")
                        if self.abort_build_request():
                            return False
                        continue
                    mod_size = os.path.getsize(mod_file)

                    # Checking potential file size overflows and warning the user about them
                    offset = cl.address - df.address + df.offset
                    if (mod_size + offset) > game_file_size:
                        print("\n[ISO-py] WARNING: " + mod_file + " will change the total file size of " + game_file + "\n")

                    mod_data = bytearray()
                    with open(mod_file, "rb") as mod:
                        mod_data = bytearray(mod.read())
                    if game_file not in modded_files:
                        modified_game_file = build_files_folder + df.physical_file
                        modded_stream = open(modified_game_file, "r+b")
                        modded_files[game_file] = [modded_stream, bytearray(modded_stream.read())]
                        iso_changed = True

                    modded_stream = modded_files[game_file][0]
                    modded_buffer = modded_files[game_file][1]
                    modded_stream.seek(0)
                    # Add zeroes if the new total file size will be less than the original file size
                    for i in range(len(modded_buffer), offset + mod_size):
                        modded_buffer.append(0)
                    for i in range(mod_size):
                        modded_buffer[i + offset] = mod_data[i]
                    modded_stream.write(modded_buffer)

                # if it's not a file to be replaced in the game
                # assume it's a new file to be inserted in the disc
                else:
                    filename = (cl.section_name + ".bin").upper()
                    filename_len = len(filename)
                    if filename_len > 12:
                        filename = filename[(filename_len - 12):]
                    mod_file = OUTPUT_FOLDER + cl.section_name + ".bin"
                    dst = build_files_folder + filename
                    shutil.copyfile(mod_file, dst)
                    contents = {
                        "name": filename,
                        "source": modified_rom_name + "/" + filename,
                        "type": "data"
                    }
                    element = et.Element("file", contents)
                    dir_tree.insert(-1, element)
                    iso_changed = True

            for game_file in modded_files:
                modded_stream = modded_files[game_file][0]
                modded_stream.close()
            if iso_changed:
                xml_tree.write(xml)
            free_sections()

        return iso_changed

    def convert_xml(self, xml: str, new_xml: str, modified_rom_name: str) -> None:
        xml_tree = et.parse(xml)
        for element in xml_tree.iter():
            key = "source"
            if key in element.attrib:
                element_source = element.attrib[key].split("/")
                element_source[0] = modified_rom_name
                element_source = "/".join(element_source)
                element.attrib[key] = element_source
        xml_tree.write(new_xml)

    def build(self, only_extract=False) -> None:
        gv = self.ask_user_for_version()
        rom_name = gv.rom_name.split(".")[0]
        extract_folder = ISO_PATH + rom_name
        xml = extract_folder + ".xml"
        if only_extract:
            self.extract(gv, extract_folder, xml)
            return
        if not check_compile_list():
            print("\n[ISO-py] ERROR: " + COMPILE_LIST + " not found.\n")
            return
        if not os.path.isfile(xml):
            self.extract(gv, extract_folder, xml)
        modified_rom_name = rom_name + "_" + MOD_NAME
        build_files_folder = ISO_PATH + modified_rom_name
        new_xml = build_files_folder + ".xml"
        delete_directory(build_files_folder)
        print("Copying files...")
        shutil.copytree(extract_folder, build_files_folder)
        print("Converting XML...")
        self.convert_xml(xml, new_xml, modified_rom_name)
        build_bin = build_files_folder + ".bin"
        build_cue = build_files_folder + ".cue"
        print("Patching files...")
        if self.patch_iso(gv.version, gv.build_id, build_files_folder, modified_rom_name, new_xml):
            print("Building iso...")
            self.plugin.build(self.python_path + PLUGIN_PATH, self.python_path + build_files_folder + "/")
            os.system("mkpsxiso -y -q -o " + build_bin + " -c " + build_cue + " " + new_xml)
            print("Build completed.")
        else:
            print("\n[ISO-py] WARNING: No files changed. ISO building skipped.\n")

    def xdelta(self) -> None:
        gv = self.ask_user_for_version()
        original_game = ISO_PATH + gv.rom_name
        modded_game = ISO_PATH + gv.rom_name.split(".")[0] + "_" + MOD_NAME + ".bin"
        if not os.path.isfile(original_game):
            print("\n[ISO-py] ERROR: couldn't find " + original_game)
            print("Make sure to put your original game in the " + ISO_PATH + " folder.\n")
            return
        if not os.path.isfile(modded_game):
            print("\n[ISO-py] ERROR: couldn't find " + modded_game)
            print("Make sure that you compiled and built your mod before trying to generate a PPF patch.\n")
            return
        print("Generating xdelta patch...")
        command = os.getcwd().replace("\\", "/") + "/" + TOOLS_PATH + "xdelta/xdelta3.exe"
        if not os.path.isfile(command):
            print("\n[ISO-py] ERROR: xdelta not found. Make sure to download xdelta https://github.com/jmacd/xdelta-gpl/releases/tag/v3.0.11")
            print("rename it to xdelta3, then place it in tools/xdelta.\n")
        output = ISO_PATH + MOD_NAME + ".xdelta"
        delete_file(output)
        flags = " -S none -s " + original_game + " " + modded_game + " " + output
        os.system(command + flags)
        print(output + " generated!")

    def clean(self, all=False) -> None:
        for version in game_options.get_version_names():
            gv = game_options.get_gv_by_name(version)
            rom_name = gv.rom_name.split(".")[0]
            modified_rom_name = rom_name + "_" + MOD_NAME
            build_files_folder = ISO_PATH + modified_rom_name
            build_cue = build_files_folder + ".cue"
            build_bin = build_files_folder + ".bin"
            build_xml = build_files_folder + ".xml"
            if all:
                extract_folder = ISO_PATH + rom_name
                extract_xml = extract_folder + ".xml"
                delete_directory(extract_folder)
                delete_file(extract_xml)
            delete_directory(build_files_folder)
            delete_file(build_bin)
            delete_file(build_cue)
            delete_file(build_xml)

    def extract_iso(self) -> None:
        self.build(only_extract=True)