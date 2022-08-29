GCC = gcc -c -Wall -ansi -pedantic -std=c90        
assembler: main.c extra.o pelet.o first_pass.o sacendpass.o
	gcc -g -Wall -ansi -pedantic  main.c extra.o pelet.o first_pass.o sacendpass.o -o assembler

extra.o: extra.c header.h 
	$(GCC) extra.c -o extra.o

pelet.o: pelet.c  extra.c header.h 
	$(GCC) pelet.c -o pelet.o

first_pass.o: first_pass.c header.h extra.c 
	$(GCC) first_pass.c -o first_pass.o
        
sacendpass.o: sacendpass.c header.h 
	$(GCC) sacendpass.c -o sacendpass.o
