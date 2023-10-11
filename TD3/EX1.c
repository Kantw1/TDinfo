#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Pour utiliser les fonctions de manipulation de chaînes
#define size 20

typedef struct chainon {
    char mot[size];
    struct chainon *next;
    struct chainon *prev;
} Chainon;

Chainon *creationChainon() {
    Chainon *c = malloc(sizeof(Chainon));
    if (c == NULL) {
        exit(1);
    }
    c->next = NULL;
    c->prev = NULL;
    printf("Rentrez un mot : ");
    scanf("%s", c->mot);
    return c;
}

int compareMot(char *mot1, char *mot2) {
    int i = 0;
    int taille1 = strlen(mot1);
    int taille2 = strlen(mot2);
   
    while (i < taille1 && i < taille2) {
        if (mot1[i] > mot2[i]) {
            return 1;
        } else if (mot1[i] < mot2[i]) {
            return -1;
        }
        i++;
    }
   
    if (taille1 < taille2) {
        return -1;
    } else if (taille1 > taille2) {
        return 1;
    }
   
    return 0; // Les mots sont identiques
}

Chainon *inserChainon(Chainon *pliste) {
    Chainon *nouveau = creationChainon();
   
    if (pliste == NULL) {
        return nouveau;
    }
   
    Chainon *p1 = pliste;
   
    while (p1 != NULL) {
        if (compareMot(nouveau->mot, p1->mot) == -1) {
            if (p1->prev == NULL) {
                p1->prev = nouveau;
                nouveau->next = p1;
                return nouveau;
            } else {
                p1->prev->next = nouveau;
                p1->prev = nouveau;
                nouveau->next = p1;
                return pliste;
            }
        }
        p1 = p1->next;
    }
   
    // Si nouveau doit être le dernier élément de la liste
    Chainon *dernier = pliste;
    while (dernier->next != NULL) {
        dernier = dernier->next;
    }
    dernier->next = nouveau;
    nouveau->prev = dernier;
   
    return pliste;
}

void afficheFil(Chainon *pliste) {
    Chainon *p1 = pliste;

    if (pliste == NULL) {
        printf("La liste est vide.\n");
        return;
    }
   
    while (p1 != NULL) {
        printf("%s -> ", p1->mot);
        p1 = p1->next;
    }
    printf("\n");
}

int main() {
    Chainon *pliste = NULL;
    int n;

    printf("Combien de mots voulez-vous ajouter ? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pliste = inserChainon(pliste);
    }

    printf("Liste triée :\n");
    afficheFil(pliste);

    return 0;
}
