#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "date.h"

int main(void) {

    //question b
    Date d;
    initialiseDate(&d); // &d désigne le pointeur associé à d
    afficheDate(&d);

    //question c
    Date date1;
    date1 = creerDateParCopie();
    afficheDate(&date1);

    //question d
    Date *date;
    date = newDate();
    afficheDate(date);

    free(date);
    date = NULL; //c'est une bonne pratique à faire après chaque free(..)

    //question f

    Mois mois = fevrier;
    int i = nbreJours(mois, 2000);
    printf("Nombre de jours dans le mois : %d \n",i);

    return 0;
}

void initialiseDate(Date *d){
    d->jour = 1; //équivalent à (*d).jour = 1;
    d->mois = janvier;
    d->annee = 1900;
}

void afficheDate(Date *d){
    // Version 1
    printf("%d/", d->jour);
    printf("%d/", d->mois);
    printf("%d \n", d->annee);
    
    // Version 2
    //printf( "%i %s %i \n", d->jour, libelleMois(d->mois), d->annee);
}

char* libelleMois(Mois m){
    char* nomsDesMois [] = {"Janvier", "Fevrier", "Mars","Avril", "Mai", "Juin", "Juillet", "Aout", "September", "Octobre", "Novembre", "Decembre"};
    return nomsDesMois[m-1]; // le -1 est parce que l'indice du tableau démarre à 1
}

Date creerDateParCopie(){
    Date d;
    initialiseDate (&d);
    return d;
}

Date *newDate(){
    Date *a = (Date *) malloc(sizeof(Date)); //malloc(...) renvoie un pointeur générique (ie void *), puis le cast en Date *
    initialiseDate(a);
    return a;
}

unsigned int nbreJours(Mois mois, unsigned int annee){ //attention années bisextiles!
    int nombreJours [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (estBissextile(annee)){
        nombreJours[1]=29;
    }
    return nombreJours[mois-1];
}

bool estBissextile(unsigned int annee){
    if(annee%4==0 && annee%100!=0){
        return true;
    }
    else if(annee%400==0){
        return true;
    }
    return false;
}

