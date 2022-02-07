#include "Defines.h"
/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/
void print_to_trace(int loadCommand, char* loadNegCommand, int instruction_count, char inst_name[INST_NAME_LEN], FILE* trace_ptr, char inst[LINE_LEN], int opcode, int dst, int src0, int src1, int imm, int pc, int* reg_ptr, char sram_out[][LINE_LEN], int Jmp_indicator) {
	fprintf(trace_ptr, "--- instruction %d (%04x) @ PC %d (%04x) -----------------------------------------------------------\n", instruction_count, instruction_count, pc, pc);
	fprintf(trace_ptr, "pc = %04d, inst = %08x, opcode = %d (%s), dst = %d, src0 = %d, src1 = %d, immediate = %08x\n", pc, inst, opcode, inst_name, dst, src0, src1, imm);
	fprintf(trace_ptr, "r[0] = 00000000 r[1] = %08x r[2] = %08x r[3] = %08x \n", reg_ptr[1], reg_ptr[2], reg_ptr[3]);
	fprintf(trace_ptr, "r[4] = %08x r[5] = %08x r[6] = %08x r[7] = %08x \n", reg_ptr[4], reg_ptr[5], reg_ptr[6], reg_ptr[7]);
	fprintf(trace_ptr, "\n");
	if (opcode <= 7) // Notice is for add,sub,and,xor,or,lsf,rsf and lhi
		fprintf(trace_ptr, ">>>> EXEC: R[%d] = %d %s %d <<<<\n\n", dst, reg_ptr[src0], inst_name, reg_ptr[src1]);
	if (opcode == ST)
		fprintf(trace_ptr, ">>>> EXEC: MEM[%d] = R[%d] = %08x <<<<\n\n", reg_ptr[src1], src0, reg_ptr[src0]);
	if (opcode >= 16 && opcode < 20) { // Notice for jlt, jle, jeq, jne
		if (Jmp_indicator == 1) {
			fprintf(trace_ptr, ">>>> EXEC: %s %d, %d, %d <<<<\n\n", inst_name, reg_ptr[src0], reg_ptr[src1], imm);
		}
		else {
			fprintf(trace_ptr, ">>>> EXEC: %s %d, %d, %d <<<<\n\n", inst_name, reg_ptr[src0], reg_ptr[src1], pc + 1);
		}
	}
	if (opcode == JIN) {
		fprintf(trace_ptr, ">>>> EXEC: %s %d, %d, %d <<<<\n\n", inst_name, reg_ptr[src0], reg_ptr[src1], imm);
	}
	if (opcode == HLT)
		fprintf(trace_ptr, ">>>> EXEC: HALT at PC %04x<<<<\n\n", pc);
	if (opcode == LD) {
		if (tolower(loadNegCommand[0]) >= 'e')
			fprintf(trace_ptr, ">>>> EXEC: R[%d] = MEM[%d] = %s <<<<\n\n", dst, reg_ptr[src1], loadNegCommand);
		else
			fprintf(trace_ptr, ">>>> EXEC: R[%d] = MEM[%d] = %08x <<<<\n\n", dst, reg_ptr[src1], loadCommand);
	}
}