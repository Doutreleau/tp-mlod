
//#include "linkedListOfMusic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <stdio.h>

void afficheElement(Element m){
    printf("%s", m->name);
    printf(",");
    printf("%s", m->artist);
    printf(",");
    printf("%s", m->album);
    printf(",");
    printf("%s", m->genre);
    printf(",");
    printf("%i", m->disc_Number);    
    printf(",");
    printf("%i", m->track_Number);    
    printf(",");
    printf("%i", m->year);    
    printf("\n");
};

void detruireElement(Element e){
    free(e);
};

bool equalsElement(Element e1, Element e2){
    return strcmp((char *) e1, (char *) e2)==0;
}
