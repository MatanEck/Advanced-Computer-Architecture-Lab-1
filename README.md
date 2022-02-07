# Advanced-Computer-Architecture-Lab-1
Lab #1: ASIC hierarchical verification: high level simulator

When designing a new processor, we typically construct simulators of the new processor before designing the architecture details, and before coding it in RTL. This allows us to catch bugs early in the design process, as well as provide a reference for future lower level simulators, and RTL verification.
In this lab we'll model a simple processor by constructing a C high level ISS (instruction set simulator). We'll build the simulator, and test its functionality.
*****************************************
Building a High Level ISA simulator:
You will write a high level ISA simulator for the SP architecture named iss. It should accept a text file containing a memory dump of the SRAM, each line containing 8 hexadecimal digits, simulate the program till HALT is encountered, and generate an output memory image as well as trace file

Opcode specifies the instruction operations:
0: ADD: addition: R[dst] = R[src0] + R[src1]
1: SUB: subtraction: R[dst] = R[src0] - R[src1]
2: LSF: left shift: R[dst] = R[src0] << R[src1]
3: RSF: (signed) right shift: R[dst] = R[src0] >> R[src1]
4: AND: bitwise logical and: R[dst] = R[src0] & R[src1]
5: OR: bitwise logical or: R[dst] = R[src0] | R[src1]
6: XOR: bitwise logical xor: R[dst] = R[src0] ^ R[src1]
7: LHI: load the high bits [31:16] of the destination register with immediate[15:0]
8: LD: loads memory contents at address specified by R[src1]
9: ST: writes R[src0] to memory at address R[src1]
16: JLT: jump to immediate[15:0] if R[src0] < R[src1]
17: JLE: jump to immediate[15:0] if R[src0] <= R[src1]
18: JEQ: jump to immediate[15:0] if R[src0] == R[src1]
19: JNE: jump to immediate[15:0] if R[src0] != R[src1]
20: JIN: indirect jump to address R[src0]
24: HLT: halt execution
