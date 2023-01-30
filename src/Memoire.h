#include<stdio.h>
#include<stdlib.h>

typedef struct maillon maillon;
struct maillon{
	unsigned int trame;
	maillon *suivant;
    unsigned int addr; 
};

void CreateMaillon(maillon *m,unsigned int n,unsigned a);
void voirToutLesMaillons(maillon *m);