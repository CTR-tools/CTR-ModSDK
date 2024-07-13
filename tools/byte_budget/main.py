import sys
import os
import re
import glob

def main():
    if len(sys.argv) != 3:
        return

    syms_filename = sys.argv[1]
    buff = str()
    with open(syms_filename, "r") as file:
        buff = file.read()
    matches = re.findall("[a-zA-Z_][a-zA-Z0-9_]*?[ ]+=[ ]+0x[0-9A-Fa-f]+", buff)

    symbols = []
    for match in matches:
        symbol, address = match.split("=")
        symbols.append((int(address.strip(), 16), symbol.strip()))
    symbols.sort(key=lambda x: x[0])

    byte_budget = dict()
    for i in range(len(symbols) - 1):
        byte_budget[symbols[i][1]] = symbols[i + 1][0] - symbols[i][0]

    object_files = glob.glob(sys.argv[2] + "*")
    end_file_len = len("c.bin")
    for object in object_files:
        file_size = os.path.getsize(object)
        object = (object[:len(object) - end_file_len]).replace("\\", "/").split("/")[-1]
        if object in byte_budget:
            if (file_size > byte_budget[object]):
                print("Function: " + object + " over budget by " + str(file_size - byte_budget[object]) + " bytes.")
    print("\nPress any key to exit.")
    input()

main()