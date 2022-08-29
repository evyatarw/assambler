#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>



#define MAX_LENGTH 81
#define MID_LENGTH 31
#define IC_START 100
#define NO_VAL -1


#define OPCODE 23
#define OPCODE_LEN 6

#define DEST 17
#define DEST_LEN 2

#define REG_DEST 15
#define REG_DEST_LEN 3

#define SOURCE 12
#define SOURCE_LEN 2

#define REG_SOURCE 10
#define REG_SOURCE_LEN 3

#define FUNCT 7
#define FUNCT_LEN 5

#define A 2
#define A_LEN 1

#define R 1
#define R_LEN 1

#define E 0
#define E_LEN 1

struct word /* main binary word */
{ 
	unsigned int e:E_LEN;
	unsigned int r:R_LEN;
	unsigned int a:A_LEN;
	unsigned int funct:FUNCT_LEN;
	unsigned int regSource:REG_SOURCE_LEN;
	unsigned int source:SOURCE_LEN;
	unsigned int regDest:REG_DEST_LEN;
	unsigned int dest:DEST_LEN;
	unsigned int opcode:OPCODE_LEN;
};
struct operation 
{
	char* name;
	int opcode;
	int funct;
};
struct plus_word /* extra binary word */
{
	unsigned int e:E_LEN;
	unsigned int r:R_LEN;
	unsigned int a:A_LEN;
	unsigned int w:21;
};
struct ic
{
	int word_place;
	struct word val;
	struct plus_word p_word;
	char *label;
	struct ic *next;
	struct ic *prev;
};
struct dc
{
	int mem_place;
	int val:24;  
	struct dc *next; 
};
struct label
{
	char *name;
	int value;
	int featur;
	struct label *next;
	struct label *prev;
};

struct ret /* the returned value of first_pass */
{
	struct ic IC;
	struct dc DC;
	struct label LABEL;
	struct label EXT;
	struct label ENT;
	int counter_dc;
	int counter_ic;
	int errors;
};

enum decision{_other, _command, _data, _string, _entery, _extern, _label};

struct ret first_pass (char*);
struct ret s_pass(struct ret);
void initialize_array (char*, int);
		/* initializing array.
		get array of char and its size */
int skip_space (char*, int);
		/* remove i (index) after the white characters.
		get string and index to start. returns the index after the movement */
int read_word (char*, char*, int*);
		/* seperate one word from givven string and recognize it's kind.
		get string to fill in the separated word into, string line to take a word from it and pointer of the index. returns enum presents the kind of the word, copy the word into the string and moves the index after the word. */
void initialize_b_word (struct ic*);
		/* initializing all of the bit fields of the struct. */
void error (char*, int, int*, char*);
		/* print error messege with it's place and increases the value of the error counter.
		get the input file name, line number, error pointer and descrition of the error. */
void is_comma_error (int, int*, int*,char*, int);
		/* cheks if there a match between the operands number and the commas number and increases the value of the error counter.
		get the operand counter, comma counter pointer, error pointer, input file name, line number. */
void check_operand_errors (char*, int, int*, int*, char*, int);
		/* cheks if there is errors could be wen the word is operand of operation, and increases the value of the error counter.
		get the operation name, operand counter, comma counter pointer, error pointer, input file name, line number. */
void check_label_errors (char*, int*, char*, int);
		/* cheks if there is errors could be wen the word is label, and increases the value of the error counter.
		get the label name, error pointer, input file name, line number. */
int is_label_exist (struct label, char*);
		/* cheks if the new label exist.
		get label list and new label name. */
struct label new_label (struct label*);
		/* create a new (initialized) label object (if the pointer is not initialized).
		get pointer of the lastest label at the list and returns the new label object. */
void next_ic(struct ic*);
		/* create a new (initialized) ic object (if the pointer is not the first at the list).
		get pointer of the lastest ic at the list and removes it to new label object. */
void copy_ic (struct ic*, struct ic*);
void copy_dc (struct dc*, struct dc*);
void copy_label (struct label*, struct label*);
struct operation recognize_operation(char*);
		/* recognize operation.
		get string and returns it's matched operation object, if the string is not name of operation returns junk operation object (contanes nothing) */
void operation_list();
