#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct chainon{
    int num;
    struct chainon * Next;
}Chainon;
Chainon * creationChainon(){
    Chainon * c = malloc(sizeof(Chainon));
    if (c == NULL){
        exit(1);
    }
    c->Next = NULL;
    c->num = rand()%20;
}

Chainon * ajoutChainon(Chainon * plist){
    Chainon * p1 = plist;
    Chainon * nouveau = creationChainon();
    if (p1 == NULL){
        printf("La liste est vide.\n");
        exit(1);
    }
    while(p1->Next !=NULL){
        p1 = p1->Next;
    }
    p1->Next = nouveau;
    return plist;
}
Chainon * ListeChainon(Chainon * plist){
    int nombre;
    printf("Rentrez le nombre de chainon souhaitez\n");
    scanf("%d",&nombre);
    for (int i = 0; i< nombre-1; i++){
        plist = ajoutChainon(plist);
    }
    return plist;
}
void afficheChainon(Chainon * plist){
    Chainon * p1 = plist;
    if (plist == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    while(p1!= NULL){
        printf("%d -> ",p1->num);
        p1 = p1->Next;
    }
}
Chainon * inverseListe(Chainon * plist){
    Chainon* prev = NULL;
    Chainon* current = plist;
    Chainon* next = NULL;

    while (current != NULL) {
        next = current->Next;
        current->Next = prev;
        prev = current;
        current = next;
        printf("\n");
        afficheChainon(prev);
    }
    return prev;

}

int main(){

    srand(time(NULL));
    Chainon * plist = creationChainon();
    plist = ListeChainon(plist);
    afficheChainon(plist);
    plist = inverseListe(plist);
    printf("\nVoici la liste inverse :\n");
    afficheChainon(plist);
    return 0;
}