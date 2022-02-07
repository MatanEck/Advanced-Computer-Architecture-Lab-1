#include "Defines.h"
/***************************************************************

	Authors:
	Matan Eckhaus Moyal
	Bar Kachlon

****************************************************************/
void fill_sram(FILE* sram_ptr, char sram_out[SRAM_SIZE][LINE_LEN]) {
	//printing sram file lines into sram.txt
	int sram_line_index = 0;
	while (sram_line_index < SRAM_SIZE) {
		fwrite(sram_out[sram_line_index], LINE_LEN, 1, sram_ptr);
		putc('\n', sram_ptr);
		sram_line_index++;
	}
}
