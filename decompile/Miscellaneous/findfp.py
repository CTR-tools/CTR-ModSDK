FRACTIONAL_BITS = 12
FP_ONE = 1 << FRACTIONAL_BITS

def fp(x: float) -> int:
    return int(x * FP_ONE)

def find_fp(constant: int) -> tuple[int, int]:
    i = 2
    while True:
        for j in range(1, i):
            if fp(j / i) == constant:
                return (j, i)
        i += 1

def main():
    print(find_fp(0xAAA))
    print(find_fp(0x9D8))

if __name__ == "__main__":
    main()
