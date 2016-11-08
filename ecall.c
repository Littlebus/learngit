#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/stat.h>
#include "riscv.h"

void ecall()
{
	int sys_num = i_reg[17];
	int arg_0 = i_reg[10];
	int arg_1 = i_reg[11];
	int arg_2 = i_reg[12];
	int arg_3 = i_reg[13];

	int file;
	void *io_buf;
	int nbytes;
	struct tms *tms_buf;
	struct stat *fstat_buf;


	if (sys_num == 63)		//read
	{
		file = arg_0;
		io_buf = (void *)mem+arg_1;
		nbytes = arg_2;
		i_reg[10] = read(file, io_buf, nbytes);
	}
	else if (sys_num == 64)		//write
	{
		file = arg_0;
		io_buf = (void *)(mem + arg_1);
		nbytes = arg_2;
		i_reg[10] = write(file, io_buf, nbytes);
	}
	else if (sys_num == 153)	//times
	{
		tms_buf = (struct tms *)(mem + arg_0);
		i_reg[10] = times(tms_buf);
	}
	else if (sys_num == 93)		//exit
		END = 1;
	else if (sys_num == 80)
	{
		file = arg_0;
		fstat_buf = (struct stat *)(mem + arg_1);
		i_reg[10] = fstat(file, fstat_buf);
	}
	else
	{
		printf("Undefined ecall %d\r\n", sys_num);
		exit(0);
	}
}
