from makefile import Makefile, clean_pch
from compile_list import CompileList, free_sections, print_errors
from syms import Syms
from redux import Redux
from common import MOD_NAME, GAME_NAME, LOG_FILE, COMPILE_LIST, DEBUG_FOLDER, BACKUP_FOLDER, OUTPUT_FOLDER, COMPILATION_RESIDUES, TEXTURES_FOLDER, TEXTURES_OUTPUT_FOLDER, RECURSIVE_COMP_PATH, ABORT_PATH, CONFIG_FILE, request_user_input, cli_clear, cli_pause, check_compile_list, check_prerequisite_files, create_directory, delete_directory, delete_file, rename_psyq_sections, get_distance_to_file
from mkpsxiso import Mkpsxiso
from nops import Nops
from game_options import game_options
from image import create_images, clear_images, dump_images
from clut import clear_cluts, dump_cluts
from c import export_as_c

import os
import sys
import logging

class Main:
    def __init__(self) -> None:
        self.redux = Redux()
        self.mkpsxiso = Mkpsxiso()
        self.nops = Nops()
        self.redux.load_config()
        self.nops.load_config()
        self.actions = {
            1   :   self.compile,
            2   :   self.clean,
            3   :   self.mkpsxiso.extract_iso,
            4   :   self.mkpsxiso.build,
            5   :   self.mkpsxiso.xdelta,
            6   :   self.mkpsxiso.clean,
            7   :   self.redux.hot_reload,
            8   :   self.redux.restore,
            9   :   self.replace_textures,
            10  :   self.redux.restore_textures,
            11  :   self.redux.start_emulation,
            12  :   self.nops.hot_reload,
            13  :   self.nops.restore,
            14  :   self.clean_pch,
            15  :   self.disasm,
            16  :   export_as_c,
            17  :   rename_psyq_sections,
            18  :   self.clean_all,
        }
        self.num_options = len(self.actions)
        self.window_title = GAME_NAME + " - " + MOD_NAME
        self.python = str()
        self.compilation_dep = list()
        self.update_title()

    def update_title(self):
        if sys.platform == "win32":
            os.system("title " + self.window_title)
            self.python = "python "
        else:
            os.system('echo -n -e "\\033]0;' + self.window_title + '\\007"')
            self.python = "python3 "

    def get_options(self) -> int:
        intro_msg = (
            "Please select an action:\n\n"
            "Mod:\n"
            "1 - Compile\n"
            "2 - Clean\n\n"
            "Iso:\n"
            "3 - Extract Iso\n"
            "4 - Build Iso\n"
            "5 - Generate xdelta patch\n"
            "6 - Clean Build\n\n"
            "PCSX-Redux:\n"
            "7 - Hot Reload Mod\n"
            "8 - Restore Mod\n"
            "9 - Replace Textures\n"
            "10 - Restore Textures\n"
            "11 - Start Emulation\n\n"
            "NotPSXSerial:\n"
            "12 - Hot Reload\n"
            "13 - Restore\n\n"
            "General:\n"
            "14 - Clean Precompiled Header\n"
            "15 - Disassemble Elf\n"
            "16 - Export textures as C file\n"
            "17 - Rename PSYQ Sections\n"
            "18 - Clean All\n"
        )
        error_msg = "ERROR: Wrong option. Please type a number from 1-" + str(self.num_options) + ".\n"
        return request_user_input(first_option=1, last_option=self.num_options, intro_msg=intro_msg, error_msg=error_msg)

    def compile(self) -> None:
        if not check_compile_list():
            print("\n[Compile-py] ERROR: " + COMPILE_LIST + " not found.\n")
            return
        root = False
        if not os.path.isfile(RECURSIVE_COMP_PATH):
            with open(RECURSIVE_COMP_PATH, "w") as _:
                root = True
        else:
            with open(RECURSIVE_COMP_PATH, "r") as file:
                # if the file was already compiled
                if MOD_NAME in file.readline().split():
                    return
        if os.path.isfile(ABORT_PATH):
            # Abort ongoing compilation chain due to an error that occured
            return
        game_syms = Syms()
        make = Makefile(game_syms.get_build_id(), game_syms.get_files())
        dependencies = []
        # parsing compile list
        free_sections()
        with open(COMPILE_LIST, "r") as file:
            for line in file:
                cl = CompileList(line, game_syms, "./")
                if cl.is_cl():
                    dependencies.append(cl.bl_path)
                if not cl.should_ignore():
                    make.add_cl(cl)
        if print_errors[0]:
            intro_msg = "[Compile-py] Would you like to continue to compilation process?\n\n1 - Yes\n2 - No\n"
            error_msg = "ERROR: Wrong option. Please type a number from 1-2.\n"
            if request_user_input(first_option=1, last_option=2, intro_msg=intro_msg, error_msg=error_msg) == 2:
                return
        if make.build_makefile():
            if make.make():
                with open(RECURSIVE_COMP_PATH, "a") as file:
                    file.write(MOD_NAME + " ")
            else:
                print("Aborting ongoing compilations. Press enter to continue.")
                input()
                with open(ABORT_PATH, "w") as _:
                    pass
        curr_dir = os.getcwd() + "/"
        if root:
            self.compilation_dep.clear()
        for dep in dependencies:
            if root:
                self.compilation_dep.append(dep)
            os.chdir(dep)
            command =  self.python + get_distance_to_file(False, CONFIG_FILE) + "../../tools/mod-builder/main.py 1 " + str(game_syms.version)
            os.system(command)
        os.chdir(curr_dir)
        if root:
            delete_file(RECURSIVE_COMP_PATH)
            delete_file(ABORT_PATH)
            self.update_title()

    def clean_files(self) -> None:
        delete_directory(DEBUG_FOLDER)
        delete_directory(BACKUP_FOLDER)
        delete_directory(OUTPUT_FOLDER)
        delete_directory(TEXTURES_OUTPUT_FOLDER)
        for file in COMPILATION_RESIDUES:
            delete_file(file)

    def clean(self) -> None:
        self.clean_files()
        curr_dir = os.getcwd() + "/"
        for dep in self.compilation_dep:
            os.chdir(dep)
            self.clean_files()
        os.chdir(curr_dir)

    def clean_pch(self) -> None:
        clean_pch()

    def clean_all(self) -> None:
        self.mkpsxiso.clean(all=True)
        self.clean()
        self.clean_pch()

    def replace_textures(self) -> None:
        create_directory(TEXTURES_OUTPUT_FOLDER)
        img_count = create_images(TEXTURES_FOLDER)
        if img_count == 0:
            print("\n[Image-py] WARNING: 0 images found. No textures were replaced.\n")
            return
        dump_images(TEXTURES_OUTPUT_FOLDER)
        dump_cluts(TEXTURES_OUTPUT_FOLDER)
        self.redux.replace_textures()
        clear_images()
        clear_cluts()

    def disasm(self) -> None:
        os.system("mipsel-none-elf-objdump -d " + DEBUG_FOLDER + "mod.elf >> " + DEBUG_FOLDER + "disasm.txt")
        print("\nDisassembly saved at " + DEBUG_FOLDER + "disasm.txt\n")

    def exec(self):
        while not check_prerequisite_files():
            cli_pause()
        game_options.load_config()
        while True:
            cli_clear()
            i = self.get_options()
            self.actions[i]()
            cli_pause()

if __name__ == "__main__":
    try:
        main = Main()
        main.exec()
    except Exception as e:
        delete_file(RECURSIVE_COMP_PATH)
        delete_file(ABORT_PATH)
        logging.basicConfig(filename=LOG_FILE, filemode="w", format='%(levelname)s:%(message)s')
        logging.exception(e)