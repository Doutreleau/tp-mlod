#include "linkedListOfMusic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define nbSongs 2702


void sort(Liste*listOfSongs);
Music * initializeNewMusic(char row[], FILE* f);



void sort(Liste *listOfSongs)
{
    Music *music;

    Liste temp1;
    Liste temp2;

    for(temp1=*listOfSongs;temp1!=NULL;temp1=temp1->suiv)
      {
        for(temp2=temp1->suiv;temp2!=NULL;temp2=temp2->suiv)
          { 
            if(((temp2->val)->year) < ((temp1->val)->year))
              {
                music = temp1->val;
                temp1->val = temp2->val;
                temp2->val = music;
              }
           }
       }
}


Music *initializeNewMusic(char row[], FILE* f){
	char * string;
	Music * newMusic = (Music *) malloc(sizeof(Music));
    fgets(row, nbSongs, f); 
    string = strdup(row); //caution : strdup contains a malloc!
    if( newMusic != NULL && string != NULL){
        newMusic -> name = strsep(&string, ",");
        newMusic -> artist = strsep(&string, ",");
        newMusic -> album = strsep(&string, ",");
        newMusic -> genre = strsep(&string, ",");
        newMusic -> disc_Number = atoi(strsep(&string, ","));
        newMusic -> track_Number = atoi(strsep(&string, ","));
        newMusic -> year = atoi(strsep(&string, ","));  
        free(string);            
    }
    return newMusic;
}

int main (void){   
    
    char fileName[] = "music.csv";
    FILE* f;
    f = fopen(fileName,"r");
    
    if(f==NULL) {
        printf ("Code de l'erreur : %d\n", errno);
        if (errno == ENOENT)
            printf ("Le fichier n'existe pas !\n");
        else{
            printf ("Erreur inconnue\n");
        }
        return EXIT_FAILURE;
    }

    char row[nbSongs];
    fgets(row, nbSongs, f); //gets the first line, which we don't want because it is "Name, Artist...."
	Music *newMusic = initializeNewMusic(row,f);
    Liste listOfMusic = creer(newMusic);

    while ((feof(f) != true))
    {
        newMusic = initializeNewMusic(row,f);
        listOfMusic = ajoutFin_i(newMusic, listOfMusic);  
    }

	printf("LISTE ORIGINELLE, NON TRIEE:\n");
    afficheListe_i(listOfMusic);

	printf("\n \n \n");
	printf("LISTE TRIEE:\n");
    sort(&listOfMusic);
    afficheListe_i(listOfMusic);
	detruire_i(listOfMusic);
    
    fclose(f);

    return EXIT_SUCCESS;
}
