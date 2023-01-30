#include "Conversion.h"

void BinaryToHexa (char s1[], char s2[]){
    
    char binary[16][5] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    char hexa[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    char liste_test[5]; /*sous liste de s1 composé de 4 bits qui se transformera en 1 bits en hexa*/
    int i=0; /*indice parcourant s1 et dénombrant les parquets de 4 bits*/
    int k=0; /*indice permettant de créer la sous liste de s1 (liste_test)*/
    int j=0;
    liste_test[4]='\0';
    int l=0;
    while (s1[i] != '\0'){
        

        j=0;
        /*créer une sous_liste de 4 bits*/
        for (l=i;l<i+4;l++){
                liste_test[j] = s1[l];
                j=j+1;
         }

        j=0;
        /*vérifie si la sous_liste de 4 bits est égal à un motif de binary*/
        while (strcmp(liste_test,binary[j]) != 0 && j<16){
                j = j+1;
        }          
        if (j==16){ printf("erreur : convertion binaire en hexa incorrecte , %s\n",liste_test);}
        /*si la sous liste est égale à un de ses motifs binaire, on attribue à s2 son équivalent en hexa*/
        else {
            s2[k]=hexa[j];
        }
        k=k+1;
        i=i+4;
    }
}

void IntToBin (int n,char out[]){
    //char Lbin[31][6] = {"00000","00001","00010","00011","00100","00101","00110","00111","01000","01001","01010","01011","01100","01101","01110","01111","10000","10001","10010","10011","10100","10101","10110","10111","11000","11001","11010","11011","11100","11101","11110","11111"}
    //if (n>31) {printf("Valeur d'operande invalide")}
    char Bininv[33]="00000000000000000000000000000000";
    int i = 0;
    int neg = 0;
    int outLen = strlen(out);
    //printf("Entree : %d\n",n);
    if (n<0) {
        neg=1;
        n=(-1)*n;
        n=fmod(n,(pow(2,outLen-1)));
        
    } else {
        n=fmod(n,(pow(2,outLen)));
    }
    while (n>0){
        Bininv[i] = n%2+'0';
        n = n/2;
        i++;
    }
    int j;
    int dec = outLen-i;
    for (j=0;j<i;j++){
        out[j+dec]=Bininv[i-j-1];
    }
    if (neg==1) {
        for (j=0;j<outLen;j++) {
            if (out[j]=='0') {
                out[j]='1';
            } else {
                out[j]='0';
            }
        }
        j=outLen-1;
        int retenue=1;
        while(j!=-1){
            if (out[j]=='0' && retenue==1){
                out[j] ='1';
                retenue =0;
            } else if (out[j] == '1' &&retenue==1){
                if (j>0) {
                    out[j]='0';
                } else {
                    retenue=0;
                }
            }
            j--;

        }
    }
    //printf("Sortie en binaire : %s\n",out);
}