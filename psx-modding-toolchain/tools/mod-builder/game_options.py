from common import SYMS_PATH, CONFIG_PATH

import json

class GameVersion:
    def __init__(self, version: str, rom_name: str, syms_files: list[str], build_id: str):
        self.version = version
        self.rom_name = rom_name
        self.syms_files = syms_files
        self.build_id = build_id

class GameOptions:
    def __init__(self) -> None:
        self.versions_by_name = dict()
        self.versions_by_build_id = dict()

    def load_config(self):
        with open(CONFIG_PATH) as file:
            data = json.load(file)
            versions = data["versions"]
            for ver in versions:
                version = list(ver.keys())[0]
                ver_contents = ver[version]
                rom_name = ver_contents["name"]
                syms_files = ver_contents["symbols"]
                for i in range(len(syms_files)):
                    syms_files[i] = SYMS_PATH + syms_files[i]
                build_id = ver_contents["build_id"]
                gv = GameVersion(version, rom_name, syms_files, build_id)
                self.versions_by_name[version] = gv
                self.versions_by_build_id[build_id] = gv

    def get_version_names(self) -> list[str]:
        names = list()
        for version in self.versions_by_name.keys():
            names.append(version)
        return names

    def get_gv_by_name(self, name: str) -> GameVersion:
        if name in self.versions_by_name:
            return self.versions_by_name[name]
        return None

    def get_gv_by_build_id(self, build_id: int) -> GameVersion:
        if build_id in self.versions_by_build_id:
            return self.versions_by_build_id[build_id]
        return None

game_options = GameOptions()