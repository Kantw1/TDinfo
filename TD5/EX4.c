#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct arbre{
    int num;
    struct arbre * left;
    struct arbre * right;
}Arbre;

typedef Arbre * pArbre;

pArbre creerArbre(int nombre){

    pArbre p1 = malloc(sizeof(Arbre));
    if (p1 == NULL){
        exit(1);}
    p1->num = nombre;
    p1->left = NULL;
    p1->right = NULL;

    return p1;
}

int existFilsGauche(pArbre a){
    if (a->left != NULL){
        return 1;
    }
    else{
        return 0;}
}
int existFilsDroite(pArbre a){
    if (a->right != NULL){
        return 1;
    }
    else{
        return 0;}
    }

pArbre ajoutFeuille(pArbre a, int nb){
    int var = rand()%10;
    if( a ==NULL){
        return creerArbre(nb);
    }
    else if(var%2 == 0){
        a->left = ajoutFeuille(a->left,nb);            
        }
    else{
        a->right = ajoutFeuille(a->right, nb);
        }
    return a;
}
pArbre creationArbre(pArbre a, int tab[]){
    for( int i = 0; i<9; i++){
        a = ajoutFeuille(a,tab[i]);
    }
    return a;
}

void traiter(pArbre a){
    printf("%d ->",a->num);
}

void parcoursPrefixe(pArbre a){
    if ( a !=NULL){
        traiter(a);
        parcoursPrefixe(a->left);
        parcoursPrefixe(a->right); }
}

void parcoursInfixe(pArbre a){
    if ( a !=NULL){
        parcoursInfixe(a->left);
        traiter(a);
        parcoursInfixe(a->right); }
}

void isABR (pArbre a, int min, int max){
if(a != NULL){
printf("\nC'est un ABR");
}
if((a->num > a->left->num) && (a->num < a->right->num) &&(a->num<max)&&(a->num > min)){
isABR
}
}

int main(){
srand(time(NULL));
    pArbre a = NULL;
    pArbre b = NULL;
    int tab1[9];
    int tab2[9];
    int nb;
    for (int i = 0; i<9; i++){
    nb = rand()%100;
    tab1[i] = nb;
    tab2[9-i] = nb;
    }
    a = creationArbre(a, tab1);
    b = creationArbre(b,tab2);
    parcoursPrefixe(a);
    printf("\n");
    parcoursPrefixe(b);
    isABR(a,a->left->num,a->right->num);
    return 0;    
}