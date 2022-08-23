from clut import get_clut, rgb2psx

import cv2

imgs = []

class Image:
    def __init__(self, path: str, name: str, label: str, mode: int):
        self.path = path.split('/')[1][:-4]
        self.path = self.path.split('_')
        self.name = label + "_" + name
        self.mode = mode
        self.x = int(self.path[0])
        self.y = int(self.path[1])
        self.address = (self.y * 2048) + (self.x * 2)
        self.w = int(self.path[4]) // (16 // self.mode)
        self.h = int(self.path[5])
        self.clut = get_clut(int(self.path[2]), int(self.path[3]), self.mode, label)
        self.img = cv2.imread(path, cv2.IMREAD_UNCHANGED)
        self.psx_img = []
        self.img_len = 0

    def img2psx(self):
        for row in self.img:
            if self.mode == 4:
                for i in range(0, len(row), 2):
                    px1 = self.clut.get_offset(row[i])
                    px2 = self.clut.get_offset(row[i + 1])
                    px = (px2 << 4) | px1
                    self.psx_img.append(px)
            elif self.mode == 8:
                for px in row:
                    px = self.clut.get_offset(px)
                    self.psx_img.append(px)
            elif self.mode == 16:
                for px in row:
                    px = rgb2psx(px[2], px[1], px[0], px[3])
                    self.psx_img.append(px & 0xFF)
                    self.psx_img.append((px >> 8) & 0xFF)
        self.img_len = len(self.psx_img)

    def debug_print(self):
        buffer = ""
        if self.clut.is_valid():
            buffer += "IMG:\n\n"
            buffer += "Coords: (" + str(self.x) + ", " + str(self.y) + ")\n"
            buffer += "Width, height: (" + str(self.w) + ", " + str(self.h) +")\n"
            buffer += "Address: " + hex(self.address) + "\n"
            buffer += '['
            for px in self.psx_img:
                buffer += hex(px) + ','
            buffer += ']\n'
        else:
            buffer += "ERROR: The images are adding too many colors to a single Image.\n"
        print(buffer)

    def show(self):
        cv2.imshow('image', self.img)
        cv2.waitKey(0)

    def __str__(self):
        buffer = ""
        if self.clut.is_valid():
            buffer += "char " + self.name + "[" + str(self.img_len) + '] __attribute__ ((section (".data"))) = {\n'
            for px in self.psx_img:
                buffer += hex(px) + ","
            buffer += "};\n\n"
            buffer += "RECT " + self.name + "_pos" + ' __attribute__ ((section (".data"))) = {\n'
            buffer += "	.x = " + str(self.x) + ",\n"
            buffer += "	.y = " + str(self.y) + ",\n"
            buffer += "	.w = " + str(self.w) + ",\n"
            buffer += "	.h = " + str(self.h) + "\n"
            buffer += "};\n"
        else:
            buffer += "ERROR: Too many colors for this Image.\n"
        return buffer

def create_image(path: str, name: str, label: str, mode: int) -> Image:
    img = Image(path, name, label, mode)
    imgs.append(img)
    return img

def get_imgs() -> list:
    return imgs