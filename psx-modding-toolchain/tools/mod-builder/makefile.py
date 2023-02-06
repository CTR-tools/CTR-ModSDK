from compile_list import CompileList
from common import create_directory, request_user_input, rename_psyq_sections, delete_file, cli_clear, GCC_OUT_FILE, COMP_SOURCE, GAME_INCLUDE_PATH, FOLDER_DISTANCE, SRC_FOLDER, DEBUG_FOLDER, OUTPUT_FOLDER, BACKUP_FOLDER, OBJ_FOLDER, DEP_FOLDER, GCC_MAP_FILE, REDUX_MAP_FILE, CONFIG_PATH, PSYQ_RENAME_CONFIRM_FILE

import re
import json
import os
import shutil

class Makefile:
    def __init__(self, build_id: int, sym_file: list[str]) -> None:
        self.build_id = build_id
        self.sym_file = sym_file
        self.cl = list()
        self.load_config()

    def load_config(self) -> None:
        with open(CONFIG_PATH, "r") as file:
            data = json.load(file)["compiler"]
            self.use_function_sections = str(data["function_sections"] == 1).lower()
            self.disable_function_reorder = str(data["reorder_functions"] == 0).lower()
            optimization_level = data["optimization"]
            if optimization_level > 3:
                self.compiler_flags = "-Os"
            else:
                self.compiler_flags = "-O" + str(optimization_level)
            if data["debug"] != 0:
                self.compiler_flags += " -g"
            self.use_psyq_str = str(data["psyq"] != 0).lower()
            self.use_psyq = data["psyq"] != 0

    def add_cl(self, cl: CompileList) -> None:
        self.cl.append(cl)

    def set_base_address(self) -> bool:
        address = 0x807FFFFF
        for cl in self.cl:
            address = min(address, cl.address)
        self.base_addr = address
        return True

    def build_makefile_objects(self) -> None:
        self.srcs = str()
        self.ovr_section = str()
        self.ovrs = list()
        for cl in self.cl:
            for src in cl.source:
                self.srcs += src + " "
            self.ovrs.append((cl.section_name, cl.source, cl.address))
            self.ovr_section += "." + cl.section_name + " "

    def build_linker_script(self, filename="overlay.ld") -> str:
        offset_buffer = str()
        add_psyq = True
        buffer =  "__heap_base = __ovr_end;\n"
        buffer += "\n"
        buffer += "__ovr_start = " + hex(self.base_addr) + ";\n"
        buffer += "\n"
        buffer += "SECTIONS {\n"
        buffer += " " * 4 + "OVERLAY __ovr_start : SUBALIGN(4) {\n"
        for ovr in self.ovrs:
            section_name = ovr[0]
            source = ovr[1]
            addr = ovr[2]
            offset = addr - self.base_addr
            offset_buffer += section_name + " " + hex(offset) + "\n"
            buffer += " " * 8 + "." + section_name + " {\n"
            if addr > self.base_addr:
                buffer += " " * 12 + ". = . + " + hex(offset) + ";\n"
            text, rodata, sdata, data, sbss, bss, ctors, psyq = [], [], [], [], [], [], [], []
            sections = [text, rodata, sdata, data, sbss, bss, ctors, psyq]
            for src in source:
                full_source = src.rsplit(".", 1)
                src = full_source[0]
                is_c = False
                if len(full_source) == 2 and full_source[1] != "s":
                    is_c = True
                text.append(" " * 12 + "KEEP(" + src + ".o(.text*))\n")
                rodata.append(" " * 12 + "KEEP(" + src + ".o(.rodata*))\n")
                sdata.append(" " * 12 + "KEEP(" + src + ".o(.sdata*))\n")
                data.append(" " * 12 + "KEEP(" + src + ".o(.data*))\n")
                sbss.append(" " * 12 + "KEEP(" + src + ".o(.sbss*))\n")
                bss.append(" " * 12 + "KEEP(" + src + ".o(.bss*))\n")
                if add_psyq and self.use_psyq and is_c:
                    add_psyq = False
                    psyq.append(" " * 12 + "KEEP(*(.psyqtext*))\n")
                    psyq.append(" " * 12 + "KEEP(*(.psyqrdata*))\n")
                    psyq.append(" " * 12 + "KEEP(*(.psyqsdata*))\n")
                    psyq.append(" " * 12 + "KEEP(*(.psyqdata*))\n")
                    psyq.append(" " * 12 + "KEEP(*(.psyqsbss*))\n")
                    psyq.append(" " * 12 + "KEEP(*(.psyqbss*))\n")
            for section in sections:
                for line in section:
                    buffer += line
            buffer += " " * 12 + ". = ALIGN(4);\n"
            buffer += " " * 12 + "__ovr_end = .;\n"
            buffer += " " * 8 + "}" + "\n"
        buffer += " " * 4 + "}" + "\n"
        buffer += "}" + "\n"

        with open(filename, "w") as file:
            file.write(buffer)

        with open("offset.txt", "w") as file:
            file.write(offset_buffer)

        return filename

    def build_makefile(self) -> bool:
        if self.use_psyq and not os.path.isfile(PSYQ_RENAME_CONFIRM_FILE):
            print("\n[Makefile-py] WARNING: your project configuration may be trying to import PSYQ functions,")
            print("but you haven't renamed your psyq sections.")
            min_option = 1
            max_option = 2
            intro_msg = "Would you like to convert them now?\n1 - Yes\n2 - No"
            error_msg = "ERROR: Please select a number between " + str(min_option) + " and " + str(max_option)
            if request_user_input(min_option, max_option, intro_msg=intro_msg, error_msg=error_msg) == 1:
                rename_psyq_sections()
            else:
                intro_msg = "Would you like to abort the compilation?\n1 - Yes\n2 - No"
                if request_user_input(min_option, max_option, intro_msg=intro_msg, error_msg=error_msg) == 1:
                    return False

        self.set_base_address()
        self.build_makefile_objects()
        buffer =  "MODDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))\n"
        buffer += "TARGET = mod\n"
        buffer += "\n"
        buffer += "SRCS = " + self.srcs + "\n"
        buffer += "CPPFLAGS = -DBUILD=" + str(self.build_id) + "\n"
        buffer += "LDSYMS = "
        for sym in self.sym_file:
            buffer += "-T$(MODDIR)" + sym + " "
        buffer += "\n"
        buffer += "USE_FUNCTION_SECTIONS ?= " + self.use_function_sections + "\n"
        buffer += "DISABLE_FUNCTION_REORDER ?= " + self.disable_function_reorder + "\n"
        buffer += "USE_PSYQ ?= " + self.use_psyq_str + "\n"
        buffer += "OVERLAYSECTION ?= " + self.ovr_section + "\n"
        buffer += "OVR_START_ADDR = " + hex(self.base_addr) + "\n"
        buffer += "OVERLAYSCRIPT = " + self.build_linker_script() + "\n"
        buffer += "BUILDDIR = $(MODDIR)" + OUTPUT_FOLDER + "\n"
        buffer += "SRCINCLUDEDIR = $(MODDIR)" + SRC_FOLDER + "\n"
        buffer += "GAMEINCLUDEDIR = $(MODDIR)" + GAME_INCLUDE_PATH + "\n"
        buffer += "EXTRA_CC_FLAGS = " + self.compiler_flags + "\n"
        buffer += "\n"
        buffer += "include " + FOLDER_DISTANCE + "../common.mk\n"

        with open("Makefile", "w") as file:
            file.write(buffer)

        return True

    def delete_temp_files(self) -> None:
        for ovr in self.ovrs:
            for src in ovr[1]:
                src = src.rsplit(".", 1)[0]
                delete_file(src + ".o")
                delete_file(src + ".dep")

    # Moving the .o and .dep to debug/
    def move_temp_files(self) -> None:
        buffer = str()
        for ovr in self.ovrs:
            for src in ovr[1]:
                src = src.rsplit(".", 1)[0]
                obj_path = src + ".o"
                dep_path = src + ".dep"
                if os.path.isfile(obj_path) and os.path.isfile(dep_path):
                    obj_file = obj_path.rsplit("/", 1)[1]
                    dep_file = dep_path.rsplit("/", 1)[1]
                    obj_dst = OBJ_FOLDER + obj_file
                    dep_dst = DEP_FOLDER + dep_file
                    buffer += obj_dst + " " + obj_path + "\n"
                    buffer += dep_dst + " " + dep_path + "\n"
                    shutil.move(obj_path, obj_dst)
                    shutil.move(dep_path, dep_dst)
        with open(COMP_SOURCE, "w") as file:
            file.write(buffer)

    # Restoring the saved .o and .dep for faster compilation
    def restore_temp_files(self) -> None:
        if os.path.isfile(COMP_SOURCE):
            with open(COMP_SOURCE, "r") as file:
                for line in file:
                    line = [l.strip() for l in line.split()]
                    shutil.copyfile(line[0], line[1])

    def make(self) -> None:
        self.restore_temp_files()
        create_directory(OUTPUT_FOLDER)
        create_directory(BACKUP_FOLDER)
        cli_clear()
        print("\n[Makefile-py] Compilation started...\n")

        os.system("make -s -j8 > " + GCC_OUT_FILE + " 2>&1")
        with open(GCC_OUT_FILE) as file:
            for line in file:
                print(line)

        if (not os.path.isfile("mod.map")) or (not os.path.isfile("mod.elf")):
            self.delete_temp_files()
            print("\n[Makefile-py] ERROR: compilation was not successful.\n")
            return

        create_directory(DEBUG_FOLDER)
        create_directory(OBJ_FOLDER)
        create_directory(DEP_FOLDER)
        shutil.move("mod.map", DEBUG_FOLDER + "mod.map")
        shutil.move("mod.elf", DEBUG_FOLDER + "mod.elf")
        self.move_temp_files()

        print("\n[Makefile-py] Successful compilation.\n")
        pattern = re.compile(r"0x0000000080[0-7][0-9a-fA-F]{5}\s+([a-zA-Z]|_)\w*")
        special_symbols = ["__heap_base", "__ovr_start", "__ovr_end", "OVR_START_ADDR"]
        buffer = ""
        with open(GCC_MAP_FILE, "r") as file:
            for line in file:
                for match in re.finditer(pattern, line):
                    res = match.group().split()
                    if res[1] in special_symbols:
                        continue
                    buffer += res[0][10:] + " " + res[1] + "\n"

        with open(REDUX_MAP_FILE, "w") as file:
            file.write(buffer)