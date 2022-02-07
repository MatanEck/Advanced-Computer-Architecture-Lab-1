#include "Defines.h"
/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/

int sign_ext(int imm) {
	imm <<= 16;
	imm >>= 16;
	return imm;
}

void handle_input(int* reg_ptr, FILE* trace_ptr, char sram_out[][LINE_LEN]) {
	unsigned int pc = 0, inst_count = 0;
	char inst[LINE_LEN+1];
	int tempPc = 0, Jmp_indicator = 0, curr_pc = 0, pc_ptr = 0;
	unsigned long curr_line = 0;
	int opcode = 0, dst = 0, src0 = 0, src1 = 0, imm = 0;
	int flag = 0;

	while ( !flag ) {
		memcpy(inst, sram_out[pc], LINE_LEN);
		inst[LINE_LEN] = "\0";
		curr_line = strtol(inst, NULL, 16);

		opcode = curr_line & 0x3E000000; //masking and shifting for opcode
		opcode = opcode >> 0x19;
		dst = curr_line & 0x01c00000;	// masking and shifting for dst
		dst = dst >> 0x16;
		src0 = curr_line & 0x00380000;	//masking and shifting for src0
		src0 = src0 >> 0x13;
		src1 = curr_line & 0x00070000;	// masking and shifting for src1
		src1 = src1 >> 0x10;
		imm = curr_line & 0x0000ffff; // masking and sign extension for immediate
		imm = sign_ext(imm);
		reg_ptr[1] = imm;


		pc = execute_command(inst_count, curr_line, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, trace_ptr, Jmp_indicator);
		inst_count++;
		if (opcode == HLT) {
			flag = 1; // exits the while loop
		}
		if (pc > SRAM_SIZE) {
			flag = 2; // exits the while loop
		}
	}
}