from symbols import Syms
from asm import ASMAnalyzer

syms = Syms()
syms.add_symbols("../../../symbols/gcc-syms-rewrite.txt")

asm = ASMAnalyzer(syms, "output.txt", 2)
asm.analyze_log("log.txt", "main")