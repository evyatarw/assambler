#include "header.h"

/*	the program is a assembler.  It get assembly file-names and translates the files to binary words that the computer understands. */


int main(int argc, char *argv[])
{
	int i;
	if(argc < 2){
		printf("\n Next time, insert assembly commands file.\n");
		exit(0);
	}
	for(i=1; i<argc; i++)
	{
		hendel_pelet(first_pass(argv[i]), argv[i]);
	}
	return 0;
}
