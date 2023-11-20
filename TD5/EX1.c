#include <stdlib.h>
#include <stdio.h>

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
    if( a ==NULL){
        return creerArbre(nb);
    }
    else if(nb< a->num){
        a->left = ajoutFeuille(a->left,nb);            
        }
    else if (nb> a->num){
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

pArbre suppMax(pArbre a, int * pe){
    pArbre tmp = a;

    if(existFilsDroite(a) == 1){
        a->right = suppMax(a->right,pe);
    }
    else{
        *pe = a->num;
        tmp = a;
        a = a->left;
        free(tmp);
    }
    return a;
}

pArbre suppression(pArbre a,int e){
    pArbre tmp = a;
    if (a == NULL){
        return a;
    }
    else if(e> a->num){
        a->right = suppression(a->right,e);
    }
    else if (e < a->num){
        a->left = suppression(a->left,e);
    }
    else if( existFilsGauche(a) != 1){
        tmp = a;
        a = a->right;
        free(tmp);
    }
    else {
        a->left = suppMax(a->left, &(a->num));
    }
    return a;
}

int recherche(pArbre a,int e, int * noeud){
    if ( a==NULL){
        return 0;
    }
    else if ( e == a->num){
        *noeud +=1;
        return 1;
    }
    else if ( e < a->num){
        *noeud +=1;
        return recherche(a->left,e, noeud);
    }
    else {
        *noeud +=1;
        return recherche(a->right, e, noeud);
    }
}

int main(){
    pArbre a = NULL;
    pArbre b = NULL;
    int tab1[9] ={10,3,5,15,20,12,7,45,9};
    int tab2[9] = {9,45,7,12,20,15,5,3,10};
    a = creationArbre(a, tab1);
    b = creationArbre(b,tab2);
    parcoursInfixe(a);
    printf("\n");
    parcoursInfixe(b);
    printf("\n");
    //a = suppression(a,5);
    a = suppression(a,15);
    parcoursInfixe(a);
    printf("\n");
    int noeud = 0;
    if (recherche(a,9,&noeud) == 1){
        printf("Le nombre est present dans l'arbre et nous avons parcourus %d noeuds\n",noeud);
    }
    else{
        printf("Le nombre n'est pas present dans l'arbre et nous avons parcourus %d noeuds\n",noeud);
    }
    return 0;    
}