#include "header.h"

/* reverse:  reverse string s in place */   
 void reverse(char s[])
 {       
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--)
	{           
		c = s[i];
		s[i] = s[j];           
		s[j] = c;       
	}   
}

/* itoa:  convert n to characters in s */   
 void itoa(int n, char s[])   
 {       
 	int i, sign;
       if ((sign = n) < 0)  /* record sign */           
       n = -n;          /* make n positive */       
       i = 0;       
       do {      /* generate digits in reverse order */           
       	s[i++] = n % 10 + '0';  /* get next digit */       
       } while ((n /= 10) > 0);    /* delete it */       
       if (sign < 0)
                  s[i++] = '-'; 
      s[i] = '\0'; 
      reverse(s);   
} 

/*decimal int to dinary int*/
unsigned int int_to_int(unsigned int k) 
{
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_int(k / 2)));
}
/*return the binary int as string*/
char * itoa0 (unsigned int t, int l, char c[], char a[])
{
	int len;
	int i;
	int w = int_to_int(t);
	itoa(w, c);
	len=strlen(c);
	if (len< l)
	{
		for (i = l-len; i >0; i--)
		{
		
			strcat(a,"0");
		}
	strcat(a,c);	
	}
	return a;
}
/*make the full word to string*/
void print_p_word(struct plus_word word, char res[]){
	char a[10];
	char buffer[25];
	initialize_array(res, 25);
	initialize_array(buffer, 25);
	initialize_array(a, 10);
	strcat(res, itoa0(word.w, 21, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(word.a, A_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(word.r, R_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(word.e, E_LEN, buffer, a));
}
void print_word(struct word w, char res[]){
	char a[10];
	char buffer[25];
	initialize_array(res, 25);
	initialize_array(buffer, 25);
	initialize_array(a, 10);
	strcat(res, itoa0(w.opcode, OPCODE_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.dest, DEST_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.regDest, REG_DEST_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.source, SOURCE_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.regSource, REG_SOURCE_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.funct, FUNCT_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.a, A_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.r, R_LEN, buffer, a));
	initialize_array(a, 10);
	initialize_array(buffer, 25);
	strcat(res, itoa0(w.e, E_LEN, buffer, a));
}
void freeList_lab(struct label* head)
{
   struct label* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}
void freeList_dc(struct dc* head)
{
   struct dc* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}
void free_ic(struct ic *head){
	struct ic* tmp;
	while (head != NULL)
	{
	free(&(head->val));
	free(&(head->p_word));
	tmp = head;
	head = head->next;
	free(tmp);
	}
}
void free_ret(struct ret *a){
	free_ic(&(a->IC));
	freeList_dc(&(a->DC));
	freeList_lab(&(a->LABEL));
	freeList_lab(&(a->EXT));
	freeList_lab(&(a->ENT));
}
	
void obfile(char * pname, struct ret r){
	char progname [80];
	struct ic * IC= &r.IC;
	struct dc *DC = &r.DC;
	char val[25];
	FILE * fp;
	strcat(progname, pname);
	strcat(progname, ".ob");
	fp = fopen(progname, "w+");
	fprintf(fp, "     %d %d        \n", r.counter_ic, r.counter_dc);
	if (IC != NULL){ 
	do{ /*add ic to file*/
		if(&IC->val != NULL)
		{
			print_word(IC->val, val);
		}
		if(&IC->p_word != NULL)
		{
			print_p_word(IC->p_word, val);
		}
		else{return;}
		fprintf(fp,"%07d %06x\n", IC->word_place, atoi(val));
		IC = IC->next;
	}
	while(IC != NULL);
	}
	if (DC == NULL){/*add dc to file*/
		fclose(fp);
		return;
	}
	do{
		fprintf(fp,"%07d %06x\n", DC->mem_place, DC->val);
		DC = DC->next;
	}
	while(DC != NULL);
	fclose(fp);
}

void extfile(char * pname, struct ret r){
	char progname [80];
	FILE * fp;
	struct label * l= &r.EXT;
	strcat(progname, pname);
	strcat(progname, ".ext");
	if (l == NULL){return;}
	fp = fopen(progname, "w+");
	do{
		fprintf(fp,"%s %07d\n", l->name, l->value);
		l = l->next;
	}
	while(l != NULL);
	fclose(fp);
}

void entfile(char * pname, struct ret r){
	char progname [80];
	FILE * fp;
	struct label * l= &r.ENT;
	strcat(progname, pname);
	strcat(progname, ".ent");
	if (l == NULL){return;}	
	fp = fopen(progname, "w+");
	do{
		fprintf(fp,"%s %07d\n", l->name, l->value);
		l = l->next;
	}
	while(l != NULL);
	fclose(fp);
}



void hendel_pelet(struct ret r, char * prog)
{
	if (r.errors==0){
		obfile(prog, r);
		extfile(prog, r);
		entfile(prog, r);
	}
	
	free_ret(&r);
}
