from symbols import Syms, RAM_BASE

class ASMInstruction:
    def __init__(self, line: str, sym: Syms) -> None:
        self.failed_decoding = False
        try:
            self.return_address = int("0x" + line[0][:8], 0) + 8
        except Exception:
            self.failed_decoding = True
            return
        self.sym = sym
        self.instruction = line[2]
        self.destination = line[3]
        switch = {
            "jal"   : self.case_jal,
            "jalr"  : self.case_jalr,
            "jr"    : self.case_jr
        }
        self.symbol = None
        self.has_returned = False
        self.returning = False
        self.func_call = False
        if self.instruction in switch:
            switch[self.instruction]()
            self.func_call = True

    def case_jal(self):
        self.destination = int(self.destination[:10], 0)
        self.symbol = self.sym.get_symbol(self.destination)
        if self.symbol is None:
            name = str()
            if self.destination < RAM_BASE:
                name = "0" + hex(self.destination + RAM_BASE)[3:]
            else:
                name = hex(self.destination)[2:]
            self.symbol = "FUN_" + name

    def case_jalr(self):
        self.destination = int("0x" + self.destination[4:12], 0)
        self.symbol = self.sym.get_symbol(self.destination)
        if self.symbol is None:
            name = str()
            if self.destination < RAM_BASE:
                name = "0" + hex(self.destination + RAM_BASE)[3:]
            else:
                name = hex(self.destination)[2:]
            self.symbol = "FUN_" + name

    def case_jr(self):
        self.destination = int("0x" + self.destination[4:12], 0)
        self.returning = True

class ASMAnalyzer:
    def __init__(self, sym: Syms, output: str, space_size: int) -> None:
        self.sym = sym
        self.output = output
        self.space_size = space_size

    def analyze_log(self, log: str, start_label: str) -> None:
        output = open(self.output, "w")
        buffer = start_label + "()\n"
        curr_spacing = self.space_size
        possible_func_calls = []
        with open(log, "r") as file:
            for line in file:
                line = line.split()
                if len(line) < 4:
                    continue
                instruction = ASMInstruction(line, self.sym)
                if instruction.failed_decoding:
                    continue
                if instruction.returning:
                    for i in range(len(possible_func_calls) - 1, -1, -1):
                        func_call = possible_func_calls[i][0]
                        if (not func_call.has_returned) and (func_call.return_address == instruction.destination):
                            possible_func_calls[i][0].has_returned = True
                            curr_spacing = possible_func_calls[i][1]
                elif instruction.func_call:
                    possible_func_calls.append([instruction, curr_spacing])
                    curr_spacing += self.space_size

        for pfc in possible_func_calls:
            func_call = pfc[0]
            if func_call.has_returned:
                spacing = pfc[1]
                buffer += (" " * spacing) + func_call.symbol + "()\n"

        output.write(buffer)
        output.close()