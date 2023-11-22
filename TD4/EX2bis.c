#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define size 10

typedef struct Arbre{
    int nb;
    struct Arbre * left;
    struct Arbre * right;
}Arbre;
typedef Arbre * pArbre;

typedef struct Chainon{
    pArbre Arbre;
    struct Chainon * next;
}Chainon;
typedef Chainon * pChainon;

typedef struct File{
    pChainon start;
    pChainon end;
}File;
typedef File * pFile;

pFile creerFile() {
    pFile f = malloc(sizeof(File));
    f->start = NULL;
    f->end = NULL;
    return f;
}
int fileVide(pFile f) {
    if (f->start == NULL){
        return 1;}
        else{
            return 0;
        }
}
void enfiler(pFile f, pArbre a){
    pChainon nouveau = malloc(sizeof(Chainon));
    nouveau->Arbre = a;
    nouveau->next = NULL;
    if (fileVide(f)){
        f->start = f->end = nouveau;
    }
    else {
        f->end->next = nouveau;
        f->end = nouveau;
    }
}

pArbre defiler(pFile f) {
    if (!fileVide(f)) {
        pChainon nouveau = f->start;
        pArbre a = nouveau->Arbre;
        f->start = f->start->next;
        free(nouveau);
        return a;
    }

    return NULL;
}
pArbre creationFeuille(int nombre){
    pArbre a = malloc(sizeof(Arbre));
    a->nb = nombre;
    a->left = NULL;
    a->right = NULL;
    return a;
}
pArbre embranchementFeuille(pArbre a, int nombre){
    int random = rand()%2;
    if (a==NULL){
        return creationFeuille(nombre);
    }
    else if ( random%2 == 0){
        a->left = embranchementFeuille(a->left,nombre);
    }
    else if ( random%2 != 0){
        a->right = embranchementFeuille(a->right,nombre);
    }
    return a;
}
pArbre creationArbre(pArbre a){
    for (int i = 0; i< size; i++){
        a = embranchementFeuille(a,rand()%30);
    }
    return a;
}
int estVide(pArbre a){
    if (a == NULL){
        return 1;
    }
    else {
        return 0;
    }
}
int estFeuille (pArbre a){
    if (estVide(a) == 0 && a->left ==NULL && a->right == NULL){
        return 1;
    }
    else{
        return 0;
    }
}
int element(pArbre a){
    return a->nb;
}
int existeFilsGauche(pArbre a){
    if (a == NULL){
        return 0;
    }
    else if (!estVide(a->left)){
        return 1;
    }
    else{
        return 0;
    }
}
int existeFilsDroit(pArbre a){
    if (a == NULL){
        return 0;
    }
    else if (!estVide(a->right)){
        return 1;
    }
    else{
        return 0;
    }
}
pArbre ajouteFilsGauche(pArbre a){
    if ( !existeFilsGauche(a)){
        a->left = creationFeuille(rand()%30);
    }
    return a;
}
pArbre ajouteFilsDroite(pArbre a){
    if ( !existeFilsGauche(a)){
        a->right = creationFeuille(rand()%30);
    }
    return a;
}
void traiter(pArbre a){
    printf("%d ->",a->nb);
}
void parcoursPrefixe(pArbre a){
    if(a != NULL){
        traiter(a);
        parcoursPrefixe(a->left);
        parcoursPrefixe(a->right);}
}
void parcoursPostfixe(pArbre a){
    if ( a!= NULL){
        parcoursPostfixe(a->left);
        parcoursPostfixe(a->right);
        traiter(a);}
}
void parcoursLargeur(pArbre a){
    if (a !=NULL){
        pFile f = creerFile();
        enfiler(f,a);
        while ( ! fileVide(f)){
            pArbre a = defiler(f);
            traiter (a);
            if ( existeFilsGauche(a)){
                enfiler(f,a->left);
            }
            if (existeFilsDroit(a)){
                enfiler(f,a->right);
            }
        }
        free(f);
    }
}
void affichage(pArbre a){
    printf("\nVoici le parcours prefixe :\n");
    parcoursPrefixe(a);
    printf("\nVoici le parcours postfixe :\n");
    parcoursPostfixe(a);
    printf("\nVoici le parcours Largeur :\n");
    parcoursLargeur(a);
}
pArbre modifierRacine(pArbre a, int e){
    a->nb = e;
    return a;
}
void supprimerFilsGauche(pArbre a);
void supprimerFilsDroit(pArbre a);
void supprimerFilsDroit(pArbre a){
    if (a == NULL){exit(2);}
    else if ( existeFilsDroit(a)){
        if (existeFilsGauche(a->right)){
            supprimerFilsGauche(a->right);
        }
        if (existeFilsDroit(a->right)){
            supprimerFilsDroit(a->right);
        }
        a->right = NULL;
        free(a->right);
    }
}
void supprimerFilsGauche(pArbre a){
    if (a== NULL){exit(3);}
    else if (existeFilsGauche(a)){
        if(existeFilsGauche(a->left)){
            supprimerFilsGauche(a->left);
        }
        if (existeFilsDroit(a->left)){
            supprimerFilsDroit(a->left);
        }
        a->left = NULL;
        free(a->left);
    }
}
int nbFeuille(pArbre a){
    if(a == NULL){
        return 0;
    }
    else if(estFeuille(a)){
        return 1;
    }
    return nbFeuille(a->left) + nbFeuille(a->right);
}
int main(){
    srand(time(NULL));
    pArbre a = NULL;
    pArbre b = NULL;
    b = creationFeuille(rand()%30);
    b= ajouteFilsDroite(b);
    b= ajouteFilsGauche(b);
    a= creationArbre(a);
    affichage(a);
    affichage(b);
    supprimerFilsDroit(b);
    supprimerFilsGauche(b);
    affichage(b);
    printf("\nIl y a %d feuilles dans cet arbre\n",nbFeuille(b));
    printf("\nIl y a %d feuilles dans cet arbre\n",nbFeuille(a));
    return 0;
}