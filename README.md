# Projet CS351 (2022-2023): Émulateur MIPS

---
title: Projet CS351 (2022-2023): Émulateur MIPS
author: [CAMUS Alexis, ALAZARD Camilles]
date: [22/11/2022]
---

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Vérifié que `make test-cli` ne renvoie pas d'erreur.
  - [x] Vérifié que `make tests` se plaint sur le nombre d'instructions et pas sur l'existence des fichiers de sortie.
  - [x] Vu que les soumissions se font avec `make tar`.


## Rendu 2

(Une dizaine de lignes devrait suffire à chaque fois)

* Comment avez-vous choisi de programmer l'analyse de texte (dont la lecture des opérandes entières) ?

  Dans le cas d'une lecture de fichier, lors de l'extraction de la ligne, les commentaires sont ignorées pour ne pas être envoyé dans le programme d'analyse. L'analyse doit donc uniquement extraire la commande et les opérandes, ce qui se fait en plusiurs étapes :

  Dans la première étape, on extrait la commande (ADDI, XOR...) pour trouver de quel type de commande (I,R ou J) il s'agit.

  Dans la deuxième étape, on extrait les opérandes et les placent dans le bon registre (rs,rd...ect).

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs pour éviter de les répéter ? Si non, serait-ce difficile ?

  Il y a effectivement des motifs reguliers.
  On peut diviser les commandes en trois types (I,R ou J) avec chacune une structure de base. 
  Ensuite, on forme des sous groupes dans les types de commandes en fonction du nombre et de l'ordre des arguments des instructions. Dans le type I par exemple, les instructions BEQ et BNE prennent trois arguments ($rs, $rt et offset) alors que BGTZ et BLEZ ne prennent que deux arguments ($rs et offset) alors on sépare ses instructions en deux sous groupe du type I.

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que toutes les instructions gérées sont couvertes ? 

  Nous avons créé un fichier par catégorie d'instructions spécifiées dans les tableaux de l'annexe 1 (soit un fichier "arithmetic", un fichier "logics", un fichier "decalage-set", un fichier "load-store" et un fichier "decalage-set") pour nous assurer que toutes les instructions soient couvertes.


* Quelle a été votre expérience avec l'utilisation et la compréhension de la documentation (ie. des annexes) ?


* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Implémenté la traduction pour des instructions de toutes les catéories
      (calcul, comparaisons, sauts, HI/LO, mémoire)
  - [x] Implémenté la traduction pour toutes les instructions de l'annexe 2
  - [ ] Pris en compte les cas particuliers : valeurs négatives, hors limites,
      noms d'instructions ou opérandes invalides...


## Rendu 3

(10/15 lignes devrait suffire à chaque fois)

* Quelle structure en modules planifiez-vous d'utiliser pour l'émulateur ?

  (voir SchémaModule) 
  Nous avons choisi de diviser en 3 modules la partie du programme permettant de faire la transition des instructions (comme par exemple "ADDI $7, $8, 45") aux instructions en hexadécimal.
  Nous avons prévu de diviser en 3 modules la partie du programme permettant d'exécuter ces instructions comme le ferait un processeur MIPS. Un premier module permettrait de gérer la mémoire et les accès mémoire, un deuxième de réaliser les instructions et un troisième de restituer le résultat dans un fichier texte (sortie_execution.txt).
  
* Quelles seront les fonctions principales de chaque module ?

  Le module "LectureDeFichier" permet de lire et écrire des fichiers textes ainsi que de d'extraire l'instruction et son type d'une ligne lue. Il permet aussi la convertion finale de la trame de 32 bits en hexadécimal.

  Le module "Types" trouve l'opcode de l'instruction (et le special si nécéssaire), extrait les arguments et les convertis en binaire. Enfin, il permet de rassembler tout cela dans la trame de 32 bits binaire.
  
  Le module "Conversion" quant à lui contient des fonctions de conversions entre bases 2,10 et 16.

* Quels avantages voyez vous à cette structure (à comparer à un unique fichier)?

  Cette structure permet de mieux séparer les fonctions et d'éviter que des fichiers soient trop volumineux. Cela répartit aussi mieux les tâches de travail et permet de lire le programme plus facilement.

## Rendu 4

* Avez-vous réussi à suivre la structure prévue au rendu 3 ? Quelles
modifications ont été nécessaires ? Rétrospectivement, est-ce que cette
structure était bien prévue ?

  (voir SchémaModuleRendu4)
  Nous avons globalement reprit la structure prévue dans le rendue 3 à la différence près que nous avons ajouté une sous partie Conversion_Exec au module Execution. 
  Nous aurions pu faire un troisième module Conversion avec les fonctions IntToBin, BinaryToHexa et HexaToInt mais nous avons préféré les inclures dans les deux modules Instruction -> Hexa et Execution puisqu'aucune des fonctions de Conversion n'est utilisé dans le module Execution, et qu'aucune fonction de Conversion_Exec n'est utilisé dans le module Instruction -> Hexa.

* Avez-vous compris le fonctionnement de chaque instruction à partir de la documentation fournie ? Si non, quels sont les points obscurs ?

  Nous avons eu des difficulés à comprendre le fonctionnement des branchements et de jumps. Nous avons trouvé les exemples plus parlant pour comprend leur logique et ils permettent de répondre à certaines questions non précisées dans le sujet (Le concept de Delay Slots par exemple).

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les comparaisons et sauts ? La mémoire ?

  Nous avons globalement peu de tests pour tester le programme.
  Nous avons réutilisé les tests du rendu 2 dont nous avions déjà prévu la sortie à l'exécution et nous avons fait un programme Fibonacci pour tester un exemple de boucle for.
  Le seul test que nous avons choisi de ne pas réutiliser est le test consernant les jumps et les branchement. Nous avons préféré utiliser le test fourni par l'équipe pédagogique pour tester ses fonctions ainsi que pour tester delay_slot.

* Le sujet spécifie-t-il tous les détails nécessaires pour bien implémenter la mémoire ? Quels choix avec-vous faits ?

  Nous avons décidé de séparer la mémoire contenant les instructions (la mémoire variable) et la mémoire composée des 36 registres spécifiés dans le sujet (les 32 registres généraux + HI + LO + PC + IR) (mémoire centrale) pour faciliter l'accès à la liste d'instructions.
  La mémoire variable est une liste chainée alors que la mémoire centrale est un tableau de 36 entiers.

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

  Au moment de l'envoi nos tests fonctionnent et nous n'avons pas trouvé de bugs.

* D'autres remarques sur votre programme ?

  Nous n'avons pas eu le temps de permettre l'entrée des instructions avec les noms des registres au lieu de leur numéro ($sp,$zero ect..), si   l'assembleur est entré de cette manière le programme ne marchera pas.


* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [x] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [x] Implémenté l'émulation de toutes les instructions.
  - [x] Tous vos tests qui passent.
  - [x] Vérifié que vous tests couvrent toutes les instructions émulées.
  - [x] Testé les cas particuliers : valeurs négatives, overflows...
  - [x] Testé les cas d'erreur : division par zéro, sauts invalides...
  - [ ] Un port fonctionnel de DOOM pour votre émulateur.

* Des retours sur le projet en général ?

  1) Mieux étaler les séances en présentiel (nous avons eu beaucoup de séances pour les rendus 1 et 2 mais très peu pour la séance 3 et pas du tout pour la séance 4)
  2) Une correction des tests après le rendu 3. Si nous n'avions pas eu "delay_slots.s" et "jump_ops.s" par exemple, nous aurions mal fait les branchements sans le savoir.
