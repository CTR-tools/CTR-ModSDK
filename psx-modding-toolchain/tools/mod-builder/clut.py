cluts = []
num_clut = [0]

class CLUT:
    def __init__(self, name: str, x: int, y: int, mode: int) -> None:
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
        self.output_path = None

    def add_color(self, psx_color: int) -> None:
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

    def set_path(self, path: str) -> None:
        self.output_path = path

    def get_path(self) -> str:
        return self.output_path

    def as_c_struct(self) -> str:
        buffer = "short " + self.name + "[] = {"
        for color in self.colors:
            buffer += hex(color) + ","
        buffer += "};\n\n"
        buffer += "RECT " + self.name + "_pos = {\n"
        buffer += " " * 4 + ".x = " + str(self.x) + ",\n"
        buffer += " " * 4 + ".y = " + str(self.y) + ",\n"
        buffer += " " * 4 + ".w = " + str(self.w) + ",\n"
        buffer += " " * 4 + ".h = " + str(self.h) + "\n"
        buffer += "};\n"
        return buffer

    def __str__(self) -> str:
        buffer = ""
        if self.valid:
            buffer += "CLUT: " + self.name + "\n"
            buffer += "Coords: (" + str(self.x) + ", " + str(self.y) + ")\n"
            buffer += "Width, height: (" + str(self.w) + ", " + str(self.h) +")\n"
            buffer += "Address: " + hex(self.address) + "\n"
            buffer += '['
            for color in self.colors:
                buffer += hex(color) + ','
            buffer += ']\n'
        else:
            buffer += "ERROR: Too many colors for this CLUT.\n"
        return buffer


def clear_cluts() -> None:
    num_clut[0] = 0
    cluts.clear()

def dump_cluts(path: str) -> None:
    print("[CLUT-py] Dumping CLUTs...")
    for clut in cluts:
        if clut.is_valid():
            output = bytearray()
            clut_path = path + clut.name + ".bin"
            clut.set_path(clut_path)
            for color in clut.colors:
                output.append(color & 0xFF)
                output.append((color >> 8) & 0xFF)
            for _ in range(len(clut.colors), clut.max_colors):
                output.append(0)
                output.append(0)
            with open(clut_path, "wb") as file:
                file.write(output)

def get_clut_list() -> list[CLUT]:
    return cluts

def get_clut(x: int, y: int, mode: int) -> CLUT:
    if mode == 16:
        return None
    for clut in cluts:
        if clut.cmp_coords(x, y):
            return clut
    cluts.append(CLUT("clut_" + str(num_clut[0]), x, y, mode))
    num_clut[0] += 1
    return cluts[-1]

def rgb2psx(r: int, g: int, b: int, a: int) -> int:
        # No transparency case
        if a == 255:
            a = 0
            # PSX interprets opaque pitch black as fully transparent,
            # so we artificially set the color to RGBA(0, 0, 8, 255) in order
            # to draw as pitch black
            if r == 0 and g == 0 and b == 0:
                b = 8
        # Full transparency translates to RGBA(0, 0, 0, 255) in the PSX
        elif a == 0:
            r = 0
            g = 0
            b = 0
            a = 0
        # Last case, add transparency to the colors if a is in ]0, 255[
        else:
            a = 1
        color = a << 5
        color = color | (((b * 249) + 1014) >> 11) & 0x1F
        color = color << 5
        color = color | (((g * 249) + 1014) >> 11) & 0x1F
        color = color << 5
        color = color | (((r * 249) + 1014) >> 11) & 0x1F
        return color