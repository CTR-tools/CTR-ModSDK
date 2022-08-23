cluts = []
num_clut = [1]

class CLUT:

    def __init__(self, x: int, y: int, mode: int, name: str):
        self.name = name
        self.x = x * 16
        self.y = y
        self.address = (self.y * 2048) + (self.x * 2)
        self.colors = []
        self.color_count = 0
        self.mode = mode
        self.w = 2 ** mode
        self.h = 1
        self.max_colors = 2 ** mode
        self.color_offset = {}
        self.valid = True

    def add_color(self, psx_color: int):
        if self.color_count == self.max_colors:
            self.valid = False
            return
        self.color_offset[psx_color] = self.color_count
        self.colors.append(psx_color)
        self.color_count += 1

    def get_offset(self, color) -> int:
        alpha = 255
        if len(color) == 4:
            alpha = color[3]
        psx_color = rgb2psx(color[2], color[1], color[0], alpha)
        if psx_color in self.color_offset:
            return self.color_offset[psx_color]
        self.add_color(psx_color)
        if self.valid:
            return self.color_offset[psx_color]
        return -1

    def cmp_coords(self, x: int, y: int) -> bool:
        return (self.x == x * 16) and (self.y == y)

    def is_valid(self) -> bool:
        return self.valid

    def debug_print(self) -> str:
        buffer = ""
        if self.valid:
            buffer += "CLUT:\n\n"
            buffer += "Coords: (" + str(self.x) + ", " + str(self.y) + ")\n"
            buffer += "Width, height: (" + str(self.w) + ", " + str(self.h) +")\n"
            buffer += "Address: " + hex(self.address) + "\n"
            buffer += '['
            for color in self.colors:
                buffer += hex(color) + ','
            buffer += ']\n'
        else:
            buffer += "ERROR: Too many colors for this CLUT.\n"
        print(buffer)

    def __str__(self) -> str:
        buffer = ""
        if self.valid:
            buffer += "short " + self.name + "[" + str(self.max_colors) + '] __attribute__ ((section (".data"))) = {\n'
            for color in self.colors:
                buffer += hex(color) + ","
            for _ in range(len(self.colors), self.max_colors):
                buffer += "0x0,"
            buffer += "};\n\n"
            buffer += "RECT " + self.name + "_pos" + ' __attribute__ ((section (".data"))) = {\n'
            buffer += "	.x = " + str(self.x) + ",\n"
            buffer += "	.y = " + str(self.y) + ",\n"
            buffer += "	.w = " + str(self.w) + ",\n"
            buffer += "	.h = " + str(self.h) + "\n"
            buffer += "};\n"
        else:
            buffer += "ERROR: Too many colors for this CLUT.\n"
        return buffer


def get_clut(x: int, y: int, mode: int, label: str) -> CLUT:
    if mode == 16:
        return None
    for clut in cluts:
        if clut.cmp_coords(x, y):
            return clut
    cluts.append(CLUT(x, y, mode, label + '_clut'+str(num_clut[0])))
    num_clut[0] += 1
    return cluts[-1]

def get_cluts() -> list:
    return cluts

def print_cluts():
    for clut in cluts:
        print(clut)

def debug_print_cluts():
    for clut in cluts:
        clut.debug_print()

def rgb2psx(r: int, g: int, b: int, a: int) -> int:
        if a == 255:
            a = 0
        elif a == 0:
            r = 0
            g = 0
            b = 0
            a = 0
        else:
            a = 1
        color = a << 5
        color = color | (((b * 249) + 1014) >> 11) & 0x1F
        color = color << 5
        color = color | (((g * 249) + 1014) >> 11) & 0x1F
        color = color << 5
        color = color | (((r * 249) + 1014) >> 11) & 0x1F
        return color