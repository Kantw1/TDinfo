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
    if (a != NULL){
        traiter(a);
        parcoursPrefixe(a->left);
        parcoursPrefixe(a->right);
    }
}
int min(pArbre a){
    if (existFilsGauche(a)){
        return min(a->left);
    }
    else{
        return a->num;
    }
}
int max(pArbre a){
    if(existFilsDroite(a)){
        return max(a->right);
    }
    else {
        return a->num;
    }
}
int estABR(pArbre a,int min, int max){
    if(a == NULL){
        return 1;
    }
    if(a->num< min || a->num > max){
        return 0;
    }
    return estABR(a->left,min,a->num -1) && estABR(a->right,a->num + 1, max);
}
void ABR(pArbre a){
    if(estABR(a,min(a),max(a))){
        printf("C'est un ABR\n");
    }
    else{
        printf("Ce n'est pas un ABR\n");
    }
}
pArbre supprimerFilsGauche(pArbre a);
pArbre supprimerFilsDroite(pArbre a){
    if (a == NULL){
        return a;
    }
    else if (existFilsDroite(a)){
        if(existFilsGauche(a->right)){
            a->left = supprimerFilsGauche(a->left);
        }   
        else if (existFilsDroite(a->right)){
            a->right = supprimerFilsDroite(a->right);
        }
        a->right = NULL;
        free(a->right);
        return a;
    }
}
pArbre supprimerFilsGauche(pArbre a){
    if (a == NULL){
        return a;
    }
    else if (existFilsGauche(a)){
        if(existFilsGauche(a->left)){
            a->left = supprimerFilsGauche(a->left);
        }   
        else if (existFilsDroite(a->left)){
            a->right = supprimerFilsDroite(a->right);
        }
        a->left = NULL;
        free(a->left);
        return a;
    }
}
int main(){
    pArbre a = NULL;
    a = creerArbre(11);
    a = ajouterFilsGauche(a,8);
    a->left = ajouterFilsGauche(a->left,6);
    a->left->left = ajouterFilsGauche(a->left->left,4);
    a->left->left = ajouterFilsDroite(a->left->left,7);
    a->left= ajouterFilsDroite(a->left,9);
    a->left->right = ajouterFilsDroite(a->left->right,10);
    a = ajouterFilsDroite(a,14);
    a->right = ajouterFilsGauche(a->right,13);
    a->right = ajouterFilsDroite(a->right,20);

    parcoursPrefixe(a);
    printf("\n");
    ABR(a);
    a = supprimerFilsGauche(a);
    parcoursPrefixe(a);
    return 0;
}