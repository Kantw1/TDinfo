#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Arbre{
    int nb;
    struct Arbre * left;
    struct Arbre * right;
}Arbre;
typedef Arbre * pArbre;

pArbre creerArbre(int nombre){
    pArbre a = malloc(sizeof(Arbre));
    a->left = NULL;
    a->right = NULL;
    a->nb = nombre;
    return a;
}
pArbre ajouterFeuille(pArbre a, int nombre){
    if( a==NULL){
        return creerArbre(nombre);
    }
    else if(nombre < a->nb){
        a->left = ajouterFeuille(a->left,nombre);
    }
    else if (nombre > a->nb){
        a->right = ajouterFeuille(a->right,nombre);
    }
    return a;
}
pArbre creationArbre(pArbre a){
    for(int i=0; i<10;i++){
        a = ajouterFeuille(a,rand()%50);
    }
    return a;
}
int existFilsGauche(pArbre a){
    if (a->left == NULL){
        return 0;
    }
    else{
        return 1;
    }
}
int existFilsDroit(pArbre a){
    if (a->right == NULL){
        return 0;
    }
    else{
        return 1;
    }
}
int recherche(pArbre a, int nombre){
    if (a==NULL){
        return 0;
    }
    else if(a->nb == nombre){
        return 1;
    }
    else if (nombre < a->nb){
        return recherche(a->left,nombre);
    }
    else{
        return recherche(a->right,nombre);
    }
}
pArbre suppMax(pArbre a, int * pe){
    pArbre tmp = a;
    if (existFilsDroit(a)){
        a->right = suppMax(a->right,pe);
    }
    else {
        *pe = a->nb;
        tmp = a;
        a = a->left;
        free(tmp);
    }
    return a;
}
pArbre suppression(pArbre a, int nombre){
    pArbre tmp = a;
    if (a == NULL){
        return a;
    }
    else if (nombre < a->nb){
        a->left = suppression(a->left,nombre);
    }
    else if (nombre > a->nb){
        a->right = suppression(a->right,nombre);
    }
    else if (!existFilsGauche(a)){
        tmp = a;
        a = a->right;
        free(tmp);
    }
    else{
        a->left = suppMax(a->left,&(a->nb));
    }
    return a;
}
pArbre supprimeNombre(pArbre a){
    int nombre;
    printf("Quel nombre Voulez vous supprimer ?\n");
    scanf("%d",&nombre);
    if(!recherche(a,nombre)){
        return supprimeNombre(a);
    }
    else{
        return suppression(a,nombre);
    }
    return a;
}
void traiter(pArbre a){
    printf("%d ->",a->nb);
}
void affichePrefixe(pArbre a){
    if (a != NULL){
        traiter(a);
        affichePrefixe(a->left);
        affichePrefixe(a->right);
    }
}
void affichage(pArbre a){
    printf("voici l'affichage :\n");
    affichePrefixe(a);
    printf("\n");
}
int estFeuille(pArbre a){
    if (a->left == NULL && a->right == NULL && a != NULL){
        return 1;
    }
    else {return 0 ;}
}
int nbFeuilles(pArbre a){
    if(a != NULL){
        if(estFeuille(a)){
            return 1;
        }
        return nbFeuilles(a->left) + nbFeuilles(a->right);
    }
    return 0;
}
int tailleArbre(pArbre a){
    if(a!= NULL){
        if(!estFeuille(a)){
            return tailleArbre(a->left) + tailleArbre(a->right) + 1;
        }
    }
    return 0;
}
int profondeurArbre(pArbre a){
    if( a!= NULL){
        int hauteurGauche = profondeurArbre(a->left);
        int hauteurDroite = profondeurArbre(a->right);
        if(hauteurDroite>hauteurGauche){
            return hauteurDroite + 1;
        }
        else {
            return hauteurGauche + 1;
        }
    }
}
void informations(pArbre a){
    printf("Il y a %d feuilles\n", nbFeuilles(a));
    printf("La taille de l'arbre est de %d\n",tailleArbre(a));
    printf("La profondeur de l'arbre est de %d\n",profondeurArbre(a));
}
int main(){
    srand(time(NULL));
    pArbre a = NULL;
    a = creationArbre(a);
    affichage(a);
    informations(a);
    a = supprimeNombre(a);
    affichage(a);
    informations(a);
    return 0;
}