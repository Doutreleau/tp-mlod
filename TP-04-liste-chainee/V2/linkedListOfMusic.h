
#pragma once

#include <stdbool.h>
#include "linkedList.h"
#include "linkedList.c"


typedef struct Music {
	char * name;
	char * artist;
	char * album;
	char * genre;
	int disc_Number;
	int track_Number;
	int year;
}Music;

typedef Music* Element;

bool equalsElement(Music * a,Music * b);
void afficheElement(Music * e);
void detruireElement(Music * a);
