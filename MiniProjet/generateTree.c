// Execution : ./generateTree < events.txt > out.txt
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
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
 
/* This function scans a line of text (until \n), converts it as an integer and returns this integer */
int scanLineAsInt() {
   int buf;
   scanf("%i\n",&buf);
   return buf;
}
 
typedef struct{
   char * name;
   int num_of_child;
   char *parent;
   char *text;
   char * option1;
   char * option2;
   char * option3;
   char * option4;
   int proba;
   int position;
} Informations;
 
Informations *readInformations(int nbInformations);
void initialiseInformations(Informations* Informations);
void printInformations(Informations tab[], int nbInformations);
void printAInformations(Informations info);
 
int main(void)
{
   int nbInformations = scanLineAsInt();
   Informations* info = readInformations(nbInformations); 
   printInformations(info, nbInformations);
 
   for (int i=0;i<nbInformations;i++){
       free((info[i]).name);
       free((info[i]).text);
       free((info[i]).parent);
       free((info[i]).option1);
       free((info[i]).option2);
       free((info[i]).option3);
       free((info[i]).option4);
   }
   free(info);
   return EXIT_SUCCESS;
}
 
Informations *readInformations(int nbInformations){   
   Informations * tabInformations = (Informations *) calloc(nbInformations, sizeof(Informations));
   for (int i=0;i<nbInformations;i++){
       initialiseInformations(&tabInformations[i]);
   }
   return tabInformations;
}
 
void initialiseInformations(Informations* Informations){
   Informations->name = scanLine();
   Informations->num_of_child = scanLineAsInt();
   Informations->parent = scanLine();
   Informations->text = scanLine();
   Informations->option1= scanLine();
   Informations->option2= scanLine();
   Informations->option3= scanLine();
   Informations->option4= scanLine();
   Informations->proba = scanLineAsInt();
   Informations->position = scanLineAsInt();
}
 
void printInformations(Informations tab[], int nbInformations){
   for (int i=0; i<nbInformations;i++){
       Informations info = tab[i];
       printAInformations(info);
   }
}
 
void printAInformations(Informations info){
   printf("node * ");
   printf("%s", info.name);
   if(info.num_of_child ==1){
       printf(" = insert_first_child(");
   }
   else if(info.num_of_child ==2){
       printf(" = insert_second_child(");
   }
   else if(info.num_of_child ==3){
       printf(" = insert_third_child(");
   }
   else if(info.num_of_child ==4){
       printf(" = insert_fourth_child(");
   }
   printf("%s", info.parent);
   printf(", new_textEvent(");
   printf("\"");
   printf("%s", info.text);
   printf("\"");
   printf(", ");
   if( strcmp(info.option1, "NULL")){
       printf("\"");
       printf("%s", info.option1);
       printf("\"");
   }else printf("NULL");
   printf(", ");
   if( strcmp(info.option2, "NULL")){
       printf("\"");
       printf("%s", info.option2);
       printf("\"");
   }else printf("NULL");
   printf(", ");
   if( strcmp(info.option3, "NULL")){
       printf("\"");
       printf("%s", info.option3);
       printf("\"");
   }else printf("NULL");
   printf(", ");
   if( strcmp(info.option4, "NULL")){
       printf("\"");
       printf("%s", info.option4);
       printf("\"");
   }else printf("NULL");
   printf("), ");
   printf("%d",info.proba);
   printf(", ");
   printf("%d", info.position);
   printf(");");
   printf("\n");
 
}
 
 

