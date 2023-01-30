#include"Conversion_Exec.h"

unsigned int HexaToInt(char s_hexa){
    switch (s_hexa){
        case 'a':
            return(10);
            break;
        case 'b':
            return(11);
            break;
        case 'c':
            return(12);
            break;
        case 'd':
            return(13);
            break;
        case 'e':
            return(14);
            break;
        case 'f':
            return(15);
            break;
        default :
            return s_hexa-'0';
        }
}