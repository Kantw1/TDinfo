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
int estFeuille(pArbre a){
    if (a->left == NULL && a->right == NULL){
        return 1;
    }
    else{
        return 0;}
}
int estVide(pArbre a){
    if(a == NULL){
        return 1;
    }
    else {
        return 0;}
}
int element(pArbre a){
    return a->num;
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
pArbre ajouterFilsGauche(pArbre a, int e){
    pArbre b = a;
    if( existFilsGauche(b) == 1){
        printf("Il y a deja un fils gauche\n");}
    else {
        b->left = creerArbre(e);}
        return b;
}
pArbre ajouterFilsDroite(pArbre a, int e){
    pArbre b = a;
    if( existFilsDroite(b) == 1){
        printf("Il y a deja un fils droit\n");}
    else {
        b->right = creerArbre(e);}
        return b;
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
void parcoursPostfixe(pArbre a){
    if ( a !=NULL){
        parcoursPostfixe(a->left);
        parcoursPostfixe(a->right);
        traiter(a); }
}

pArbre modifierRacine(pArbre a, int e){
    a->num = e;
    return a;
}
void supprimerFilsGauche(pArbre a);

void supprimerFilsDroite(pArbre a){
    if (a == NULL){
    exit(1);
    }
    else if(existFilsDroite(a) == 1){
        if( existFilsGauche(a->right) == 1){
            supprimerFilsGauche(a->right);
        }
        else if( existFilsDroite(a->right) == 1){
            supprimerFilsDroite(a->right);
    }
    a->right = NULL;
    free(a->right);
    }
}

void supprimerFilsGauche(pArbre a){
    if (a ==NULL){
        exit(1);
    }
    else if(existFilsGauche(a)){
        if (existFilsGauche(a->left)){
            supprimerFilsGauche(a->left);
        }
        else if(existFilsDroite(a->left)){
            supprimerFilsDroite(a->left);
        }
        a->left =NULL;
        free(a->left);
    }
}

void nombreFeuille(pArbre a, int * pa){
    if ( a !=NULL){
        nombreFeuille(a->left, pa);
        nombreFeuille(a->right,pa);
        if (estFeuille(a) == 1){
            *pa += 1;
        }
    }
}

void tailleArbre(pArbre a, int * pc){
    if ( a !=NULL){
        tailleArbre(a->left, pc);
        tailleArbre(a->right,pc);
        if (estFeuille(a) != 1){
            *pc += 1;
        }
    }
}

int hauteurArbre(pArbre a){

    if( a ==NULL || (a->left == NULL && a->right == NULL)){
        return 0;}
    else{
        int hauteurGauche = hauteurArbre(a->left);
        int hauteurDroite = hauteurArbre(a->right);
        if ( hauteurDroite > hauteurGauche){
            return 1 + hauteurDroite;
        }
        else {
            return 1 + hauteurGauche;
        }
    }
}

int main(){
    pArbre a = NULL;
    a = creerArbre(1);
    a = ajouterFilsGauche(a,2);
    a->left = ajouterFilsGauche(a->left,3);
    a->left->left = ajouterFilsGauche(a->left->left,4);
    a->left->left = ajouterFilsDroite(a->left->left,5);
    a->left= ajouterFilsDroite(a->left,6);
    a->left->right = ajouterFilsDroite(a->left->right,7);
    a = ajouterFilsDroite(a,8);
    a->right = ajouterFilsGauche(a->right,9);
    a->right = ajouterFilsDroite(a->right,10);

    parcoursPrefixe(a);
    printf("\n");
    parcoursPostfixe(a);
    printf("\n");
    supprimerFilsGauche(a->left);
    parcoursPrefixe(a);
    printf("\n");
    supprimerFilsDroite(a);
    parcoursPrefixe(a);

    int b = 0;
    int * pa = &b;
    nombreFeuille(a,pa);
    printf("\n");
    printf("%d\n",b);
    int c = 0;
    int * pc = &c;
    tailleArbre(a,pc);
    printf("%d\n",c);
    printf("%d\n",hauteurArbre(a));
    a = modifierRacine(a, 15);
    parcoursPrefixe(a);

    return 0;
}
