#include "header.h"

/*delet ent that not used*/
void hendle_ent(struct ic IC, struct label lab){
	int is_exist = 0;
	struct ic * Ic = &IC; 
	struct label * la= &lab;
	do
	{
		if (IC.label!=NULL)
				if(IC.p_word.e==1)
					if (strcmp(la->name, IC.label)==0){
						is_exist = 1;}	
		do
		{			
			Ic = Ic->next;
			if (Ic->label!=NULL)
				if(IC.p_word.e==1)
					if (strcmp(la->name, IC.label)==0){
						is_exist = 1;
						break;}		
		}while(Ic.next != NULL);
		if(is_exist ==0)
			printf("The label %s is written as entery but does not define.", la->name);
		la= la->next;
	}while (la != NULL);
}
/*if label is exist return the value, if not; return 0*/
int find_label(char * l,struct label lab){
	struct label * la = &lab;
	if ( la != NULL)
	{
		do{
			if (strcmp(l, la->name)==0)
				return la->value;
			la= la->next;
		}
		while(la !=NULL);
	}
	printf("The label %s does not define.", l);
	return 0;
}
/* scan the ic list and fill in the missing data from the label list. */
struct ret sacendpass(struct ret r)
{
	struct ic * iC =  &(r.IC);
	struct label lab = r.LABEL;
	struct leble * ext;
	struct label *tmp;
	int first_ext=0;
	hendle_ent(r.IC, r.ENT); 
	do
	{		
		if(&iC->label != NULL)
		{ 
			if(iC->p_word.e == 1)
			{
				ext = malloc(sizeof(struct label));
				if(ext == NULL){
					printf("Error alocate memory.\n");
					r.errors ++;
					iC = iC->next;
					break;
				}
				
				if(first_ext == 0){

					tmp = &r.EXT;
					first_ext =1;
				}
				else{
					tmp->next=(struct label *)ext;
					tmp=(struct label *)ext;
				}
				tmp->name=iC->label;
				tmp->value=iC->word_place;
			}
		if (iC->p_word.w==0){
			iC->p_word.w = find_label(iC->label, lab); 
			if (iC->p_word.w==0){r.errors++;}
			}
		}
		iC = iC->next;
	}
	while(iC != NULL );
	return r;
}

