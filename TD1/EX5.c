#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define size 10

typedef struct chainon{

    char Nom[20];
    char Prenom[20];
    int Groupe;
    int note[size];
    struct chainon * Next;

}Etudiant;


char* nom() {
    int i = rand() % 10 + 1;
    char* nom = (char*)malloc(i + 1); // Allouer de la mémoire pour la chaîne et le caractère nul
    if (nom == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(1);
    }

    for (int j = 0; j < i; j++) {
        nom[j] = 'a' + rand() % 26; // Utilisez '26' pour obtenir des lettres de 'a' à 'z'
    }
    nom[i] = '\0'; // Ajoutez un caractère de fin de chaîne

    //printf("%s\n", nom);
    return nom; // Retournez un pointeur vers la chaîne allouée dynamiquement
}

Etudiant * creationEtudiant(){

    Etudiant * c = malloc(sizeof(Etudiant));

    if( c== NULL){

        exit(1);
    }

    c->Groupe = rand()%6+1;
    strcpy(c->Nom, nom());
    strcpy(c->Prenom, nom());
    
    for (int i = 0; i<size; i++){

        c->note[i] = rand()%20+1;
    }
    c->Next = NULL;
}

Etudiant * ajoutEtudiant(Etudiant * plist){

    Etudiant * p1 = plist;
    if (p1 == NULL){

        exit(2);
    }
    while (p1->Next != NULL){

        p1 = p1->Next;
    }
    p1->Next = creationEtudiant();

    return plist;
}

void afficheEtudiant(Etudiant * plist, int groupe){

    Etudiant * p1 = plist;

    if (plist == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    printf("\n\nvoici le groupe %d\n\n",groupe);
    while (p1 != NULL){

        if(p1->Groupe == groupe){
            printf("%s ",p1->Nom);
            printf("%s -> ",p1->Prenom);
        }
        p1 = p1->Next;
        
    }
    printf("\n");
}

float moyTab(int * tab){

    float moyenne = 0;
    for ( int i = 0; i <size; i++){

        moyenne += *(tab+i);
    }
    moyenne = moyenne/size;

    return moyenne;
}

Etudiant* trouveEtudiant(char* nom, char* prenom, Etudiant* plist) {
    Etudiant* p1 = plist;
    if (plist == NULL) {
        exit(1);
    }
    while (p1 != NULL) {
        if (strcmp(nom, p1->Nom) == 0 && strcmp(prenom, p1->Prenom) == 0) {
            return p1;
        }
        p1 = p1->Next;
    }
    return NULL;
}

float moyPromo(Etudiant * plist){
    Etudiant * p1 = plist;
    float note=0;
    int div =0;
    if (plist == NULL){
        exit(5);
    }
    while(p1 != NULL){
        note += moyTab(p1->note);
        div ++;
        p1 = p1->Next;
    }
    note = note/div;
    return note;
}

float plusMauvaiseMoy(Etudiant * plist){

    Etudiant * p1 = plist;
    float note=20;
    if (plist == NULL){
        exit(5);
    }
    while(p1 != NULL){
        if (note > moyTab(p1->note)){
            note = moyTab(p1->note);
        }
        p1 = p1->Next;
    }
    return note;
}

int main() {
    srand(time(NULL));
    int N;
    int groupe = 0;
    Etudiant* plist = creationEtudiant();
    printf("Combien voulez vous ajoutez d'etudiant?\n");
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        plist = ajoutEtudiant(plist);
    }
    for (int y = 0; y < 6; y++) {
        groupe++;
        afficheEtudiant(plist, groupe);
    }
    Etudiant* p1 = plist;
    char Prenom[20];
    char Nom[20];
    if (p1 == NULL) {
        exit(5);
    }
    printf("Quel est le Nom de l'etudiant?\n");
    scanf("%s", Nom);
    printf("Quel est le Prenom de l'etudiant?\n");
    scanf("%s", Prenom);
    p1 = trouveEtudiant(Nom, Prenom, plist);
    if (p1 != NULL) {
        printf("La moyenne de l'etudiant est %f\n", moyTab(p1->note));
    } else {
        printf("Etudiant non trouve.\n");
    }
    printf("La moyenne de toute la promo est : %f\n", moyPromo(plist));
    printf("La moyenne du pire eleve : %f\n", plusMauvaiseMoy(plist));
    return 0;
}