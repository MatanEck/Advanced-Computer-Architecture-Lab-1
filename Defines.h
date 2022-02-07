#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#pragma warning(disable:4996)
// define sizes:
#define SRAM_SIZE 65536
#define INST_NAME_LEN 4
#define LINE_LEN 8 
#define NUM_OF_REG 8
#define REG_LEN 32

// define the opcodes:
#define ADD 0
#define SUB 1
#define LSF 2
#define RSF 3
#define AND 4
#define OR  5
#define XOR 6
#define LHI 7
#define LD 8
#define ST 9
#define JLT 16
#define JLE 17
#define JEQ 18
#define JNE 19
#define JIN 20
#define HLT 24

/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/


// ================================== Function declarations ================================== //

void copy_input_lines(void* input_to_cpy, char sram_out[][LINE_LEN]);
void handle_input(int* reg_ptr, FILE* trace_ptr, char sram_out[][LINE_LEN]);
int sign_ext(int imm);
int execute_command(unsigned int instruction_count, char inst[LINE_LEN], int opcode, int dst, int src0, int src1, int imm, int pc, int* reg_ptr, char sram_out[][LINE_LEN], FILE* trace_ptr, int Jmp_indicator);
void fill_sram(FILE* sram_ptr, char sram_out[SRAM_SIZE][LINE_LEN]);
void print_to_trace(int loadCommand, char* loadNegCommand, int instruction_count, char inst_name[INST_NAME_LEN], FILE* trace_ptr, char inst[LINE_LEN], int opcode, int dst, int src0, int src1, int imm, int pc, int* reg_ptr, char sram_out[][LINE_LEN], int Jmp_indicator);
