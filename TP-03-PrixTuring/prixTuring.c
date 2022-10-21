/**
Compilation
gcc --std=c99 -W -Wall -o prixTuring prixTuring.c
 
Exécution
./prixTuring < turingWinners.txt > out.txt
 
Tests
diff out.txt turingWinners.txt
 
Détection de fuites mémoires
valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./prixTuring < turingWinners.txt > out.txt
**/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
 
 
typedef struct{
   int year;
   char * name;
   char * work;
} Winner;
 
Winner *readWinners(int nbWinners);
void initialiseWinner(Winner* winner);
void printWinners(Winner tab[], int nbWinners);
void printAWinner(Winner win);
void infosAnnee(int year, Winner tab[], int nbWinners);
void sortTuringWinnersByYear(Winner tab[], int nbWinners);
int firstYear(Winner tab[], int nbWinners);
int nextYear(Winner tab[], int nbWinners, int previousyear);
 
 
 
 
/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */
char* scanLine()
{
   int maxLineSize = 255;
   char c, *line = calloc(maxLineSize+1,sizeof(char));
 
   scanf("%250[^\n]", line);
 
   if ( (c = getchar()) != '\n') {
       /* we did not get all the line */
       line[250] = '[';
       line[251] = line[252] = line[253] = '.';
       line[254] = ']';
       // line[255] = '\0'; // useless because already initialized by calloc
 
       // let's skip all chars untli the end of line
       while (( (c = getchar()) != '\n') && c != EOF) ;
   }
 
   return line;
}
 
/* This function scans a line of text (until \n), converts it as an integer and returns this integer */int scanLineAsInt() {
 
   int buf;
   scanf("%i\n",&buf);
   return buf;
}
 
 
int main(void)
{
   char fileName[] = "turingWinners.txt";
   FILE* f;
   f = open(fileName, "r");
   if (f==NULL){
       printf("Error");
   }
 
   int nbWinners = scanLineAsInt();
   printf("nbGagnants = %i\n",nbWinners);
   Winner* win = readWinners(nbWinners); //on peut aussi écrire readWinners en faisant une WinnerArray winners = readWinners(nbWinners) et la WinnerArray est une struct avec l'array des Winners et le nb de winners
   printWinners(win, nbWinners);
 
   //infosAnnee(2003, win, nbWinners);
   //sortTuringWinnersByYear(win, nbWinners);
  
   free(win);
   fclose(f);
   return EXIT_SUCCESS;
}
 
Winner *readWinners(int nbWinners){
   Winner * tabWinners = (Winner *) calloc(nbWinners, sizeof(Winner));
   for (int i=0;i<nbWinners;i++){
       Winner winner;
       initialiseWinner(&winner);
       tabWinners[i] = winner;
   }
   return tabWinners;
}
 
void initialiseWinner(Winner* winner){
   winner->year = scanLineAsInt();
   winner->name = scanLine();
   winner->work = scanLine();
}
 
void printWinners(Winner tab[], int nbWinners){
   for (int i=0; i<nbWinners;i++){
       Winner win = tab[i];
       printAWinner(win);
   }
}
 
void printAWinner(Winner win){
   printf("%d \n",win.year);
   printf("%s \n", win.name);
   printf("%s \n", win.work);
}
 
 
void infosAnnee(int year, Winner tab[], int nbWinners){
   for (int i=0; i<nbWinners; i++){
       if ((tab[i]).year==year){
           printAWinner(tab[i]);
       }
   }
}

