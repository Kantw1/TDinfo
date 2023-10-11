#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct chainon{

    int article;
    struct chainon * next;
}Client;

Client * creationclient(){

    Client * c = malloc(sizeof(Client));
    if(c==NULL){
        exit (1);
    }
    
    c->article = rand()%50+1;
    c->next = NULL;
    return c;
}

Client * creationclientpay(int a){

    Client * c = malloc(sizeof(Client));
    if(c==NULL){
        exit (1);
    }
    
    c->article = a;
    c->next = NULL;
    return c;
}

Client* insertFin(Client * pliste){
    Client *nouveau = creationclient();
    Client *p1 = pliste;
    while(p1->next != NULL){
        p1=p1->next;
    }
    p1->next = nouveau;
    return pliste;
}

Client* insertFinpay(Client * pliste, int a){
    Client *nouveau = creationclientpay(a);
    Client *p1 = pliste;
    while(p1->next != NULL){
        p1=p1->next;
    }
    p1->next = nouveau;
    return pliste;
}

Client * queue(Client * pliste, int nb){

    Client * p1 = pliste;
    int info = 0;
    if(nb > 0){

        for(int i = 0 ; i< nb; i++){
            if (info ==0){

                p1 = creationclient();
                info = 1;
            }
            else{
                p1 = insertFin(p1);
            }
        }

    }
    else {
        exit(1);
    }
    return p1;
}

Client * queuepayed(Client * pliste, int * clientpayed, int * info ){

    Client * p2 = pliste;
    if(*info ==0){
        p2 = creationclientpay(*clientpayed);
        *info =1;
    }
    else{
    p2 = insertFinpay(p2,*clientpayed);
    }

    return pliste;
}

Client * nouveauClient(Client * pliste){

    if (pliste == NULL){
        exit(1);
    }
    Client * p1 = pliste;
    p1 = insertFin(p1);
    return p1;
}

Client * suppClient(Client * pliste, int *clientpayed){

    if (pliste == NULL){
        exit(1);
    }
    Client *p1 = pliste;
    //printf("supp %d\n", p1->article);
    *clientpayed = p1->article;
    pliste = p1->next;
    free(p1);
    return pliste;
}

void afficheFil(Client * pliste){

    Client * p1 = pliste;
    if (pliste == NULL){
        printf("y");
        exit(2);
    }
    while(p1 != NULL){

        printf("%d-> " , p1->article);
        p1 = p1->next;
    }
    printf("\n");

}

Client * simulator(Client * pliste, Client * payed,int *clientpayed){

    Client * p1 = pliste;
    Client * p2 = payed;
    int random;

    for( int i = 0; i<3; i++){

        p1 = insertFin(p1);
    }

    p1 = suppClient(p1, clientpayed);
    p2 = creationclientpay(*clientpayed);

    while (p1 != NULL){

        afficheFil(p1);
        //afficheFil(p2);
        p1 = suppClient(p1, clientpayed);
        p2 = insertFinpay(p2,*clientpayed);
        random = rand()%3;
        if(random == 1){
            p1 = insertFin(p1);
        }
    }
    return p2;
}

int main(){

    int clientpayed = 0;
    int * pass = &clientpayed;
    Client * pliste = NULL;
    Client * payed = NULL;
    int nombre;
    srand(time(NULL));

    printf("rentrez la taille de la fil\n");
    scanf("%d",&nombre);
    pliste = queue(pliste,nombre);
    afficheFil(pliste);
    payed = simulator(pliste,payed, &clientpayed);
    printf("Voici tous les cients passes\n");
    afficheFil(payed);

    return 0;
}
