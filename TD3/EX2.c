#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Pour utiliser les fonctions de manipulation de chaînes
#include <time.h>
#define size 20

typedef struct chainon{

struct chainon * next;
    int diam;
    }Crepe;

typedef Crepe * Pcrepe;
void afficheList(Pcrepe plist);
Pcrepe creationCrepe(){
    Pcrepe c = malloc(sizeof(Crepe));
    if (c ==NULL){
        exit(1);
    }
    c->diam = rand()%10;
    c->next = NULL;
    return c;
}
Pcrepe inserFil(Pcrepe plist, Pcrepe nouveau){
    if( plist == NULL){
        plist = nouveau;
        return plist;
    }

    Pcrepe p1 = plist;

    while ( p1->next != NULL){
        p1 = p1->next;
        }
    p1->next = nouveau;
    return plist;
}
Pcrepe suppFil(Pcrepe  plist){

    if( plist ==NULL){
        exit(1);
    }
    if(plist->next==NULL){
        free(plist);
        return NULL;
    }
    Pcrepe p1 = plist;
    Pcrepe inter = NULL;
    inter = p1;
    p1 = p1->next;;
    free(inter);

    return plist;
}
Pcrepe inserPil(Pcrepe plist){

    if( plist == NULL){
        plist = creationCrepe();
        return plist;
    }

    Pcrepe nouveau = creationCrepe();
    Pcrepe inter = NULL;


    inter = plist;
    plist = nouveau;
    plist->next = inter;

    return plist;
}
Pcrepe suppPil(Pcrepe plist) {
    if (plist == NULL) {
        exit(1);
    }

    Pcrepe p1 = plist;
    plist = p1->next; // Met à jour la tête de la pile
    free(p1);

    return plist;
}
Pcrepe premierChainon(Pcrepe plist){
    Pcrepe p1 = plist;
    p1->next = NULL;
    return p1;
}
void afficheList(Pcrepe plist){
    if(plist == NULL){
        exit(2);
    }
    while(plist !=NULL){
        printf("%d -> ",plist->diam);
        plist = plist->next;
    }
    printf("\n");
}
int triCrepe (Pcrepe plist){
    Pcrepe p1 = plist;
    while(p1->next!=NULL){
        if(p1->diam > p1->next->diam){
            return 0;
        }
        p1 = p1->next;
    }
    return 1;
}
Pcrepe invCrepe(Pcrepe plist, int M){
    Pcrepe p2 = NULL;    
    for (int i = 0; i<M; i++){
        afficheList(premierChainon(plist));
        p2 = inserFil(p2,creationCrepe());
        afficheList(p2);
        //plist = suppPil(plist);
        printf("cacacacacacacac");
    }
    exit(1);
    //plist = inserFil(plist,p2);
    return p2;
}
int main(){
    srand(time(NULL));
    Pcrepe plist = NULL;
    int nombre;
    printf("Combien de crepes voulez vous?\n");
    scanf("%d",&nombre);
    for (int i = 0; i<nombre; i++){
        plist = inserPil(plist);
    }
    afficheList(plist);
    printf("%d\n",triCrepe(plist));
    //plist = inserFil(plist,creationCrepe());
    //afficheList(plist);
    
    plist = invCrepe(plist,5);
    //afficheList(plist);
    return 0;
}

RIEN COMPRIS