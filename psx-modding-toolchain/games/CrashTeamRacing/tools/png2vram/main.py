import os
import sys

from image import create_image
from c_file import make_c_file

def main():
    directory = sys.argv[1]
    bpp = int(sys.argv[2])
    i = 1
    for root, _, files in os.walk(directory):
        for filename in files:
            path = root + "/" + filename
            img = create_image(path, "img"+str(i), directory, bpp)
            img.img2psx()
            i += 1
    make_c_file(directory)

main()