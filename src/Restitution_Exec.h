#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Conversion_Exec.h"
#include "Commandes.h"
#include"Memoire.h"

void ExecPhase2(unsigned int MemInstru[],int MemReg[],maillon *MemVar,int Ninstru);
void ExecPhase1(char Entree_Hex[], char SORTIE_Execution[]);