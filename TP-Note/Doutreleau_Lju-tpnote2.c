#include <stdlib.h>
#include <stdio.h>


#define CHUNK_SIZE_MAX 5


//question 1
typedef struct String{
    int chunkSize;
    char * chunk;
    struct String *nextString;
}String;


void string_new(char * string);
void destroy_string(String s);
int char_length(char * expression);
unsigned int string_length (String s);

//question 2
int char_length(char * expression){
    int l = 0;
    char c = expression[l];
    while( c != '\0' ) {
        c = expression[l];
        l++;
    }
    return l;
}

void string_new(char * string){
    String * pointeur_new_string = (String *) malloc(sizeof(String));    

    if(pointeur_new_string != NULL){
        pointeur_new_string -> nextString = NULL;
        pointeur_new_string -> chunk = string;
        pointeur_new_string -> chunkSize = char_length(string);
    }
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
    if(expression[0] !=NULL){
        char * new_char = expression[0];
    }
    if(expression[1] != NULL){
        new_char += expression[1];
    }
    if(expression[2] != NULL){
        new_char += expression[2];
    }
    if(expression[3] != NULL){
        new_char += expression[3];
    }
    if(expression[4] != NULL){
        new_char += expression[4];
    }
}

String string_insert_at(String original_string, int position, char * added_string){
    int length_original_string = string_length(original_string);
    int length_added_string = char_length(added_string);

    
    
}


int main(void){
    String s = string_new("HELLO !");
    unsigned int size = string_length(s);
    printf("%i", size);
    destroy_string(s);
    
}