#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct File{
    int num;
    struct File * next;
    }File;
typedef File * pFile;

typedef struct ABR{
    int valeur;
    struct ABR * left;
    struct ABR * right;
}ABR;
typedef ABR * pABR;

pFile creationChainon(){
    pFile a = malloc(sizeof(File));
    if(a==NULL){
        exit (1);
    }
    a->num = rand()%100;
    a->next = NULL;
    return a;
}
pFile ajoutChainon(pFile a){
    pFile p1 = a;
    pFile nouveau = creationChainon();
    if ( p1==NULL){
        return nouveau;
    }
    else{
        while ( p1->next != NULL){
            p1 = p1->next;
        }
    }
    p1->next = nouveau;
    return a;
}
pFile creationFile( pFile a){
    int nb = 10+rand()%20;
    printf("Le tableau aura %d elements\n",nb);
    for( int i = 0; i < nb; i++){
        a = ajoutChainon(a);
    }
    return a;
}
void afficheFile ( pFile a ){
    if (a ==NULL){exit(1);}
    printf("Voici la File : ");
    while( a!=NULL){
        printf("%d ->",a->num);
        a = a->next;
    }
    printf("\n");
}
pABR creationFeuille(int nombre){
    pABR b = malloc(sizeof(ABR));
    if (b==NULL){
        exit(2);
    }
    b->left = NULL;
    b->right = NULL;
    b->valeur = nombre;
    return b;
}
pABR creationArbre(int nombre, pABR b){
    if (b == NULL){
        return creationFeuille(nombre);
    }
    else if(nombre < b->valeur){
        b->left = creationArbre(nombre,b->left);
    }
    else if(nombre > b->valeur){
        b->right = creationArbre(nombre,b->right);
    }
    return b;
}
int recherche(int nombre, pABR b){
    if (b == NULL){
        return 0;
    }
    else if ( nombre == b->valeur){
        return 1;
    }
    else if ( nombre < b->valeur){
        return recherche(nombre,b->left);
    }
    else if ( nombre > b->valeur){
        return recherche(nombre,b->left);
    }
    
}
pABR creationGrandABR(pFile a, pABR b){
    pFile p1 = a;
    if ( p1 == NULL){
        printf("il n'y a pas de valeur dans la liste\n");
        exit(3);
    }
    while (p1 != NULL){
        if(recherche(p1->num,b) != 1){
            b = creationArbre(p1->num,b);
        }
        p1 = p1->next;
    }
    return b;
}
void traiter(pABR b){
    printf("%d ->", b->valeur);
}
void parcoursPrefixe(pABR b){
    if ( b !=NULL){
        traiter(b);
        parcoursPrefixe(b->left);
        parcoursPrefixe(b->right);
    }
}
void parcoursInfixe(pABR b){
    if ( b !=NULL){
        parcoursInfixe(b->left);
        traiter(b);
        parcoursInfixe(b->right);
    }
}
void affichageABR(pABR b){
    printf("Voici le parcours infixe : ");
    parcoursInfixe(b);
    printf("\nVoici le parcours prefixe : ");
    parcoursPrefixe(b);
}
int main(){
    srand(time(NULL));
    pFile a = NULL;
    pABR b = NULL;
    a = creationFile(a);
    afficheFile(a);
    b = creationGrandABR(a,b);
    affichageABR(b);
    return 0;
}
