from common import request_user_input, is_number
from game_options import game_options

import os

class Syms():
    def __init__(self, build_id=None) -> None:
        self.version = int()
        self.gv = self.ask_user_for_version(build_id)
        self.syms = dict()
        for file in self.gv.syms_files:
            self.parse_gcc_file(file)

    def ask_user_for_version(self, build_id: int):
        if build_id is not None:
            return game_options.get_gv_by_build_id(build_id)
        names = game_options.get_version_names()
        intro_msg = "Select the game version:\n"
        for i in range(len(names)):
            intro_msg += str(i + 1) + " - " + names[i] + "\n"
        error_msg = "ERROR: Invalid version. Please select a number from 1-" + str(len(names)) +"."
        self.version = request_user_input(first_option=1, last_option=len(names), intro_msg=intro_msg, error_msg=error_msg)
        return game_options.get_gv_by_name(names[self.version - 1])

    def parse_gcc_file(self, filename: str) -> None:
        if not os.path.isfile(filename):
            print("\n[Syms-py] ERROR: " + filename + " not found.\n")
            return
        with open(filename, "r") as file:
            for line in file:
                if line.strip() == "":
                    continue
                original_line = line
                line = [l.strip() for l in line.split("=")]
                if len(line) != 2:
                    print("\n[Syms-py] ERROR: syntax error in file: " + filename)
                    print("[Syms-py] at line: " + original_line + "\n")
                    continue
                symbol = line[0]
                address = line[1].split(";")[0].strip()
                if not is_number(address):
                    print("\n[Syms-py] ERROR: invalid address in file: " + filename)
                    print("[Syms-py] at line: " + original_line + "\n")
                    continue
                address = int(address, 0)
                self.syms[symbol] = address

    def get_files(self) -> list[str]:
        if self.gv is None:
            return None
        return self.gv.syms_files

    def get_address(self, symbol: str) -> int:
        if symbol in self.syms:
            return self.syms[symbol]
        return None

    def get_version(self) -> str:
        if self.gv is None:
            return None
        return self.gv.version

    def get_build_id(self) -> int:
        if self.gv is None:
            return None
        return self.gv.build_id