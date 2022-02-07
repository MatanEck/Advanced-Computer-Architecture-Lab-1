#include "Defines.h"
/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/
int execute_command(unsigned int instruction_count, char inst[LINE_LEN], int opcode, int dst, int src0, int src1, int imm, int pc, int* reg_ptr, char sram_out[][LINE_LEN], FILE* trace_ptr, int Jmp_indicator) {
	int shifted_imm = 0, mem_address = 0;
	char data_to_store[LINE_LEN+1], inst_name[INST_NAME_LEN];
	char loaded_line[LINE_LEN+1];
	unsigned int conv_num = 0;

	switch (opcode) {

	case ADD:
		strcpy(inst_name, "ADD");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = reg_ptr[src0] + reg_ptr[src1];
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;

	case SUB:
		strcpy(inst_name, "SUB");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = (reg_ptr[src0] - reg_ptr[src1]);
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;
	case LSF:
		strcpy(inst_name, "LSF");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = (reg_ptr[src0] << reg_ptr[src1]);
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;
	case RSF:
		strcpy(inst_name, "RSF");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = (reg_ptr[src0] >> reg_ptr[src1]);
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;
	case AND:
		strcpy(inst_name, "AND");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = (0, NULL, reg_ptr[src0] & reg_ptr[src1]);
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;
	case OR:
		strcpy(inst_name, "OR");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = (reg_ptr[src0] | reg_ptr[src1]);
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;
	case XOR:
		strcpy(inst_name, "XOR");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[dst] = (reg_ptr[src0] ^ reg_ptr[src1]);
		if (dst == 0)
			reg_ptr[dst] = 0;
		pc++;
		break;
	case LHI:
		strcpy(inst_name, "LHI");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		shifted_imm = imm << 16;
		reg_ptr[dst] = reg_ptr[dst] & 0x0000ffff;
		reg_ptr[dst] = reg_ptr[dst] | shifted_imm;
		pc++;
		break;
	case LD:
		strcpy(inst_name, "LD");
		memcpy(loaded_line, sram_out[reg_ptr[src1]],LINE_LEN);
		loaded_line[LINE_LEN] = "\0";
		Jmp_indicator = (int)strtol(loaded_line, NULL, 16);
		print_to_trace(Jmp_indicator, loaded_line, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		if (tolower(loaded_line[0]) >= 'e') {
			conv_num = strtol(loaded_line, NULL, 16);
			reg_ptr[dst] = conv_num;
		}
		else {
			reg_ptr[dst] = Jmp_indicator;
		}
		pc++;
		if (dst == 0) {
			reg_ptr[dst] = 0;
		}
		break;
	case ST:
		strcpy(inst_name, "ST");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		mem_address = reg_ptr[src1];
		sprintf(data_to_store, "%08x", reg_ptr[src0]);
		memcpy(sram_out[mem_address], data_to_store, LINE_LEN);
		pc++;
		break;
	case JLT:
		strcpy(inst_name, "JLT");
		if (reg_ptr[src0] < reg_ptr[src1]) {
			Jmp_indicator = 1; //set Jmp_indicator to 1 - have to jump
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
			reg_ptr[7] = pc;
			pc = imm;
		}
		else {
			Jmp_indicator = 0;
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc - 1, reg_ptr, sram_out, Jmp_indicator);
			pc++;
		}
		break;
	case JLE:
		strcpy(inst_name, "JLE");
		if (reg_ptr[src0] <= reg_ptr[src1]) {
			Jmp_indicator = 1; //set Jmp_indicator to 1 - have to jump
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
			reg_ptr[7] = pc;
			pc = imm;
		}
		else {
			Jmp_indicator = 0;
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc - 1, reg_ptr, sram_out, Jmp_indicator);
			pc++;
		}
		break;
	case JEQ:
		strcpy(inst_name, "JEQ");

		if (reg_ptr[src0] == reg_ptr[src1]) {
			Jmp_indicator = 1; //set Jmp_indicator to 1 - have to jump
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
			reg_ptr[7] = pc;
			pc = imm;
		}
		else {
			Jmp_indicator = 0;
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc - 1, reg_ptr, sram_out, Jmp_indicator);
			pc++;
		}
		break;
	case JNE:
		strcpy(inst_name, "JNE");
		if (reg_ptr[src0] != reg_ptr[src1]) {
			Jmp_indicator = 1; //set Jmp_indicator to 1 - have to jump
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
			reg_ptr[7] = pc;
			pc = imm;
		}
		else {
			Jmp_indicator = 0;
			print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc - 1, reg_ptr, sram_out, Jmp_indicator);
			pc++;
		}
		break;
	case JIN:
		strcpy(inst_name, "JIN");
		Jmp_indicator = 1; //set Jmp_indicator to 1 - have to jump
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		reg_ptr[7] = pc;
		pc = reg_ptr[src0];
		break;
	case HLT:
		strcpy(inst_name, "HLT");
		print_to_trace(0, NULL, instruction_count, inst_name, trace_ptr, inst, opcode, dst, src0, src1, imm, pc, reg_ptr, sram_out, Jmp_indicator);
		break;
	}
	return pc;
}