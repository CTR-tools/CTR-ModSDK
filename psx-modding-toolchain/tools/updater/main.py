import requests as r
import os
import shutil

temp_file = "repo.zip"
temp_folder = "repo/"
version_file = "tools/updater/.version"
repo = "mateusfavarin/psx-modding-toolchain"
branch = "main"
url = "https://api.github.com/repos/" + repo

def get_program_version() -> str:
    if os.path.isfile(version_file):
        with open(version_file, "r") as file:
            for line in file:
                return line
    return "0"

def update_program_version(version: str):
    with open(version_file, "w") as file:
        file.write(version)

def get_newest_version() -> str:
    commits = r.get(url + "/commits").json()
    return commits[0]["sha"]

def cli_pause() -> None:
    print("Press Enter to continue...")
    input()

def download_repo() -> bool:
    print("[Updater-py] Downloading update...")
    req = r.get(url + "/zipball/" + branch)
    if req.status_code == 200:
        with open(temp_file, "wb") as file:
            file.write(req.content)
        return True
    else:
        print(["[Updater-py] ERROR: Could not connect to " + url])
        return False

def move_files(folder: str, i: int) -> None:
    for root, _, files in os.walk(folder):
        for file in files:
            if file == ".gitignore":
                continue
            file_src = root + "/" + file
            file_dst = root[i:] + "/" + file
            folders = root[i:].replace("\\", "/").split("/")
            # Checking if the folder exists, so the file can be moved
            path = str()
            for folder in folders:
                path += folder + "/"
                if not os.path.exists(path):
                    os.mkdir(path)
            # Deleting old file
            if os.path.isfile(file_dst):
                os.remove(file_dst)
            # Replacing with new file
            shutil.move(file_src, file_dst)

def apply_patch() -> None:
    print("[Updater-py] Applying patch...")
    os.mkdir(temp_folder)
    shutil.unpack_archive(temp_file, temp_folder)
    content_folder = str()
    for root, dirs, _ in os.walk(temp_folder):
        content_folder = root + dirs[0]
        break
    i = len(content_folder) + 1
    move_files(content_folder + "/tools/", i)
    move_files(content_folder + "/docs/", i)
    shutil.rmtree(temp_folder)
    os.remove(temp_file)

def main() -> None:
    curr_version = get_program_version()
    new_version = get_newest_version()
    if curr_version == new_version:
        print("[Updater-py] Your toolchain is already up-to-date.")
        cli_pause()
        return
    if not download_repo():
        cli_pause()
        return
    apply_patch()
    update_program_version(new_version)
    cli_pause()

if __name__ == "__main__":
    main()