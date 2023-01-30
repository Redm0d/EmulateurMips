#include "Types.h"

void TypeI(int n, char arg[],char s[]){ // "ADDI","BEQ","BGTZ","BLEZ","BNE","LUI","LW","NOP","SW", n allant de 14 à 22 inclus, 23 c'est syscall non utilisé ici
    
    //printf("%s\n",s);
    char LSpeFunc[9][7]={"001000","000100","000111","000110","000101","001111","100011","000000","101011"};
    int i=0;
    int j=0;
    int Narg=0;
    int Lr[]={0,0,0};
    char c[5];
    while (arg[i]!='\0'){
        
        if (arg[i]!=' ' && arg[i]!=',' && arg[i]!='$' ){
            
            while (arg[i]!=' ' && arg[i]!=',' && arg[i]!='$'&& arg[i]!='\0') {
                c[j]=arg[i];
                c[j+1]='\0';
                j++;
                i++;

            }
            Lr[Narg] = atoi(c);
            
            
            Narg++;
            j=0;
            c[0]='\0';
        } else {
            i++;
        }
    }
    
    for (j=0;j<6;j++){
        s[j]=LSpeFunc[n-14][j]; //Mets les 6 premiers bit pour dire quel fonction c'est 
    }
    /*
    printf("%d\n",Narg);
    for (j=0;j<3;j++){
        printf("%d,%d\n",Lr[j],j);
    }*/
    char rt[] = "00000";
    char imm[]= "0000000000000000";
    char rs[]="00000";
    //printf("%d\n",n);
    if (n==19) {//LUI
        IntToBin(Lr[0],rt);
        IntToBin(Lr[1],imm);
    }else if (n==20||n==22) {//SW et LW
        IntToBin(Lr[0],rt);
        IntToBin(Lr[2],rs);
        IntToBin(Lr[1],imm);
    }else if (n==14) {//ADDI qui a rs et rt en entree inversé ¯\_(ツ)_/¯
        IntToBin(Lr[0],rt);
        IntToBin(Lr[1],rs);
        IntToBin(Lr[2],imm);
    } else {
        if (Narg ==2) {
            IntToBin(Lr[0],rs);
            IntToBin(Lr[1],imm);
        } else {
            IntToBin(Lr[1],rt);
            IntToBin(Lr[0],rs);
            IntToBin(Lr[2],imm);
        }
    }

    for (i=6;i<32;i++){
        if (i<11) {
            if (n==19){
                s[i] = '0';
                }
            else{s[i] = rs[i-6];}
        } else if (i<16) {
                s[i] = rt[i-11];
        } else {
                s[i] = imm[i-16];
        }
    }
}

void TypeJ(int n, char arg[],char s[]){// J et Jar
    //printf("%s\n",s);
    char LSpeFunc[2][7]={"000010","000011"};
    int i=0;
    int j=0;
    int Narg=0;
    int Lr[]={0,0,0};
    char c[5];
    while (arg[i]!='\0'){
        
        if (arg[i]!=' ' && arg[i]!=',' && arg[i]!='$' ){
            
            while (arg[i]!=' ' && arg[i]!=',' && arg[i]!='$'&& arg[i]!='\0') {
                c[j]=arg[i];
                c[j+1]='\0';
                j++;
                i++;

            }
            Lr[Narg] = atoi(c);
            Narg++;
            j=0;
            c[0]='\0';
        } else {
            i++;
        }
    }
    for (j=0;j<6;j++){
        s[j]=LSpeFunc[n-24][j]; //Mets les 6 premiers bit pour dire quel fonction c'est 
    }
    /*printf("%d\n",Narg);
    for (j=0;j<3;j++){
        printf("%d,%d\n",Lr[j],j);
    }
    printf("%d\n",n);*/
    char index[]="00000000000000000000000000";
    IntToBin(Lr[0],index);
    for (i=6;i<32;i++){
        s[i] = index[i-6];
    }

}

void TypeR(int n, char arg[],char s[]){
    //printf("%s\n",s);
    //"ROTR","SLL","SRL", on des typyR differents
    //char liste_instructionR[14][10]={"AND","OR","XOR","ROTR","SLL","SRL","SLT","MFHI","MFLO","JR","ADD","DIV","MULT","SUB"};
    char LSpeFunc[14][7]={"100100","100101","100110","000010","000000","000010","101010","010000","010010","001000","100000","011010","011000","100010"};
    int i=0;
    int j=0;
    int Narg=0;
    int Lr[]={0,0,0};
    char c[5];

    while (arg[i]!='\0'){
        
        if (arg[i]!=' ' && arg[i]!=',' && arg[i]!='$' ){
            
            while (arg[i]!=' ' && arg[i]!=',' && arg[i]!='$'&& arg[i]!='\0') {
                c[j]=arg[i];
                c[j+1]='\0';
                j++;
                i++;

            }
            Lr[Narg] = atoi(c);
            Narg++;
            j=0;
            c[0]='\0';
        } else {
            i++;
        }
    }
    
    for (j=0;j<6;j++){
        s[26+j]=LSpeFunc[n][j]; //Mets les 6 derniers bit pour dire quel fonction c'est 
    }
    /*
    printf("%d\n",Narg);
    for (j=0;j<3;j++){
        printf("%d,%d\n",Lr[j],j);
    }
    printf("%d\n",n);*/
    //changement des bits des operandes en fonctions des cas
    if (n>2&&n<6){ // CAS "ROTR","SLL","SRL"
        char rd[] = "00000";
        char rt[] = "00000";
        char sa[] = "00000";
        IntToBin(Lr[0],rd);
        IntToBin(Lr[1],rt);
        IntToBin(Lr[2],sa);
        
        for (i=11;i<26;i++){
            if (i<16) {
                s[i]=rt[i-11];
            } else if (i<21) {
                s[i] = rd[i-16];
            } else {
                s[i] = sa[i-21];
               
            }
            
        }
        
        if (n==3) {s[10] = '1';}

    } else if (n==9){
        char rs[] = "00000";
        IntToBin(Lr[0],rs);
        for(i=6;i<11;i++){
            s[i]=rs[i-6];
        }
    } else { //CAS AUTRES
        
        char rd[] = "00000";
        char rt[] = "00000";
        char rs[] = "00000";
        if (Narg == 1){ //MFHI et MFHO
            IntToBin(Lr[0],rd);
            for(i=16;i<21;i++){
                s[i]=rd[i-16];
            }
        } else if (Narg==2) { //Div
            IntToBin(Lr[0],rs);
            IntToBin(Lr[1],rt);
            for (i=6;i<16;i++){
                if (i<11) {
                    s[i]=rs[i-6];
                } else {
                    s[i]=rt[i-11];
                } 
            }
        } else { // Cas autres 
            IntToBin(Lr[1],rs);
            IntToBin(Lr[2],rt);
            IntToBin(Lr[0],rd);
            for (i=6;i<21;i++){
                if (i<11) {
                    s[i]=rs[i-6];
                } else if (i<16) {
                    s[i] = rt[i-11];
                } else {
                    s[i] = rd[i-16];
                }
            }
        }
    }
}
