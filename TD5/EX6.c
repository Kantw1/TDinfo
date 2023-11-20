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
    //Creation d'un chainon avec une valeur aléatoire
    pFile a = malloc(sizeof(File));
    if(a==NULL){
        exit (1);
    }
    a->num = rand()%100;
    a->next = NULL;
    return a;
}
pFile ajoutChainon(pFile a){
    //ajout d'un chainon en fin de liste
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
    //Creation d'une file avec un nombre aléatoire de valeur
    int nb = 10+rand()%20;
    printf("Le tableau aura %d elements\n",nb);
    for( int i = 0; i < nb; i++){
        a = ajoutChainon(a);
    }
    return a;
}
void afficheFile ( pFile a ){
    //affichage de la file
    if (a ==NULL){exit(1);}
    printf("Voici la File : ");
    while( a!=NULL){
        printf("%d ->",a->num);
        a = a->next;
    }
    printf("\n");
}
pABR creationFeuille(int nombre){
    //creation d'une feuille pour un arbre
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
    //ajout de la feuille en respectant les regle ABR
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
    //recherche un nombre dans l'arbre
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
        return recherche(nombre,b->right);
    }
    
}
pABR creationGrandABR(pFile a, pABR b){
    //creation de l'ABR
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
    // affiche la valeur de l'arbre
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
void parcoursPostfixe(pABR b){
    if ( b !=NULL){
        parcoursPostfixe(b->left);
        parcoursPostfixe(b->right);
        traiter(b);
    }
}
void affichageABR(pABR b){
    printf("\nVoici l'Arbre affhiche de differente maniere : \n");
    printf("Voici le parcours infixe : ");
    parcoursInfixe(b);
    printf("\nVoici le parcours prefixe : ");
    parcoursPrefixe(b);
    printf("\nVoici le parcours postfixe : ");
    parcoursPostfixe(b);
    printf("\n");
}
pABR inserFeuille(pABR b){
    //ajoute une nouvelle feuille en respectant les règles des ABR
    int nombre;
    printf("\nQuel nombre voulez vous ajouter ?\n");
    scanf("%d",&nombre);
    if(recherche(nombre,b) != 1){
            b = creationArbre(nombre,b);
        }
    return b;
}
int existFilsGauche(pABR b){
    // vérifie s'il existe un fils gauche
    if (b->left != NULL){
        return 1;
    }
    else{
        return 0;}
}
int existFilsDroite(pABR b){
    // vérifie s'il existe un fils droit
    if (b->right != NULL){
        return 1;
    }
    else{
        return 0;}
    }
pABR suppMax(pABR b, int * pe){
    //échange la valeur du noeud supprimer avec le fils droit le plus grand de son fils gauche
    pABR tmp = b;

    if(existFilsDroite(b) == 1){
        b->right = suppMax(b->right,pe);
    }
    else{
        *pe = b->valeur;
        tmp = b;
        b = b->left;
        free(tmp);
    }
    return b;
}
pABR suppression(pABR b,int e){
    //supprime une valeur
    pABR tmp = b;
    if (b == NULL){
        return b;
    }
    else if(e> b->valeur){
        b->right = suppression(b->right,e);
    }
    else if (e < b->valeur){
        b->left = suppression(b->left,e);
    }
    else if( existFilsGauche(b) != 1){
        tmp = b;
        b = b->right;
        free(tmp);
    }
    else {
        b->left = suppMax(b->left, &(b->valeur));
    }
    return b;
}
pABR suppressionNombre(pABR b){
    //supprime une valeur si elle existe dans l'arbre
    int nombre;
    printf("\nQuel nombre voulez vous supprimer de l'arbre ?\n");
    scanf("%d",&nombre);
    if ( recherche(nombre,b) == 0){
        printf("Ce nombre n'existe pas, essayez encore !");
        b = suppressionNombre(b);
    }
    else {
        b = suppression(b,nombre);
    }
    return b;

}
pABR ajoutFeuille(int nb, pABR c){
    int var = rand()%10;
    if( c ==NULL){
        return creationFeuille(nb);
    }
    else if(var%2 == 0){
        c->left = ajoutFeuille(nb, c->left);            
        }
    else{
        c->right = ajoutFeuille(nb, c->right);
        }
    return c;
}
pABR creationArbre2(pABR c, pFile a){
   pFile p1 = a;
    if ( p1 == NULL){
        printf("il n'y a pas de valeur dans la liste\n");
        exit(3);
    }
    while (p1 != NULL){
        if(recherche(p1->num,c) != 1){
            c = ajoutFeuille(p1->num,c);
        }
        p1 = p1->next;
    }
    return c;
}
int minABR ( pABR b){
    if ( b == NULL){
        exit(7);
    }
    if (existFilsGauche(b)==1){
        return minABR(b->left);
    }
    else {
        return b->valeur;
    }
}
int maxABR ( pABR b){
    if ( b == NULL){
        exit(7);
    }
    if (existFilsDroite(b)==1){
        return maxABR(b->right);
    }
    else {
        return b->valeur;
    }
}
int estABR(pABR d, int min, int max) {
    if (d == NULL) {
        return 1;
    }

    // Vérifie si la valeur du nœud courant est dans la plage autorisée
    if (d->valeur < min || d->valeur > max) {
        return 0;  // La valeur du nœud est en dehors de la plage autorisée pour un ABR
    }

    // Appelle récursivement la fonction pour le sous-arbre gauche avec une nouvelle plage
    // autorisée allant de min à la valeur du nœud - 1
    // et appelle récursivement la fonction pour le sous-arbre droit avec une nouvelle plage
    // autorisée allant de la valeur du nœud + 1 à max
    return estABR(d->left, min, d->valeur - 1) && estABR(d->right, d->valeur + 1, max);
}
void verificationABR(pABR d){
    if (estABR(d,minABR(d),maxABR(d))==1){
        printf("C'est un ABR\n");
    }
    else{
        printf("Ce n'est pas un ABR\n");
    }
}
pABR constructionNouveauABR(pABR c, pABR f){
    if ( c ==NULL){
        return f;
    }
    f = creationArbre(c->valeur,f);
    f = constructionNouveauABR(c->left,f);
    f = constructionNouveauABR(c->right,f);
    return f;
}
int main(){
    srand(time(NULL));
    pFile a = NULL;
    pABR b = NULL;
    pABR c = NULL;
    pABR f = NULL;
    a = creationFile(a);
    afficheFile(a);
    b = creationGrandABR(a,b);
    affichageABR(b);
    verificationABR(b);
    c = creationArbre2(c,a);
    affichageABR(c);
    verificationABR(c);
    f = constructionNouveauABR(c,f);
    affichageABR(f);
    verificationABR(f);
    /*b = inserFeuille(b);
    affichageABR(b);
    suppressionNombre(b);
    affichageABR(b);*/
    return 0;
}
