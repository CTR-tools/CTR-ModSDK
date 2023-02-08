import sys
import os

def trimbin(filename: str, target_path: str, offset_file: str) -> None:
    arr = bytearray()
    with open(filename, "rb") as file:
        arr = file.read()

    extension = filename.split(".")[1]
    with open(offset_file, "r") as file:
        for line in file:
            line = line.split()
            if line[0] == extension:
                arr = arr[int(line[1], 0):]
                break

    with open(filename, "wb") as file:
        file.write(arr)

    new_name = extension + ".bin"
    new_filename = target_path+new_name
    if os.path.isfile(new_filename):
        os.remove(new_filename)
    os.rename(filename, new_filename)

def main() -> None:
    trimbin(sys.argv[1], sys.argv[2], sys.argv[3])

main()