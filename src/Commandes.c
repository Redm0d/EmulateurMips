#include "Commandes.h"

void TypeR_Exec (unsigned trame, int MemoireCentrale []){
    int function = 0;
    function = trame & 63;
 
    int rs;
    rs = trame >> 21;
    rs = rs & 31;

    int rt;
    rt = trame >> 16;
    rt = rt & 31;

    int rd;
    rd = trame >> 11;
    rd = rd & 31;

    int sa;
    sa = trame >> 6;
    sa = sa & 31;

    switch(function)
    {   
        case 0 : //SLL(0)
            MemoireCentrale[rd] = MemoireCentrale[rt] << sa;
            break;

        case 2 : //ROTR(2) et SRL(2)
            if (rs == 1){//Rotate
                int puis2 = pow(2,sa);
                int decal = MemoireCentrale[rt]&puis2;
                MemoireCentrale[rd]=MemoireCentrale[rt]>>sa;
                MemoireCentrale[rd]+= decal<<(32-sa);
            }
            else {//Shift
                MemoireCentrale[rd] = MemoireCentrale[rt] >> sa;
            }
            break;

        case 16 : //MFHI(16)
            //Hight Register = 34 //Low Register= 35
            MemoireCentrale[rd] = MemoireCentrale[34];
            break;

        case 18 : //MFLO(18)
            //Hight Register = 34 //Low Register= 35
            MemoireCentrale[rd] = MemoireCentrale[35];
            break;

        case 24 : ; //MULT(24)
            //Hight Register = 34 //Low Register= 35
            long int res;
            res = MemoireCentrale[rs]*MemoireCentrale[rt];
            long int a = 0xffffffff;
            MemoireCentrale[35] = res & a;
            res = res >> 32;
            MemoireCentrale[34] = res & a;
            break;
            
        case 26 : //DIV (26) 
            //Hight Register = 34 //Low Register= 35
            if (MemoireCentrale[rt]!=0){
                MemoireCentrale[34] = MemoireCentrale[rs] % MemoireCentrale[rt];
                MemoireCentrale[35] = (MemoireCentrale[rs]-MemoireCentrale[35])/MemoireCentrale[rt];
            } else {
                printf("Division par Zero détectée");
            }
            break;

        case 32 : //ADD(32)
            MemoireCentrale[rd] = MemoireCentrale[rs] + MemoireCentrale[rt];
            break;

        case 34 : //SUB(34)
            MemoireCentrale[rd] = MemoireCentrale[rs] - MemoireCentrale[rt];
            break;

        case 36 : //AND(36)
            MemoireCentrale[rd] = MemoireCentrale[rs] & MemoireCentrale[rt];
            break;
            
       case 37 : //OR(37)
            MemoireCentrale[rd] = MemoireCentrale[rs] | MemoireCentrale[rt];
            break;
            
        case 38 : //XOR(38)
            MemoireCentrale[rd] = MemoireCentrale[rs] ^ MemoireCentrale[rt];
            break;
            
        case 42 : //SLT(42)
            if (MemoireCentrale[rs]<MemoireCentrale[rt]){
               MemoireCentrale[rd] = 1;
            }
            else {MemoireCentrale[rd] = 0;
            }
            break;
    }
}

void TypeI_Exec (unsigned trame,int MemoireCentrale[]){
    int immediate;
    immediate = trame & 0x7fff;
    
    int parite =trame&0x8000 ;
    if (parite==0x8000){
        immediate = immediate -0x8000;
    }
    
    int opcode;
    opcode = trame >> 26;
    opcode = opcode & 63;

    int rs;
    rs = trame >> 21;
    rs = rs & 31;

    int rt;
    rt = trame >> 16;
    rt = rt & 31;

    switch (opcode)
    {
        case 8 : //ADDI(8)
            MemoireCentrale[rt] = MemoireCentrale[rs] + immediate;
            
            if (MemoireCentrale[rt]<-32768 || MemoireCentrale[rt]>32767){
                printf("Erreur ADDI : Overflow\n");
            }
            break;

        case 15 : //LUI(15)
            MemoireCentrale[rt] = immediate << 16;
            break;

    }

}

void TypeBranchement_Exec(unsigned int trame,int MemoireCentrale[]){
    //Gérer les autres fonctions : BEQ(4), BNE(5), BLEZ(6), BGTZ(7), LW(35), SW(43)
    int offset;
    switch((trame>>26)&63){

        case 0 : ; //JR(0)
            offset = MemoireCentrale[(trame>>21)&31];
            MemoireCentrale[33] = offset;
            break;

        case 2:; //J(2)
             offset = trame&0x3ffffff;
            MemoireCentrale[33] = offset;
            break;

        case 3: ; //JAL(3)
            offset = trame&0x3ffffff;
            MemoireCentrale[33] = offset;
            MemoireCentrale[31] = MemoireCentrale[32]*4 + offset;
            break;

        case 4:; //BEQ(4)
            if (MemoireCentrale[(trame>>21)&31] == MemoireCentrale[(trame>>16)&31]){
                offset = trame&0x7fff;
                int parite = trame&0x8000 ;
            if (parite == 0x8000){
                offset = offset - 0x8000;
            }
            if (offset != 0){
                MemoireCentrale[33] = offset + MemoireCentrale[32] + 1;
                }
            else {
                MemoireCentrale[33] = MemoireCentrale[32] + 1;
                }
            }
            break;

        case 5:; //BNE(5)
            if (MemoireCentrale[(trame>>21)&31] != MemoireCentrale[(trame>>16)&31]){
                offset = trame&0x7fff;
                int parite = trame&0x8000;
            if (parite == 0x8000){
                offset = offset - 0x8000;
            }
            if (offset !=0 ){
                MemoireCentrale[33] = offset + MemoireCentrale[32] + 1;
                }
            else {
                MemoireCentrale[33] = MemoireCentrale[32] + 1;
                }
            }
            break;

        case 6:; //BLEZ(6)
            if (MemoireCentrale[(trame>>21)&31] <= MemoireCentrale[0]){
                offset = trame&0x7fff;
                int parite = trame&0x8000 ;
                if (parite == 0x8000){
                    offset = offset - 0x8000;
                }
                if (offset!=0){
                    MemoireCentrale[33] = offset + MemoireCentrale[32] + 1;
                } 
                else {
                    MemoireCentrale[33] = MemoireCentrale[32] + 1;
                }
            }
            break;

        case 7:; //BGTZ(7)
            if (MemoireCentrale[(trame>>21)&31] > MemoireCentrale[0]){
                offset = trame&0x7fff;
                int parite = trame&0x8000 ;
                if (parite == 0x8000){
                    offset = offset - 0x8000;
                }
                if (offset!=0){
                    MemoireCentrale[33] = offset + MemoireCentrale[32] + 1;
                }
                else {
                    MemoireCentrale[33] = MemoireCentrale[32] + 1;
                }
            }
            break;

        default :;
        MemoireCentrale[33]=-1;
        break;

    }
}
