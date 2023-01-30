#include "Restitution_Exec.h"

void ExecPhase2(unsigned int MemInstru[],int MemReg[],maillon *MemVar,int Ninstru){
    int *PC = &MemReg[32];
    *PC = 0;
    int *IR = &MemReg[33];
    *IR = -1;
    int cavasauter=2;
    
    while (*PC<Ninstru&&*PC>-1){
        MemReg[0]=0;
        int Opcode = (MemInstru[*PC]>>26)&63;
        if ((Opcode==0)&&((MemInstru[*PC]&63)!=8)) {// Type R sauf JR ! 
            TypeR_Exec(MemInstru[*PC],MemReg);
            //Fonction d'execution du type R
        }else if (((Opcode==0)&&((MemInstru[*PC]&63)==8))||(Opcode>1&&Opcode<8)){//Instructions Branchement (╯°□°)╯︵ ┻━┻
            cavasauter=2;
            TypeBranchement_Exec(MemInstru[*PC],MemReg);
            if (*IR  != -1){
                cavasauter-=1;
            }
        }else if(Opcode==35||Opcode==43){//Instruction Memoire
            
            if (Opcode==43){ //Store Word
                CreateMaillon(MemVar,MemReg[(MemInstru[*PC]>>16)&63],((MemInstru[*PC]>>21)&63)+(MemInstru[*PC]&0xffff));
            } else {
                maillon *MemTest = MemVar;
                while (MemTest!=NULL&&MemTest->addr!=((MemInstru[*PC]>>21)&63)+(MemInstru[*PC]&0xffff)){
                    MemTest=MemTest->suivant;
                }
                if (MemTest->addr==((MemInstru[*PC]>>21)&63)+(MemInstru[*PC]&0xffff)){
                    MemReg[(MemInstru[*PC]>>16)&63]=MemTest->trame;
                }
            }
        }else { //Les autres ┬─┬ノ( º _ ºノ)
            TypeI_Exec(MemInstru[*PC],MemReg);
        }
        
        if (cavasauter==1){//L'instruction fut un jump effectif (on a perdu 1 sur la variable)
            cavasauter-=1; //Validation 
        } else if (cavasauter==0){ //DelaySlot
            *PC=*IR-1;
            *IR=-1;
            cavasauter=2;
        }else {
            cavasauter=2;
        }
        *PC=*PC+1;
               
    }
}


void ExecPhase1(char Entree_Hex[], char SORTIE_Execution[]){
    FILE*Hexa_In;
    Hexa_In = fopen (Entree_Hex, "r");
    FILE * OUT;
    OUT = fopen(SORTIE_Execution,"w");
    char c;
    unsigned int i;
    unsigned int tot=0;
    unsigned int pow16=268435456;
    //Init ListeChainee
    unsigned int n = 0;
    maillon *m1 = malloc(sizeof(maillon));
    m1->suivant = NULL;
    m1->trame=-1;
    m1->addr=0;

    while (feof(Hexa_In)!=1){
        for (i=0;i<8;i++){
            if (fscanf(Hexa_In,"%c", &c)!= 1) {continue;}
            tot+=HexaToInt(c)*pow16;
            pow16/=16;
        }
        CreateMaillon(m1,tot,0);
        n++;//Compteur
        if (fscanf(Hexa_In,"%c", &c)!= 1) {continue;}
        tot=0;pow16=268435456;
    }

    unsigned int MemInstru[n-1];
    m1 = m1->suivant;
    for (i=1;i<n;i++){MemInstru[i-1]=m1->trame;m1 = m1->suivant;}
    int MemReg[36]; //Registres de $0 à $31 + PC, LR, HI, LO
    MemReg[0]=0;
    int k;
    for (k=0;k<36;k++){MemReg[k]=0;}
    maillon *MemVar=malloc(sizeof(maillon));
    MemVar->suivant =NULL;
    fclose(Hexa_In);

    ExecPhase2(MemInstru,MemReg,MemVar,n-1);
    printf("Exécution Terminé\n");
    
    for (i=32;i>0;i--){//Ecriture des registres dans le fichier de sortie
        k=32-i;
        if (k<10){
            fprintf(OUT,"$0%d:%d\n",k,MemReg[k]);
        } else {
            fprintf(OUT,"$%d:%d\n",k,MemReg[k]);
        }
    }
    fprintf(OUT,"HI:%d\n",MemReg[34]);
    fprintf(OUT,"LO:%d\n",MemReg[35]);
    fclose(OUT);
}