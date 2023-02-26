from common import COMMENT_SYMBOL, CONFIG_PATH, OUTPUT_FOLDER, is_number
from syms import Syms

import json
import re
import os

sections = dict()
line_count = [0]
print_errors = [False]

def error_print(error: str):
    print(error)
    print_errors[0] = True

class CompileList:
    def __init__(self, line: str, sym: Syms) -> None:
        self.original_line = line
        self.sym = sym
        self.ignore = False
        self.is_bin = False
        self.pch = str()
        self.min_addr = 0x80000000
        self.max_addr = 0x807FFFFF if self.is_8mb() else 0x801FFFFF
        self.parse_line(line)
        line_count[0] += 1

    def is_8mb(self) -> bool:
        with open(CONFIG_PATH, "r") as file:
            data = json.load(file)["compiler"]
            return data["8mb"] == 1

    def parse_line(self, line: str) -> None:
        line = line.replace(COMMENT_SYMBOL, "," + COMMENT_SYMBOL + ",")
        line = [l.strip() for l in line.split(",") if l.strip() != ""]
        for i in range(len(line)):
            if line[i] == COMMENT_SYMBOL:
                if i == 0:
                    line = []
                else:
                    line = line[:i]
                break
        if len(line) < 5:
            if len(line) > 0:
                error_print("\n[BuildList-py] ERROR: wrong syntax at line " + str(line_count[0]) + ": " + self.original_line + "\n")
            self.ignore = True
            return

        version = line[0]
        if is_number(version):
            version = int(version, 0)
            if version != self.sym.get_build_id():
                self.ignore = True
                return
        else:
            if (version.lower() != "common") and (version != self.sym.get_version()):
                self.ignore = True
                return

        self.game_file = line[1]
        offset = 0
        try:
            offset = eval(line[3])
        except Exception:
            error_print("\n[BuildList-py] ERROR: invalid arithmetic expression for offset at line " + str(line_count[0]) + ": " + self.original_line + "\n")

        self.address = self.calculate_address_base(line[2], offset)
        srcs = [l.strip() for l in line[4].split()]
        self.source = list()
        folders = dict()
        for src in srcs:
            src = src.replace("\\", "/").rsplit("/", 1)
            directory = src[0] + "/"
            regex = re.compile(src[1].replace("*", "(.*)"))
            output_name = src[1].split(".")[0]
            if not directory in folders:
                for _, _, files in os.walk(directory):
                    folders[directory] = files
                    break
            if directory == OUTPUT_FOLDER and output_name in sections:
                self.source.append(directory + src[1])
            else:
                if directory in folders:
                    for file in folders[directory]:
                        if regex.search(file):
                            self.source.append(directory + file)
                else:
                    error_print("\n[BuildList-py] WARNING: directory " + directory + " not found.")
                    error_print("at line: " + str(line_count[0]) + ": " + self.original_line + "\n")
                    self.ignore = True
                    return

        if len(self.source) == 0:
            error_print("\n[BuildList-py] WARNING: no file(s) found.")
            error_print("at line: " + str(line_count[0]) + ": " + self.original_line + "\n")
            self.ignore = True
            return
        if len(line) == 6:
            self.section_name = line[5].split(".")[0]
        else:
            self.section_name = self.get_section_name_from_filepath(self.source[0])

        extension = self.source[0].rsplit(".", 1)[1]
        if not (extension.lower() in ["c", "s"]):
            self.is_bin = True
            self.ignore = True
            return

        if (self.address != 0) and ((self.address < self.min_addr) or (self.address > self.max_addr)):
            error_print("\n[BuildList-py] ERROR: address specified is not in the [" + hex(self.min_addr) + ", " + hex(self.max_addr) + "] range.")
            error_print("[BuildList-py] at line " + str(line_count[0]) + ": " + self.original_line + "\n")
            self.ignore = True
            return

        if self.section_name in sections:
            self.ignore = True
            error_print("\n[BuildList-py] ERROR: binary filename already in use, please define another alias.")
            error_print("[BuildList-py] at line " + str(line_count[0]) + ": " + self.original_line + "\n")
            return
        else:
            sections[self.section_name] = True

    def get_section_name_from_filepath(self, filepath: str) -> str:
        return filepath.replace("/", "").replace(".", "").replace("-", "_")

    def calculate_address_base(self, symbol: str, offset: int) -> int:
        addr = self.sym.get_address(symbol)
        if addr is not None:
            return addr + offset
        if is_number(symbol):
            return int(symbol, 0) + offset
        error_print("\n[BuildList-py] ERROR: invalid address or symbol at line " + str(line_count[0]) + ": " + self.original_line + "\n")
        return -1

    def should_ignore(self) -> bool:
        return self.ignore

    def should_build(self) -> bool:
        if self.ignore and not self.is_bin:
            return False
        return True

def free_sections() -> None:
    sections.clear()
    line_count[0] = 0
    print_errors[0] = False
