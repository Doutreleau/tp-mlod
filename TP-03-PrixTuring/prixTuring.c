#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "prixTuring.h"

/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
@@ -48,12 +49,120 @@ int scanLineAsInt() {
	return buf;
}

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
Winner *addNewWinner( Winner tab[], int nbWinners);
void printAWinnerFromIndex(Winner tab[], int index);

int main(void)
{
	int nbWinners = scanLineAsInt();
	printf("nbGagnants = %i\n",nbWinners);
	Winner* win = readWinners(nbWinners); //on peut aussi écrire readWinners en faisant une WinnerArray winners = readWinners(nbWinners) et la WinnerArray est une struct avec l'array des Winners et le nb de winners
	//printWinners(win, nbWinners);

	int nbGagnants = scanLineAsInt();
	printf("nbGagnants = %i\n",nbGagnants);

	//infosAnnee(2003, win, nbWinners);
	//sortTuringWinnersByYear(win, nbWinners);
	win = addNewWinner( win, nbWinners);
	printWinners(win, nbWinners+1);
	for (int i=0;i<nbWinners;i++){ //it's not "nbWinners+1" because, even if we call the function addNewWinner, there was no scanLine() for the added winner, so there is no need to free space
		free((win[i]).name);
		free((win[i]).work);
	}
	free(win);
	return EXIT_SUCCESS;
}

Winner *readWinners(int nbWinners){	
	Winner * tabWinners = (Winner *) calloc(nbWinners, sizeof(Winner));
	for (int i=0;i<nbWinners;i++){
		initialiseWinner(&tabWinners[i]);
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


void sortTuringWinnersByYear(Winner tab[], int nbWinners){
	//first step : find the first year
	int firstyear = nextYear(tab, nbWinners, 0);

	//after finding the first year, we look for the next year, then the next next year, until we reach the last year.
	int count = 1; //will count the number of years found
	while (count<nbWinners){
		int nextyear = nextYear(tab, nbWinners, firstyear);
		firstyear = nextyear;
		count++;
	}
}

//finds the next year of the Turing Prize, and prints the name of the nominee and their work
int nextYear(Winner tab[], int nbWinners, int previousyear){
	int min=9999999; //this is a random big year, which should never be reached. It will later contain the smallest year
	int index=0; //index of the first year
	for (int i=0; i<nbWinners; i++){
		if((tab[i]).year<min && (tab[i]).year>previousyear){
			min = (tab[i]).year;
			index = i;
		}
	}
	printAWinnerFromIndex(tab, index);
	return min;
}

void printAWinnerFromIndex(Winner tab[], int index){
	printf("%d \n", (tab[index]).year);
	printf("%s \n", (tab[index]).name);
	printf("%s \n", (tab[index]).work);
}


Winner *addNewWinner(Winner tab[], int nbWinners){
	int newYear = 2016;
	char * newName = "Tim Berners-Lee";
	char * newWork = "Invention du WWW";
	tab = (Winner *) realloc(tab, (nbWinners+1)*sizeof(Winner));
	(tab[nbWinners]).year = newYear;
	(tab[nbWinners]).name = newName;
	(tab[nbWinners]).work = newWork;
	return (tab);
}
