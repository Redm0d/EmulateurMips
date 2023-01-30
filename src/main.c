// Projet MIPS 2022-2023
// Auteurs: Camus_Alazard

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "Conversion.h"
#include "LectureDeFichier.h"
#include "Types.h"
#include "Restitution_Exec.h"

int main(int argc, char **argv){
    if (argc == 1){
        char instruction[20];
        char instruction_binaire[]="00000000000000000000000000000000";
        char instruction_hexa[]="00000000";
        if (fgets(instruction, sizeof(instruction), stdin)==NULL) {printf("Erreur Lecture\n");}
        Convertir(instruction,instruction_binaire);
        
        BinaryToHexa(instruction_binaire,instruction_hexa);
        printf("%s\n",instruction_hexa);
    }

    if (argc == 2) {
        /* S'il y a 2 arguments (argc==2), lancer le mode automatique pas-à-pas.
        Le premier argument (argv[1]) est le nom du programme assembleur.
        Le second argument (argv[2]) est forcément "-pas". */
        printf("---------taper 'quit' pour quitter le mode pas-à-pas---------\n");
        int q = 0;
        char instruction[20];
        char instruction_binaire[]="00000000000000000000000000000000";
        char instruction_hexa[]="00000000";
        while (q != 1){
            if (fgets(instruction, sizeof(instruction), stdin)==NULL) {printf("Erreur Lecture\n");continue;}
            if (strcmp(instruction,"quit\n") == 0){
                q = 1;
            } else {
                Convertir(instruction,instruction_binaire);
                
                BinaryToHexa(instruction_binaire,instruction_hexa);
                printf("%s\n",instruction_hexa);
            }
        }
   }

   if (argc == 4){
        // commande : ./emul-mips tests/arithmetic.s sortie_assemblage.txt sortie_execution.txt
        /* (argv[1]) -> nom du programme assembleur.
        (argv[2]) -> nom du fichier où il faut enregistrer le code assemblé.
        (argv[3]) -> nom du fichier où il faut enregistrer l'état final du programme
        à la fin de l'exécution. */

        Extraction(argv[1],argv[2]);
        printf("Assemblage Terminé\n");
        ExecPhase1(argv[2],argv[3]);
        
    }
    return (0);
}






