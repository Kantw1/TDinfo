#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Client{

    int article;
    struct Client * next;
}Client;

typedef struct FileClient{
    Client * debut;
    Client * fin;
}FileClient;

typedef Client * Pclient;
typedef FileClient * Pfile;

Pclient creationClient(){
    Pclient c = malloc(sizeof(Client));
    c->article = rand()%50+1;
    c->next = NULL;
    return c;
}
void afficheFil(Pfile plist){
    Pclient p1 = plist->debut;
    while(p1 != NULL){
        printf("%d -> ",p1->article);
        p1 = p1->next;
    }
    printf("\n");
}
Pfile creationFile(Pfile plist){
    if (plist->fin == NULL){
        plist->fin = creationClient();
        plist->debut = plist->fin;
    }
    else{

        plist->fin->next = creationClient();
        plist->fin = plist->fin->next;
        return plist;
    }
}
Pfile suppFile(Pfile plist){
    if (plist->debut->next == NULL){
        free(plist->debut);
        free(plist->fin);
        return NULL;
    }
    Pclient p1 = plist->debut;
    plist->debut = plist->debut->next;
    free(p1);
    return plist;
}
int main(){
    srand(time(NULL));
    Pfile plist = malloc(sizeof(FileClient));
    plist->debut = NULL;
    plist->fin = NULL;
    int a = rand()%20 + 10;
    for (int i = 0; i< a; i++){
        plist = creationFile(plist);
    }
    afficheFil(plist);
    while(plist->debut != NULL){
        plist = suppFile(plist);
        if( rand()%3 == 0){
            for (int a = 0;  a<rand()%3; a++){
                plist = creationFile(plist);
            }
        }
        afficheFil(plist);
    }
    return 0;
}