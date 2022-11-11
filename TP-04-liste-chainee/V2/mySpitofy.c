//#include "linkedListOfMusic.h"
//#include "linkedListOfMusic.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
 
#define nbSongs 2702
#define maxChar 200
 
 
typedef struct Music {
   char * name;
   char * artist;
   char * album;
   char * genre;
   int disc_Number;
   int track_Number;
   int year;
}Music;
 
 
struct cellule_s {
   Music *val;
   struct cellule_s* suiv;
};
 
typedef struct cellule_s Cellule;
 
typedef Cellule* Liste;
 
void sort(Liste*h);
 
// retourne vrai si l est vide et faux sinon
bool estVide(Liste l);
 
// créer une liste d'un seul élément contenant la valeur v
Liste creer(Music * v);
 
// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Music * v, Liste l);
 
 
// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_Music *
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l);
 
// version recursive
void afficheListe_r(Liste l);
 
 
// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l);
 
// version récursive
void detruire_r(Liste l);
 
// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Music * v, Liste l);
 
// version recursive
Liste ajoutFin_r(Music * v, Liste l);
 
// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Music * v,Liste l);
 
// version récursive
Liste cherche_r(Music * v,Liste l);
 
// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Music * v, Liste l);
 
// version recursive
Liste retirePremier_r(Music * v, Liste l);
 
 
void afficheEnvers_r(Liste l);
 
 
void afficheMusic (Music * m){
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
 
void detruireMusic (Music * e){
   free(e);
};
 
bool equalsMusic (Music * e1, Music * e2){
   return strcmp((char *) e1, (char *) e2)==0;
}
 
 
 
// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
   return l == NULL;
}
 
// créer une liste d'un seul élément contenant la valeur v
Liste creer(Music * v){
   Liste list = malloc(sizeof(Cellule));
   if (list != NULL){
       (*list).val = v;
       (*list).suiv = NULL;
   }
   return list;
}
 
// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Music * v, Liste l) {
   Liste list = creer(v);
   (*list).suiv=l;
   return list;
}
 
 
// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_Music *
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) {
   if (! estVide(l)){
       while ((*l).suiv!=NULL){
           afficheMusic((*l).val);
           l = (*l).suiv;
       }
       printf("\n");
   }
}
 
// version recursive
void afficheListe_r(Liste l) {
   if (! estVide(l)){
       afficheMusic(l->val);
       afficheListe_r(l->suiv);
   }
   else
   {
       printf("/n");
   }
  
}
 
// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
   Liste suivant, courant = l;
 
   while(!estVide(courant)){
       suivant = courant->suiv;
       detruireMusic(courant->val);
       free(courant);
       courant = suivant;
   }
}
 
// version récursive
void detruire_r(Liste l) {
   if(!estVide(l)){
       detruire_r(l->suiv);
       detruireMusic(l->val);
       free(l);
   }
}
 
// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Music * v, Liste l) {
   Liste elem = creer(v);
   Liste p = l;
 
   if(estVide(p)){
       return elem;
   }
 
   while (!estVide(p->suiv))
       p=p->suiv;     
   p->suiv = elem;
  
   return l;
}
 
// version recursive
Liste ajoutFin_r(Music * v, Liste l) {
   if(estVide(l)){
       return creer(v);
   }
   else{
       l->suiv = ajoutFin_r(v,l->suiv);
   }
   return l;  
}
 
 
// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Music * v,Liste l) {
   Liste p = l;
 
   while (!estVide(p) && (!equalsMusic(p->val, v))){
       p = p-> suiv;
   }
   return p;
}
 
// version récursive
Liste cherche_r(Music * v,Liste l) {
   if(estVide(l) || equalsMusic(v, l->val)){
       return l;
   }  
   else{
       return cherche_r(v, l->suiv);
   }
}
 
// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Music * v, Liste l) {
   Liste precedent, p;
 
   if(estVide(l)){
       return l;
   }
 
   if(equalsMusic(l->val, v)){
       p = l->suiv;
       l -> suiv = NULL;
       detruire_r(l);
       return p;
   }
 
   precedent = l;
   p = l->suiv;
   while(!estVide(p) &&(!equalsMusic(p->val, v))){
       precedent = p;
       p = p->suiv;
   }
 
   if(!estVide(p)){
       //on a trouvé v
       precedent -> suiv = p-> suiv;
       p-> suiv = NULL;
       detruire_r(p);
   }
 
   return l;
}
 
 
// version recursive
Liste retirePremier_r(Music * v, Liste l) {
   Liste p = l;
   if(estVide(l)){
       return l;
   }
 
   if(equalsMusic(l->val, v)){
       p = l->suiv;
       l -> suiv = NULL;
       detruire_r(l);
       return p;
   }
 
   l->suiv = retirePremier_r(v, l->suiv);
   return l;
}
 
 
void afficheEnvers_r(Liste l) {
   if(!estVide(l)){
       if(!estVide(l->suiv)){
           afficheEnvers_r(l->suiv);
       }
       else{
           afficheMusic(l->val);
           printf(" ");
       }
   }
}
 
 
 
void sort(Liste*h)
{
   Music *a;
 
   Liste temp1;
   Liste temp2;
 
   for(temp1=*h;temp1!=NULL;temp1=temp1->suiv)
     {
       for(temp2=temp1->suiv;temp2!=NULL;temp2=temp2->suiv)
         {
           if(((temp2->val)->year) < ((temp1->val)->year))
             {
               a = temp1->val;
               temp1->val = temp2->val;
               temp2->val = a;
             }
          }
      }
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
   //first Music * of list
   char *string;
   Music * newMusic = (Music *) malloc(sizeof(Music));
   fgets(row, nbSongs, f); //gets the first line, which we don't want because it is "Name, ARtist...."
   fgets(row, nbSongs, f); //second line (ie the first line we are interested in)
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
 
   Liste listOfMusic = creer(newMusic);
   //printf("estVide(l) = %s\n",estVide(listOfMusic)?"TRUE":"FALSE");
 
   while ((feof(f) != true))
   {
       char *string;
       Music * newMusic = (Music *) malloc(sizeof(Music));
       fgets(row, nbSongs, f);
       string = strdup(row); //caution : strdup contains a malloc!
       if(newMusic != NULL && string != NULL){
           newMusic -> name = strsep(&string, ",");
           newMusic -> artist = strsep(&string, ",");
           newMusic -> album = strsep(&string, ",");
           newMusic -> genre = strsep(&string, ",");
           newMusic -> disc_Number = atoi(strsep(&string, ","));
           newMusic -> track_Number = atoi(strsep(&string, ","));
           newMusic -> year = atoi(strsep(&string, ",")); 
           free(string);           
       }
       listOfMusic = ajoutFin_i(newMusic, listOfMusic);      
      
   }
 
   printf("liste originelle, non triée:\n");
   afficheListe_i(listOfMusic);
 
   printf("\n \n \n");
   printf("liste triée:\n");
   sort(&listOfMusic);
   afficheListe_i(listOfMusic);
  
   fclose(f);
 
   return EXIT_SUCCESS;
}

