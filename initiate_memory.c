#include "Defines.h"
/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/
void copy_input_lines(void* input_to_cpy, char sram_out[][LINE_LEN]) {
	//copying memory lines from a given text file, into sram_out
	const char* zeros = "00000000";
	int i = 0;
	char line[LINE_LEN+3];

	while (fgets(line, LINE_LEN+3, input_to_cpy) != NULL) {
		memcpy(sram_out[i], line, LINE_LEN);
		i++;
	}

	while (i < SRAM_SIZE) {  //still need to fill up the rest of the arrays with zeros
		memcpy(sram_out[i], zeros, LINE_LEN);
		i++;
	}

}