#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct chainon{

    int data;
    struct chainon * next;
}Chainon;

Chainon * creationChainon(){
    Chainon * c = malloc(sizeof(Chainon));
    if (c == NULL){
        exit(1);
    }
    c->data = rand()%5;
    c->next = NULL;
}

Chainon * ajoutChainon(Chainon * plist){
    Chainon * p1 = plist;
    Chainon * nouvau = creationChainon();
    if (plist == NULL){
        exit(2);
    }
    while (p1->next!=NULL){
        p1 = p1->next;
    }
    p1->next = nouvau;
    return plist;
}
Chainon * creationListe(Chainon * plist){
    Chainon * p1;
    plist = creationChainon();
    p1 = plist;
    int N;
    printf("Combien de chainon voulez vous?\n");
    scanf("%d",&N);
    for (int i= 0; i<N-1; i++){
        p1 = ajoutChainon(p1);
    }
    return plist;    
}
Chainon * suppChainon(Chainon * plist){
    Chainon * p1 = plist;
    Chainon * inter;
    int supp = rand()%5;
    printf("\nTous les %d vont etre supprime\n",supp);
    while(p1!=NULL && p1->data == supp){
        inter = p1;
        p1 = p1->next;
        free(inter);
    }
    plist = p1;
    while(p1!=NULL && p1->next != NULL){
        if(p1->next->data == supp){
            inter = p1->next;
            p1->next = p1->next->next;
            free(inter);
        }
        else{
            p1 = p1->next;
        }
    }
    return plist;
}
void afficheList(Chainon * plist){
    Chainon * p1 = plist;
    while(p1!=NULL){
        printf("%d -> ",p1->data);
        p1 = p1->next;
    }
}
int main(){
    srand(time(NULL));
    Chainon * plist =NULL;
    plist = creationListe(plist);
    afficheList(plist);
    plist =suppChainon(plist);
    afficheList(plist);
    return 0;
}