import copy
import os
import shutil
import sys

remaining_args = copy.deepcopy(sys.argv[1:])
using_cl_args = len(sys.argv) > 1

CONFIG_FILE = "config.json"

def cli_pause() -> None:
    if using_cl_args:
        if len(remaining_args) == 0:
            sys.exit(0)
    else:
        print("Press Enter to continue...")
        input()

def get_distance_to_config(print_error: bool) -> str:
    if print_error:
        print("No config.json found. Make sure to set this prerequisite file before continuing.")
        cli_pause()
    config = CONFIG_FILE
    distance = str()
    max_depth = 100
    k = 0
    failed = False
    while not os.path.isfile(config):
        distance += "../"
        config = distance + CONFIG_FILE
        k += 1
        if k == max_depth:
            failed = True
            break
    if not failed:
        return distance
    return get_distance_to_config(True)

LOG_FILE = "crash.log"
FOLDER_DISTANCE = get_distance_to_config(False)
ISO_PATH = FOLDER_DISTANCE + "build/"
SYMS_PATH = FOLDER_DISTANCE + "symbols/"
PLUGIN_PATH = FOLDER_DISTANCE + "plugins/"
GAME_INCLUDE_PATH = FOLDER_DISTANCE + "include/"
MAKEFILE = "Makefile"
COMPILE_LIST = "buildList.txt"
SRC_FOLDER = "src/"
OUTPUT_FOLDER = "output/"
BACKUP_FOLDER = "backup/"
DEBUG_FOLDER = "debug/"
OBJ_FOLDER = DEBUG_FOLDER + "obj/"
DEP_FOLDER = DEBUG_FOLDER + "dep/"
COMP_SOURCE = DEBUG_FOLDER + "source.txt"
TEXTURES_FOLDER = "newtex/"
TEXTURES_OUTPUT_FOLDER = TEXTURES_FOLDER + "output/"
GCC_MAP_FILE = DEBUG_FOLDER + "mod.map"
GCC_OUT_FILE = "gcc_out.txt"
COMPILATION_RESIDUES = ["overlay.ld", MAKEFILE, "offset.txt", "comport.txt", GCC_OUT_FILE]
REDUX_MAP_FILE = DEBUG_FOLDER + "redux.map"
CONFIG_PATH = FOLDER_DISTANCE + CONFIG_FILE
SETTINGS_PATH = FOLDER_DISTANCE + "../settings.json"
DISC_PATH = FOLDER_DISTANCE + "disc.json"
TOOLS_PATH = FOLDER_DISTANCE + "../../tools/"
PSYQ_CONVERTED_PATH = TOOLS_PATH + "gcc-psyq-converted/lib/"
PSYQ_RENAME_CONFIRM_FILE = PSYQ_CONVERTED_PATH + ".sections-renamed"
COMMENT_SYMBOL = "//"
MOD_NAME = os.getcwd().replace("\\", "/").split("/")[-1]
HEXDIGITS = ["A", "B", "C", "D", "E", "F"]

def rename_psyq_sections() -> None:
    sections = ["text", "data", "bss", "rdata", "sdata", "sbss", "note"]
    prefix = "mipsel-linux-gnu-" if sys.platform == "linux" or sys.platform == "linux2" else "mipsel-none-elf-"
    command = prefix + "objcopy"
    for section in sections:
        command += " --rename-section ." + section + "=.psyq" + section
    print("\n[Common-py] Renaming PSYQ sections...")
    curr_directory = ""
    for root, _, files in os.walk(PSYQ_CONVERTED_PATH):
        for filename in files:
            split_filename = filename.rsplit(".", 1)
            if len(split_filename) != 2:
                continue
            extension = split_filename[1]
            if extension == "a" or extension == "o":
                if root[-1] != "/":
                    root = root + "/"
                directory = root.split("/")[-2]
                if directory != curr_directory:
                    curr_directory = directory
                    print("[Common-py] Converting " + directory + "/ directory...")
                filepath = root + filename
                os.system(command + " " + filepath)
    with open(PSYQ_RENAME_CONFIRM_FILE, "w"):
        pass
    print("[Common-py] PSYQ sections renamed successfully.\n")

def check_file(filename: str) -> bool:
    if not os.path.isfile(filename):
        print("[Common-py] ERROR: no " + filename + " found.")
        return False
    return True

def check_prerequisite_files() -> bool:
    status = check_file(COMPILE_LIST)
    status = check_file(DISC_PATH) and status
    status = check_file(SETTINGS_PATH) and status
    if not status:
        print("[Common-py] Please set up these prerequisite files before continuing.")

    return status

def create_directory(dirname: str) -> None:
    if not os.path.isdir(dirname):
        os.mkdir(dirname)

def delete_directory(dirname: str) -> None:
    if os.path.isdir(dirname):
        try:
            shutil.rmtree(dirname)
        except Exception:
            print("\n[Common-py] ERROR: Cannot delete folder " + dirname)
            print("Please make sure that no external processes are accessing files in the folder.\n")

def delete_file(filename: str) -> None:
    if os.path.isfile(filename):
        try:
            os.remove(filename)
        except Exception:
            print("\n[Common-py] ERROR: Cannot delete file " + filename)
            print("Please make sure that no external processes are accessing this file.\n")

def request_user_input(first_option: int, last_option: int, intro_msg: str, error_msg: str) -> int:
    if using_cl_args and len(remaining_args) == 0:
        raise Exception("ERROR: Not enough arguments to complete command.")

    if not using_cl_args:
        print(intro_msg)

    raise_exception = False
    i = 0
    while True:
        try:
            i = int(input()) if not using_cl_args else int(remaining_args.pop(0))
            if (i < first_option) or (i > last_option):
                if using_cl_args:
                    raise_exception = True
                    break
                else:
                    print(error_msg)
            else:
                break
        except:
            if using_cl_args:
                raise_exception = True
                break
            else:
                print(error_msg)

    if raise_exception:
        raise Exception(error_msg)

    return i

def get_build_id() -> int:
    if not os.path.isfile("Makefile"):
        return None
    with open("Makefile", "r") as file:
        for line in file:
            line = line.split()
            if len(line) and line[0] == "CPPFLAGS":
                build_var = line[-1]
                build_id = int(build_var.split("=")[-1].strip())
                return build_id

def is_number(s: str) -> bool:
    is_hex = False
    if len(s) > 1 and s[0] == "-":
        s = s[1:]
    if len(s) > 2 and s[:2] == "0x":
        s = s[2:]
        is_hex = True
    for char in s:
        if not ((char.isdigit()) or (is_hex and char.upper() in HEXDIGITS)):
            return False
    return True

def cli_clear() -> None:
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")

def check_compile_list() -> bool:
    if os.path.isfile(COMPILE_LIST):
        return True
    return False