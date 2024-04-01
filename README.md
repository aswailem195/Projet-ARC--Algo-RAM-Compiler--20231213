#   Projet de fin de semestre : Conception d'un compilateur ALGO / RAM

## Introduction
Le but de ce Projet est de construire un compilateur du langage algorithmique vers la machine RAM
du cours d’algorithmique de 2éme année (arc pour Algo-Ram-Compiler). Pour cela nous utiliserons
conjointement Flex et Bison pour construire l’arbre syntaxique abstrait du programme, une table de
symbole sous forme de double liste chàinée et un module chargé de gérer l’arbre abstrait et de produire
le code cible
- Nous avons réussi à compiler le programme contenu dans le fichier `example12.algo`, dans lequel nous indiquons ce qui ne fonctionne pas encore.
- Dans le répertoire test, il y a des exemples numérotés de 1 à 12.
- Pour faciliter l'exécution du code, nous récupérons le code de la machine RAM de M. Zanotti. Ensuite, pour compiler notre algorithme, nous utilisons la commande :
  ```
    /bin/arc "./test/exemple{file_number}.algo"
  
  ```
- Vous pouvez l'exécuter avec la commande :
    ```bash
  node ./ram/ram.js out.ram ./ram/input
     ```
  - Si Node.js n'est pas installé, vous pouvez l'installer en utilisant les commandes suivantes :
    - Sur Ubuntu ,Debian ou archi :
        ```bash
        sudo apt update
        sudo apt install nodejs
        sudo pacman -S nodejs
        ```
    - Sur CentOS ou Fedora :
        ```bash
        sudo yum install nodejs
        ```
    - Sur macOS avec Homebrew :
        ```bash
        brew install node
        ```
    - Sur Windows, téléchargez l'installeur à partir du site officiel de Node.js : [Node.js Downloads](https://nodejs.org/en/download/)


- Dans le fichier "input", nous mettons les valeurs des données d'entrée.
- Pour faciliter les tests de code, vous pouvez utiliser la commande :
     ```
  ./test -{option} file_number
     ```

Les options sont les suivantes :
- "-l" : lire
- "-c" : compiler
- "-e" : compiler et exécuter
- "-h" : liste des exemples

Dans les sections suivantes, nous expliquerons en détail chaque fichier individuel du projet.

## Analyse lexicale (`lexer.lex`) - Reconnaissance du vocabulaire

Il s'agit du découpage du flot de données en unités lexicales, en accord avec le code portant du sens. pour l'exemple 6:

```algo
VAR g<-9
PROGRAMME()
VAR taille,t[5], @p
DEBUT
    ALLOUER( p, 10 )
    taille <- 5+3
    t[0] <- 1
    p[0] <- 5
FIN
```
- <PROGRAMME, "PROGRAMME">
- <(, "(">
- <), ")">
- <VAR, "VAR">
- ..
## Analyse syntaxique (parser.y, asa.h, asa.c)

Il prend les unités lexicales et produit une structure reflétant la grammaire du langage.
### Affichage avec DOT

Pour faciliter la visualisation et la gestion de la structure arborescente de notre programme, nous avons utilisé l'outil DOT. Cette technique s'est avérée être une solution claire et intuitive pour représenter l'arbre syntaxique généré par le compilateur. Pour le dernier exemple, l'image ci-dessous représente cette structure.

Arbre syntaxique généré par le compilateur pour example 6
## Analyse sémantique (Semantic.c, ts.c)

Elle utilise l'arbre abstrait pour vérifier le sens des instructions. Elle permet de détecter les erreurs de typage, d'incompatibilité de type, de déclaration de variables, et de dépassement de mémoire.
## Génération de code intermédiaire

- Génère du code pour une machine RAM.
- La structure de la mémoire est détaillée dans le rapport.
