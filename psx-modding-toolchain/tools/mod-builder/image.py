from clut import get_clut, rgb2psx

import cv2

import os

imgs = []

class Image:
    def __init__(self, filename: str) -> None:
        path = filename
        filename = filename.split('/')[-1][:-4]
        filename = filename.split('_')
        self.name = filename[0]
        self.mode = int(filename[7])
        self.x = int(filename[1])
        self.y = int(filename[2])
        self.address = (self.y * 2048) + (self.x * 2)
        self.w = int(filename[5]) // (16 // self.mode)
        self.h = int(filename[6])
        self.clut = get_clut(int(filename[3]), int(filename[4]), self.mode)
        self.img = cv2.imread(path, cv2.IMREAD_UNCHANGED)
        self.psx_img = bytearray()
        self.img_len = 0
        self.output_path = None

    def img2psx(self) -> None:
        for row in self.img:
            if self.mode == 4:
                for i in range(0, len(row), 2):
                    px1 = self.clut.get_offset(row[i])
                    px2 = self.clut.get_offset(row[i + 1])
                    if px1 == -1 or px2 == -1:
                        return
                    px = (px2 << 4) | px1
                    self.psx_img.append(px)
            elif self.mode == 8:
                for px in row:
                    px = self.clut.get_offset(px)
                    if px == -1:
                        return
                    self.psx_img.append(px)
            elif self.mode == 16:
                for px in row:
                    px = rgb2psx(px[2], px[1], px[0], px[3])
                    self.psx_img.append(px & 0xFF)
                    self.psx_img.append((px >> 8) & 0xFF)

    def set_path(self, path: str) -> None:
        self.output_path = path

    def get_path(self) -> str:
        return self.output_path

    def show(self) -> None:
        cv2.imshow('image', self.img)
        cv2.waitKey(0)

    def __str__(self) -> str:
        buffer = ""
        if (self.clut is not None) and (self.clut.is_valid()):
            buffer += "IMG: " + self.name + "\n"
            buffer += "Coords: (" + str(self.x) + ", " + str(self.y) + ")\n"
            buffer += "Width, height: (" + str(self.w) + ", " + str(self.h) +")\n"
            buffer += "Address: " + hex(self.address) + "\n"
            buffer += '['
            for px in self.psx_img:
                buffer += hex(px) + ','
            buffer += ']\n'
        else:
            buffer += "ERROR: The images are adding too many colors to a single Image.\n"
        return buffer


def get_image_list() -> list[Image]:
    return imgs

def clear_images() -> None:
    imgs.clear()

def dump_images(path: str) -> None:
    print("\n[Image-py] Dumping images...")
    for img in imgs:
        if img.clut.is_valid():
            img_path = path + img.name + ".bin"
            img.set_path(img_path)
            with open(img_path, "wb") as file:
                file.write(img.psx_img)
        else:
            print("[Image-py] WARNING: Image " + img.name + " was ignored because it uses " + img.clut.name + ", which exceeds the number of maximum colors")

def create_images(directory: str) -> int:
    total = 0
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename[-4:].lower() == ".png":
                total += 1
                path = root + filename
                img = Image(path)
                imgs.append(img)
                img.img2psx()
    return total