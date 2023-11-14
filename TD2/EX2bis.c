#include <stdlib.h>
#include <stdio.h>

typedef struct Chainon{
    int nb;
    struct Chainon * next;
}Chainon;
typedef struct Pile{
    Chainon * tete;
}Pile;

typedef Chainon * pchainon;
typedef Pile * ppile;

pchainon creationChainon(int a){
    pchainon c = malloc(sizeof(Chainon));
    c->next = NULL;
    c->nb = a;
    return c;
}

ppile creationPile(ppile plist, int a){
    if (plist->tete ==NULL){
        plist->tete = creationChainon(a);
        return plist;
    }
    pchainon nouveau= creationChainon(a);
    pchainon inter = plist->tete;
    plist->tete = nouveau;
    plist->tete->next = inter;
    return plist;
}
void affichePile(ppile plist){
    pchainon p1 = plist->tete;
    while(p1 != NULL){
        printf("%d -> ", p1->nb);
        p1 = p1->next;
    }
    printf("\n");
}
ppile depile(ppile plist, int *pnmb){
    *pnmb = plist->tete->nb;
    if(plist->tete == NULL){
        return plist;
    }
    pchainon p1 = plist->tete;
    plist->tete = p1->next;
    free(p1);
    return plist;
}
int main(){
    int nombre;
    int * pnmb = &nombre;
    ppile plist = malloc(sizeof(Pile));
    plist->tete = NULL;
    ppile pair = malloc(sizeof(Pile));
    pair->tete = NULL;
    ppile impair = malloc(sizeof(Pile));
    impair->tete = NULL;
    for (int i = 20; i>0; i--){
        plist = creationPile(plist,i);
    }
    affichePile(plist);
    while (plist->tete!=NULL){
        plist = depile(plist,pnmb);
        if(*pnmb%2==0){
            pair = creationPile(pair,*pnmb);
        }
        else{
            impair = creationPile(impair,*pnmb);
        }
    }
    affichePile(pair);
    affichePile(impair);
    return 0;
}