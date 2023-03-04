import json
import os
import shutil
import sys

TOOLS_FOLDER = "tools/"

def cli_pause() -> None:
    print("Startup script completed. Press Enter to exit.")
    input()

def get_distance_to_tools(print_error: bool) -> str:
    if print_error:
        print("ERROR: no tools/ folder found in the toolchain.")
        cli_pause()
        return
    folder = TOOLS_FOLDER
    distance = str()
    max_depth = 100
    k = 0
    failed = False
    while not os.path.isdir(folder):
        distance += "../"
        folder = distance + TOOLS_FOLDER
        k += 1
        if k == max_depth:
            failed = True
            break
    if not failed:
        return distance
    return get_distance_to_tools(True)

DISTANCE_FOLDER = get_distance_to_tools(False)
STARTUP_FILE = "startup_game.json"
STARTUP_PATH = DISTANCE_FOLDER + TOOLS_FOLDER + "startup/"
PLUGIN_FILE = "plugin.py"
PLUGIN_PATH = STARTUP_PATH + PLUGIN_FILE
BAT_FILE = "MOD.BAT"
STARTUP_MOD_BAT = "STARTUP_MOD.BAT"
BAT_PATH = STARTUP_PATH + BAT_FILE
STARTUP_MOD_BAT_PATH = STARTUP_PATH + STARTUP_MOD_BAT
SH_FILE = "MOD.SH"
STARTUP_MOD_SH = "STARTUP_MOD.SH"
SH_PATH = STARTUP_PATH + SH_FILE
STARTUP_MOD_SH_PATH = STARTUP_PATH + STARTUP_MOD_SH
BUILD_FOLDER = "build/"
PLUGIN_FOLDER = "plugins/"
SYMBOLS_FOLDER = "symbols/"
MOD_FOLDER = "mods/"
CONFIG_FILE = "config.json"
DISC_FILE = "disc.json"
FOLDERS = [BUILD_FOLDER, "include/", MOD_FOLDER, PLUGIN_FOLDER, SYMBOLS_FOLDER]

def create_directory(dirname: str) -> None:
    if not os.path.isdir(dirname):
        os.mkdir(dirname)

def copy_file(src: str, dst: str) -> None:
    if os.path.isfile(src) and not os.path.isfile(dst):
        shutil.copyfile(src, dst)

def make_mod(mod_folder: str) -> None:
    create_directory(mod_folder)
    create_directory(mod_folder + "src/")
    create_directory(mod_folder + "newtex/")
    if sys.platform == "win32":
        copy_file(BAT_PATH, mod_folder + BAT_FILE)
    else:
        copy_file(SH_PATH, mod_folder + SH_FILE)
    buffer = "// version, section, address, offset, path, binary name [optional]\n"
    with open(mod_folder + "buildList.txt", "w") as file:
        file.write(buffer)

class Version():
    def __init__(self, data, symbols, dst_path) -> None:
        self.name = list(data.keys())[0]
        self.symbols = []
        for symbol in symbols:
            symbol = self.rename_name(symbol)
            self.symbols.append(symbol)
        data = data[self.name]
        self.build_id = data["build_id"]
        self.game_path = data["game_path"].replace("\\", "/")
        self.game_name = self.game_path.rsplit("/")[-1]
        self.dst_path = dst_path

    def rename_name(self, s: str) -> str:
        s = s.split(".")
        if len(s) > 1:
            s = s[0] + "_" + self.name + "." + s[1]
        else:
            s = s[0] + "_" + self.name
        return s

    def copy_game(self) -> None:
        game_dst = self.dst_path + self.game_name
        print("Copying " + self.game_path + " to " + game_dst + "...")
        copy_file(self.game_path, game_dst)

    def extract_contents(self) -> str:
        game_dst = self.dst_path + self.game_name
        print("Extracting " + game_dst + "...")
        raw_name = self.game_name.split(".")[0]
        extract_folder = self.dst_path + raw_name + "/"
        xml = self.dst_path + raw_name + ".xml"
        os.system("dumpsxiso -x " + extract_folder + " -s " + xml + " " + game_dst)
        return extract_folder

    def contents_to_dict(self, extract_folder: str) -> None:
        if not os.path.isdir(extract_folder):
            print("WARNING: Could not extract the contents of the game.\n")
            print("Make sure that you have mkpsxiso/dumpsxiso installed to your PATH.")
            return

    def to_dict(self) -> dict:
        d = dict()
        inner_dict = dict()
        inner_dict["name"] = self.game_name
        inner_dict["symbols"] = self.symbols
        inner_dict["build_id"] = self.build_id
        d[self.name] = inner_dict
        return d


class StartupScript:
    def __init__(self) -> None:
        with open(STARTUP_FILE) as file:
            data = json.load(file)
            self.game_name = data["game_name"]
            symbols = data["symbols"]
            versions = data["versions"]
            self.versions = []
            for version in versions:
                self.versions.append(Version(version, symbols, self.game_name + "/" + BUILD_FOLDER))
            self.compiler = data["compiler"]

    def make_config_json(self) -> None:
        print("Creating default configuration...")
        d = dict()
        d["compiler"] = self.compiler
        vs = []
        for version in self.versions:
            vs.append(version.to_dict())
            for symbol in version.symbols:
                with open(self.game_name + "/" + SYMBOLS_FOLDER + symbol, "w") as _:
                    pass
        d["versions"] = vs
        with open(self.game_name + "/" + CONFIG_FILE, "w") as file:
            json.dump(d, file, indent=4)

    def get_executable_from_cnf(self, cnf: str):
        # SYSTEM.CNF expects to have 'BOOT = cdrom:\EXENAME;1' as a line
        with open(cnf, "r") as file:
            for line in file:
                to_match = "cdrom:\\"
                pattern = line.find(to_match)
                if pattern != -1:
                    end = line.find(";1")
                    if end != -1:
                        return line[(pattern + len(to_match)) : end]
                    else:
                        return line[pattern + len(to_match)]

    def make_disc_json(self) -> None:
        print("Creating default disc description...")
        d = dict()
        d["common"] = []
        for version in self.versions:
            version_files = []
            version.copy_game()
            exe = str()
            extract_folder = version.extract_contents()
            for root, _, files in os.walk(extract_folder):
                root = root.replace("\\", "/") + "/"
                for file in files:
                    if file == "SYSTEM.CNF":
                        exe = self.get_executable_from_cnf(root + file)
                    subfile_dict = dict()
                    subfile_dict["name"] = file
                    subfile_dict["address"] = "0x0"
                    subfile_dict["offset"] = "0x0"
                    file_dict = dict()
                    file_dict[file] = [subfile_dict]
                    version_files.append(file_dict)
            for file in version_files:
                if exe in file:
                    file[exe][0]["address"] = "0x80010000"
                    file[exe][0]["offset"] = "0x800"
            d[version.name] = version_files
        with open(self.game_name + "/" + DISC_FILE, "w") as file:
            json.dump(d, file, indent=4)

    def create_folders(self) -> None:
        print("Creating folders...")
        create_directory(self.game_name)
        for folder in FOLDERS:
            create_directory(self.game_name + "/" + folder)

    def copy_default_plugin(self) -> None:
        print("Copying default plugin...")
        copy_file(PLUGIN_PATH, self.game_name + "/" + PLUGIN_FOLDER + PLUGIN_FILE)

    def make_example_mod(self) -> None:
        print("Creating default mod example...")
        if sys.platform == "win32":
            copy_file(STARTUP_MOD_BAT_PATH, self.game_name + "/" + MOD_FOLDER + STARTUP_MOD_BAT)
        else:
            copy_file(STARTUP_MOD_SH_PATH, self.game_name + "/" + MOD_FOLDER + STARTUP_MOD_SH)
        mod_folder = self.game_name + "/" + MOD_FOLDER + "ModExample/"
        make_mod(mod_folder)

    def start(self):
        self.create_folders()
        self.make_config_json()
        self.make_disc_json()
        self.copy_default_plugin()
        self.make_example_mod()
        cli_pause()


def main():
    ss = StartupScript()
    ss.start()

def main_mod():
    print("Please type your mod name:")
    mod_name = input() + "/"
    make_mod(mod_name)

if __name__ == "__main__":
    if sys.argv[1] == '0':
        main()
    else:
        main_mod()