from makefile import Makefile
from compile_list import CompileList, free_sections
from syms import Syms
from redux import Redux
from common import LOG_FILE, COMPILE_LIST, DEBUG_FOLDER, BACKUP_FOLDER, OUTPUT_FOLDER, COMPILATION_RESIDUES, TEXTURES_FOLDER, TEXTURES_OUTPUT_FOLDER, request_user_input, cli_clear, cli_pause, check_compile_list, check_prerequisite_files, create_directory, delete_directory, delete_file, rename_psyq_sections
from mkpsxiso import Mkpsxiso
from nops import Nops
from game_options import game_options
from image import create_images, clear_images, dump_images
from clut import clear_cluts, dump_cluts

import os
import logging

redux = Redux()
mkpsxiso = Mkpsxiso()
nops = Nops()
num_options = [0]

def get_options() -> int:
    intro_msg = (
        "Please select an action:\n\n"
        "Mod:\n\n"
        "1 - Compile\n"
        "2 - Clean\n\n"
        "Iso:\n\n"
        "3 - Extract Iso\n"
        "4 - Build Iso\n"
        "5 - Generate xdelta patch\n"
        "6 - Clean Build\n\n"
        "PCSX-Redux:\n\n"
        "7 - Hot Reload Mod\n"
        "8 - Restore Mod\n"
        "9 - Replace Textures\n"
        "10 - Restore Textures\n"
        "11 - Start Emulation\n\n"
        "NotPSXSerial:\n\n"
        "12 - Hot Reload\n"
        "13 - Restore\n\n"
        "Misc:\n\n"
        "14 - Disassemble Elf\n"
        "15 - Rename PSYQ Sections\n"
        "16 - Clean All\n"
    )
    error_msg = "ERROR: Wrong option. Please type a number from 1-" + str(num_options[0]) + ".\n"
    return request_user_input(first_option=1, last_option=num_options[0], intro_msg=intro_msg, error_msg=error_msg)

def compile() -> None:
    if not check_compile_list():
        print("\n[Compile-py] ERROR: " + COMPILE_LIST + " not found.\n")
        return
    game_syms = Syms()
    make = Makefile(game_syms.get_build_id(), game_syms.get_files())
    # parsing compile list
    with open(COMPILE_LIST, "r") as file:
        for line in file:
            cl = CompileList(line, game_syms)
            if not cl.should_ignore():
                make.add_cl(cl)
    if make.build_makefile():
        make.make()
    free_sections()

def clean() -> None:
    delete_directory(DEBUG_FOLDER)
    delete_directory(BACKUP_FOLDER)
    delete_directory(OUTPUT_FOLDER)
    delete_directory(TEXTURES_OUTPUT_FOLDER)
    for file in COMPILATION_RESIDUES:
        delete_file(file)

def clean_all() -> None:
    mkpsxiso.clean(all=True)
    clean()

def replace_textures() -> None:
    create_directory(TEXTURES_OUTPUT_FOLDER)
    img_count = create_images(TEXTURES_FOLDER)
    if img_count > 0:
        dump_images(TEXTURES_OUTPUT_FOLDER)
        dump_cluts(TEXTURES_OUTPUT_FOLDER)
        redux.replace_textures()
        clear_images()
        clear_cluts()
    else:
        print("\n[Image-py] WARNING: 0 images found. No textures were replaced.\n")

def disasm() -> None:
    os.system("mipsel-none-elf-objdump -d " + DEBUG_FOLDER + "mod.elf >> " + DEBUG_FOLDER + "disasm.txt")
    print("\nDisassembly saved at " + DEBUG_FOLDER + "disasm.txt\n")

def main():
    while not check_prerequisite_files():
        cli_pause()
    game_options.load_config()
    redux.load_config()
    nops.load_config()
    actions = {
        1   :   compile,
        2   :   clean,
        3   :   mkpsxiso.extract_iso,
        4   :   mkpsxiso.build,
        5   :   mkpsxiso.xdelta,
        6   :   mkpsxiso.clean,
        7   :   redux.hot_reload,
        8   :   redux.restore,
        9   :   replace_textures,
        10  :   redux.restore_textures,
        11  :   redux.start_emulation,
        12  :   nops.hot_reload,
        13  :   nops.restore,
        14  :   disasm,
        15  :   rename_psyq_sections,
        16  :   clean_all,
    }
    num_options[0] = len(actions)
    while True:
        cli_clear()
        i = get_options()
        actions[i]()
        cli_pause()

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        logging.basicConfig(filename=LOG_FILE, filemode="w", format='%(levelname)s:%(message)s')
        logging.exception(e)