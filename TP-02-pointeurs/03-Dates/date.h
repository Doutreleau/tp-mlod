
#ifndef DATE_H
#define DATE_H

enum MesMois{janvier = 1, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre};

typedef enum MesMois Mois;

struct DateSimple{
    int jour;
    Mois mois;
    int annee;
};

typedef struct DateSimple Date;

void initialiseDate(Date *d);

void afficheDate(Date *d);

char* libelleMois(Mois m);

Date creerDateParCopie();

Date *newDate();

unsigned int nbreJours(Mois mois, unsigned int annee);

bool estBissextile(unsigned int annee);


#endif