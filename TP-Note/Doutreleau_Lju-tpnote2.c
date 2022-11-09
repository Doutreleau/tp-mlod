#include <stdlib.h>
#include <stdio.h>
 
 
#define CHUNK_SIZE_MAX 5
 
 
//question 1
typedef struct String{
   int chunkSize;
   char * chunk;
   struct String *nextString;
}String;
 
 
String string_new(char * string);
void destroy_string(String s);
int char_length(char * expression);
unsigned int string_length (String s);
char * truncate_5_first_char( char* added_string,int length_added_string);
 
//question 2
int char_length(char * expression){
   int length = 0;
   char c = expression[length];
   while( c != '\0' ) {
       c = expression[length];
       length++;
   }
   return length;
}
 
String string_new(char * string){
   String * pointeur_new_string = (String *) malloc(sizeof(String));   
 
   if(pointeur_new_string != NULL){
       pointeur_new_string -> nextString = NULL;
       pointeur_new_string -> chunk = string;
       pointeur_new_string -> chunkSize = char_length(string);
   }
   return *pointeur_new_string;
}
 
//question 3
//la fonction qui manque est une fonction pour détruire le String (puisqu'on a fait un malloc dans la création d'un String).
 
void destroy_string(String s){
   if (&s != NULL){
       free(&s);
   }
}
 
unsigned int string_length (String s){
   if ( &s !=NULL){
       return s.chunkSize;
   }
}
 
//question 4
 
char * get_the_first_five_char_of_expression(char * expression){
 
   char new_char[5];
 
   if(expression[0] !=NULL){
       new_char[0] = expression[0];
   }
   if(expression[1] != NULL){
       new_char[1] = expression[1];
   }
   if(expression[2] != NULL){
       new_char[2] = expression[2];
   }
   if(expression[3] != NULL){
       new_char[3] = expression[3];
   }
   if(expression[4] != NULL){
       new_char[4] = expression[4];
   }
   return new_char;
}
char * truncate_5_first_char( char* added_string, int length_added_string){
   char new_char = added_string[5];
  
   for (int i =0; i<length_added_string;i++){
 
   }
}
/*
String string_insert_at(String original_string, int position, char * added_string){
   int length_original_string = string_length(original_string);
   int length_added_string = char_length(added_string);
 
   //step 1 : we create a new string from the 5 first characters of added_string, and we reference it in the original string
   char * new_expression_from_added_string = get_the_first_five_char_of_expression(added_string);
   String next = string_new(new_expression_from_added_string);
   (&original_string) -> nextString = &next;
 
   //then we change added_string to truncate the 5 first characters
   added_string = truncate_5_first_char(added_string, length_added_string-5);
   length_added_string = length_added_string-5;
 
   //we re-do step 1 until there are less than 5 characters in added_string
   while(length_added_string >4){
       char * new_expression_from_added_string = get_the_first_five_char_of_expression(added_string);
 
       String new = string_new(new_expression_from_added_string);
       ((&next) -> nextString) = &(new);
       next = new;
       added_string = truncate_5_first_char(added_string, length_added_string-5);
       length_added_string = length_added_string-5;
      
   }
 
  
  
}*/
 
int main(void){
   String s = string_new("HELLO !");
   unsigned int size = string_length(s);
   printf("%i", size);
   destroy_string(s);
   return 0;
}

