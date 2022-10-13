#include <stdio.h>
#include <stdint.h>

#define SIZE 5

int main(void) {
    int64_t matrice1[][SIZE]={{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int64_t matrice2[][SIZE]={{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10}};
    int64_t matriceResultat[SIZE][SIZE];

    matrix_mult(matriceResultat,matrice1,matrice2);
    matrix_print(matriceResultat);

    for(int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            matrice1[i][j]=0;

        }
    }

    return 0;
}

void matrix_mult(int64_t mResultat[SIZE][SIZE], int64_t m1[SIZE][SIZE], int64_t m2[SIZE][SIZE]){
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            mResultat[i][j]=0;
            for (int k=0; k<SIZE; k++){
                mResultat[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
}


void matrix_print(int64_t m[SIZE][SIZE]){
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            printf("%li\t",m[i][j]);
        }
        printf("\n");
    }
}
//Algo peu réutilisables, ca marche seulement pour les matrices 5*5, il faut changer manuellement le SIZE dans le code.

/* 
Pour la généralisation:


typedef struc{
    uint8_t numLines;
    uint8_t numColumns;
    int **values;
} Matrix;


void matrix_mult (Matrix res, Matrix matrice1, Matrix matrice2){
    //Comme le cas précédent    
}
*/