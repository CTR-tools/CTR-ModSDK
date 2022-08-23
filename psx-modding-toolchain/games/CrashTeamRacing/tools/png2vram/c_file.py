from clut import get_cluts
from image import get_imgs

data_size = [0]
RECT_SIZE = 8
CHAR_SIZE = 1
SHORT_SIZE = 2

def declare_header() -> str:
    buffer = '#include <common.h>\n\n'
    buffer += "struct Texture\n"
    buffer += "{\n"
    buffer += " " * 4 + "const char * image;\n"
    buffer += " " * 4 + "const RECT * pos;\n"
    buffer += "};\n"
    return buffer + "\n"

def define_texture_struct(filename: str) -> str:
    buffer = "struct Texture " + filename + '_textures[] __attribute__ ((section (".sdata"))) = {\n'
    k = 0
    imgs = get_imgs()
    for img in imgs:
        buffer += " " * 4 + "[" + str(k) + "] =\n"
        buffer += " " * 4 + "{\n"
        buffer += " " * 8 + ".image = " + img.name + ",\n"
        buffer += " " * 8 + ".pos = &" + img.name + "_pos,\n"
        buffer += " " * 4 + "},\n\n"
        k += 1

    cluts = get_cluts()
    for clut in cluts:
        buffer += " " * 4 + "[" + str(k) + "] =\n"
        buffer += " " * 4 + "{\n"
        buffer += " " * 8 + ".image = (char *) " + clut.name + ",\n"
        buffer += " " * 8 + ".pos = &" + clut.name + "_pos,\n"
        buffer += " " * 4 + "},\n\n"
        k += 1

    buffer += "};\n"
    return buffer + "\n"

def define_images():
    buffer = ""
    imgs = get_imgs()
    for img in imgs:
        buffer += img.__str__() + "\n"
        data_size[0] += img.img_len * CHAR_SIZE + RECT_SIZE
    return buffer + "\n"

def define_cluts():
    buffer = ""
    cluts = get_cluts()
    for clut in cluts:
        buffer += clut.__str__() + "\n"
        data_size[0] += clut.max_colors * CHAR_SIZE + RECT_SIZE
    return buffer + "\n"

def make_c_file(filename) -> None:
    buffer = declare_header()
    buffer += define_images()
    buffer += define_cluts()
    buffer += define_texture_struct(filename)
    filename += ".c"
    with open(filename, "w") as file:
        file.write(buffer)