#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct chainon{
    int num;
    struct chainon * next;
}PileDyn;

PileDyn * creationPileDyn(int nb){
    PileDyn * c = malloc(sizeof(PileDyn));
    if (c ==NULL){
        exit(1);
    }
    c->num = nb;
    c->next = NULL;
}
PileDyn * empiler(int nb, PileDyn * ppile){
    PileDyn * p1 = ppile;
    if (ppile == NULL){
        exit(2);
    }
    while(p1->next != NULL){
        p1 = p1->next;
    }
    p1->next = creationPileDyn(nb);
    return ppile;
}
PileDyn * creationPile(PileDyn * ppile){
    int i = 1;
    ppile = creationPileDyn(i);
    for (i=2;i<21; i++){
        ppile = empiler(i,ppile);
    }
    return ppile;
}
void affichePil(PileDyn * ppile){
    if (ppile ==NULL){
        exit(1);
    }
    PileDyn * p1 = ppile;
    while( p1!=NULL){
        printf("%d -> ",p1->num);
        p1 = p1->next;
    }
}
PileDyn* depile(PileDyn* ppile, int* pnmb) {
    if (ppile ==NULL){
        exit(1);
    }
    if (ppile->next == NULL){
        *pnmb = ppile->num;
        free(ppile);
        return NULL;
    }
    PileDyn * p1 = ppile;
    PileDyn * p2 = NULL;
    while(p1->next!=NULL){
        p2 = p1;
        p1 =p1->next;
    }
    *pnmb = p1->num;
    free(p1);
    p2->next = NULL;
    return ppile;
}
int main(){
    srand(time(NULL));
    PileDyn * ppile = NULL;
    PileDyn * pair = NULL;
    PileDyn * impair = NULL;
    int nombre;
    int pairverif = 0;
    int impairverif = 0;
    int * pnmb = &nombre;
    ppile = creationPile(ppile);
    affichePil(ppile);
    PileDyn * p1 = ppile;
    while(p1 != NULL){
        //printf("info");
        p1 = depile(p1,pnmb);
        if ( *pnmb%2 == 0){
            if(pairverif == 0){
                pair = creationPileDyn(*pnmb);
                pairverif =1;
            }
            else{
                pair = empiler(*pnmb,pair);
            }
        }
        else{
                if(impairverif == 0){
                    impair = creationPileDyn(*pnmb);
                    impairverif =1;
            }
                else{
                    impair = empiler(*pnmb,impair);
            }
        }
    }
    printf("\n");
    affichePil(pair);
    printf("\n");
    affichePil(impair);
    
    
    return 0;
}