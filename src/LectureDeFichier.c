#include "LectureDeFichier.h"

void Convertir (char instruction[],char s[]){
    
    char liste_instruction[26][10]={"AND","OR","XOR","ROTR","SLL","SRL","SLT","MFHI","MFLO","JR","ADD","DIV","MULT","SUB","ADDI","BEQ","BGTZ","BLEZ","BNE","LUI","LW","NOP","SW","SYSCALL","J","JAL"};//[0;13] TypeR,[14,23] Type I,[24,25] Type J
    long unsigned int i=0;
    char commande[10];
    
    /*charger la commande (type ADD, OR...) dans le string commande*/
    char arguments[32]; //ATTENTION PROBLEME DE DEPASSEMENT SI ON METS DES INSTRUCTIONS TROP GRANDES !
    while (instruction[i]!=' '){
        commande[i]=instruction[i];
        i++;
    }
    commande[i]='\0';

    i++;
    int j=i;

    /*charger les arguments de la commande (immédiates et registres) dans le string arguments*/
    while(i<strlen(instruction)) {
        arguments[i-j]=instruction[i];
        i++;
    }
    arguments[i-j]='\0';

    i=0;

    /*recherche du type de la commande :*/
    /*attribution d'une classe à la commande en fonction de l'indice de la commande dans le string liste_instruction */
    while (strcmp(commande,liste_instruction[i])!=0 && i<26){
        i++;
        }
    
    if (i<14) {TypeR(i,arguments,s);} 
    else if (i<24) {TypeI(i,arguments,s);}
    else if (i<26) {TypeJ(i,arguments,s);}
}


void Extraction (char programme[], char sortie_assemblage[]){

   /* fonction qui permet de lire le programme en assembleur ligne par ligne*/
    FILE*PROGRAMME;
    FILE*SORTIE_ASSEMBLAGE;
    PROGRAMME = fopen(programme, "r");
    SORTIE_ASSEMBLAGE = fopen (sortie_assemblage, "w");
    char s_in[32];
    s_in[0]='\0';
    char s_binary[]="00000000000000000000000000000000";
    char s_hexa[]="00000000";
    int i = 0;
    char c;
    int j;

    while (!feof(PROGRAMME)){
        if (fscanf(PROGRAMME,"%c", &c)!= 1) {continue;}

        /*permet d'ignorer les commentaires*/
        if (c == '#'){
            while (c != '\n' && c != '\0' && !feof(PROGRAMME)){
                if (fscanf(PROGRAMME,"%c", &c)!= 1) {continue;}
            }
        }

        /*permet de lire une ligne du fichier*/
        if (c!= '\n' && c!='\0' && c!='\r'){
                s_in[i] = c;
                s_in[i+1] = '\0'; /* permet d'écraser la ligne précédente pour lire la nouvelle ligne*/
                i++;

        }else if (c == '\n' && strcmp(s_in,"\0") != 0) {
                for (j=0;j<32;j++) {
                    s_binary[j]="0"[0];
                    }
                Convertir(s_in,s_binary);
                BinaryToHexa(s_binary,s_hexa);
                if (((strcmp(s_hexa,"00000000")==0) ^ (strncmp(s_in,"NOP",3)==0))==0){
                    fprintf(SORTIE_ASSEMBLAGE, "%s", s_hexa);
                    fprintf(SORTIE_ASSEMBLAGE, "\n");
                }
                i = 0;
                s_in[0]='\0';
        }
   }
   if (c != '\n'){
        for (j=0;j<32;j++) {s_binary[j]="0"[0];}
        Convertir(s_in,s_binary);
        BinaryToHexa(s_binary,s_hexa);
        if (((strcmp(s_hexa,"00000000")==0) ^ (strncmp(s_in,"NOP",3)==0))==0){
            fprintf(SORTIE_ASSEMBLAGE, "%s", s_hexa);
            fprintf(SORTIE_ASSEMBLAGE, "\n");
        }
    }
    fclose(PROGRAMME);
    fclose(SORTIE_ASSEMBLAGE);
}