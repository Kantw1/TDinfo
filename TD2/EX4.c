#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct chainon{

char car;
struct chainon * next;
}Chainon;

Chainon * creationChainon(){

    Chainon * c = malloc(sizeof(Chainon));
    int truc = rand()%12;
    if(c==NULL){
        exit (1);
    }
    if(truc == 1 || truc == 2){
    if (truc == 1){
    c->car = '(';
    }
    else {
    c->car = ')';
    }
    }
    else{
    c->car = 'a' + rand()%24+1;
    }
    c->next = NULL;
    return c;
}

Chainon* insertFin(Chainon * pliste){
    Chainon *nouveau = creationChainon();
    Chainon *p1 = pliste;
    while(p1->next != NULL){
        p1=p1->next;
    }
    p1->next = nouveau;
    return pliste;
}

Chainon * queue(Chainon * pliste, int nb){

    Chainon * p1 = pliste;
    int info = 0;
    if(nb > 0){

        for(int i = 0 ; i< nb; i++){
            if (info ==0){

                p1 = creationChainon();
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

void afficheFil(Chainon * pliste){

    Chainon * p1 = pliste;
    if (pliste == NULL){
        printf("y");
        exit(2);
    }
    while(p1 != NULL){

        printf("%c " , p1->car);
        p1 = p1->next;
    }
    printf("\n");

}

void controle(Chainon * pliste){

int info1 = 0;
int info2 = 0;
int info3 = 0;
Chainon * p1 = pliste;

while(p1->next != NULL){


if (p1->car == '('){
info1 ++;
}
else if ( p1->car == ')'){
info2 ++;

}
if (info2 > info1){
info3 ++;
}
        p1=p1->next;
    }
if( info3 != 0){

printf("Pas bien parenthese\n");
}
else {
printf("bien perenthese\n");
}
}

int main(){

Chainon * pliste = NULL;
int nombre = 0 ;
srand(time(NULL));
printf("rentrez la taille de la fil\n");
scanf("%d",&nombre);
pliste = queue(pliste,nombre);
afficheFil(pliste);

controle(pliste);

return 0 ;
}