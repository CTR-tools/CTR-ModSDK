import math
ONE = 4096

buffer = r"{"
for i in range(0x400):
    sin = int(math.sin(math.radians((i * 360)/ONE)) * ONE) & 0xFFFF
    cos = int(math.cos(math.radians((i * 360)/ONE)) * ONE) & 0xFFFF
    buffer += r" { .sin = " + str(sin) + r", .cos = " + str(cos) + r" }, "

buffer += r"};"
print(buffer)
