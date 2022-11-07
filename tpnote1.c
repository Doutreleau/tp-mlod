
#include <stdio.h>

int * repeat (int * t1, int * t2);
int avoir_nombre_de_contenus_dans_nouveau_tableau(int t1[]);
void print(int * tab);


int * repeat (int * t1, int * t2){
    
    int nombreDeContenusDansNewT2 = avoir_nombre_de_contenus_dans_nouveau_tableau (t1);
    

    int newt2 [nombreDeContenusDansNewT2];

    for (int i=0;i< sizeof(t1); i++){
        int nombreRepetitions = t1[i];
        
        for (int j=0;j<nombreRepetitions;j++){
            newt2[j] = t2[i];
        }
    }
    return (&newt2);


}

int avoir_nombre_de_contenus_dans_nouveau_tableau(int *t1){
    int nombreDeContenusDansNewT2 = 0;
    for (int indiceDeT1=0; indiceDeT1< sizeof(t1); indiceDeT1++){
        nombreDeContenusDansNewT2 += t1[indiceDeT1];
    }
    return nombreDeContenusDansNewT2;
}

int main(void){
    int t1 = {1,2,4};
    int size = sizeof(t1);
    int t2 = {10,3,8};
    int * newTab = repeat (t1, t2);
    affiche_tableaux(newTab, sizeOf(newTab));
    return 0;
    
}

void affiche_tableau(int *tab, unsigned taille)
{
    for (unsigned i = 0; i < taille; ++i)
        printf("tab[%u] = %d\n", i, tab[i]);
}
