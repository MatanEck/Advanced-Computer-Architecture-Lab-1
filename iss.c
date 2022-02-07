#include "Defines.h"
/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/
// ======================================= main - ISS ======================================= //  
int main(int argc, char** argv) {
	FILE *input_ptr, * sram_ptr, *trace_ptr ;
	int reg[NUM_OF_REG] = { 0 };
	int* reg_ptr = reg;
	char sram_out[SRAM_SIZE][LINE_LEN];

	if (argc != 2) {
		printf("Error: Incorrect input file number\n");
		exit(EXIT_FAILURE);
	}
	input_ptr = fopen(argv[1], "r");
	if (input_ptr == NULL) {
		printf("Error: Can't open input file for reading\n");
		exit(EXIT_FAILURE);
	}

	trace_ptr = fopen("trace.txt", "w");
	if (trace_ptr == NULL) {
		printf("Error: Can't open trace.txt file for writing\n");
		exit(EXIT_FAILURE);
	}

	sram_ptr = fopen("sram_out.txt", "w");
	if (sram_ptr == NULL) {
		printf("Error: Can't open sram_out.txt file for writing\n");
		exit(EXIT_FAILURE);
	}

	copy_input_lines(input_ptr, sram_out);

	handle_input(reg_ptr, trace_ptr, sram_out);
	
	fill_sram(sram_ptr, sram_out);

	fclose(input_ptr);
	fclose(trace_ptr);
	fclose(sram_ptr);
}
//=========================================================================================== //
