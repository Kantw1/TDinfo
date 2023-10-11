#include <stdio.h>
#include <stdlib.h>

typedef struct chainon{

int valeur;
struct chainon * next;

}Chainon;

Chainon * creationChainon(int a){

Chainon * c = malloc(sizeof(Chainon));
if(c==NULL){
exit (1);
}
c->valeur = a;
c->next = NULL;
return c;
}

Chainon * insertDebut(Chainon* pliste, int a){

Chainon* nouveau = creationChainon(a);
nouveau->next = pliste;

pliste = nouveau;

return pliste;

}

Chainon* insertFin(Chainon * pliste, int a){
Chainon *nouveau = creationChainon(a);
Chainon *p1 = pliste;
while(p1->next != NULL){
p1=p1->next;
}
p1->next = nouveau;
return pliste;
}

void afficheListe(Chainon*pliste){

Chainon* nouveau;
Chainon* p1;
if (pliste == NULL){

exit(4);
}

p1 = pliste;
while (p1->next != NULL){

printf("%d-> " , p1->valeur);
p1 = p1->next;
}

}


void inserChainon(int b, Chainon * pliste){

Chainon * p1 = pliste;
Chainon *nouveau = creationChainon(b);
Chainon * inter = creationChainon(b);
int info = 0;
printf("vous avez choisi %d\n",b);
while (p1->next != NULL&& info != 1){
if(((p1->next)->valeur) >= b){
inter->next = p1->next;
p1->next = nouveau;
nouveau->next = inter->next;
info = 1;
}

p1=p1->next;
}

afficheListe(pliste);

}

int main(){
Chainon* pliste = NULL;
int n;
int a = 1;
int b;
printf("Taille\n");
scanf("%d",&n);
pliste = creationChainon(a);

for( int i =1; i<=n; i++){
a = 2*a;
pliste =insertFin(pliste,a);
}
afficheListe(pliste);

printf("\nchoisir un nouveau nombre\n");
scanf(" %d",&b);
inserChainon(b, pliste);

printf("\n");

return 0;

}