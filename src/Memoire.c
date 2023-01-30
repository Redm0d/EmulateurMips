#include"Memoire.h"

void CreateMaillon(maillon *m,unsigned int n,unsigned a){
    maillon *ms = m;
    while(ms->suivant!=NULL){ms = ms->suivant;}
    maillon *mr = malloc(sizeof(maillon));
    ms->suivant = mr;
    mr ->trame = n;
    mr->addr = a;
    mr->suivant=NULL;
}

void voirToutLesMaillons(maillon *m){
    while (m!=NULL){
        printf("%u,%u\n",m->trame,m->addr);
        m=m->suivant;
    }
}