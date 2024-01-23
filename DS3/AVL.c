#include <stdio.h>
#include <stdlib.h>

typedef struct AVL {
    int nb;
    struct AVL *right;
    struct AVL *left;
    int hauteur;
} AVL;

typedef AVL *pAVL;

pAVL creationAVL(int nombre) {
    pAVL root = malloc(sizeof(AVL));
    root->left = NULL;
    root->right = NULL;
    root->hauteur = 1;
    return root;
}

int recherche(pAVL root, int nb) {
    if (root == NULL) {
        return 0;
    } else if (nb == root->nb) {
        return 1;
    } else if (nb < root->nb) {
        return recherche(root->left, nb);
    } else {
        return recherche(root->right, nb);
    }
}

// Fonction pour obtenir la hauteur d'un nœud
int gethauteur(pAVL node) {
    if (node == NULL)
        return 0;
    return node->hauteur;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction pour mettre à jour la hauteur d'un nœud en fonction de la hauteur de ses enfants
void updatehauteur(pAVL node) {
    if (node != NULL) {
        node->hauteur = 1 + max(gethauteur(node->left), gethauteur(node->right));
    }
}

// Fonction pour effectuer une rotation simple à droite
pAVL rotateRight(pAVL y) {
    pAVL x = y->left;
    pAVL T2 = x->right;

    // Effectuer la rotation
    x->right = y;
    y->left = T2;

    // Mettre à jour les hauteurs
    updatehauteur(y);
    updatehauteur(x);

    return x;
}

// Fonction pour effectuer une rotation simple à gauche
pAVL rotateLeft(pAVL x) {
    pAVL y = x->right;
    pAVL T2 = y->left;

    // Effectuer la rotation
    y->left = x;
    x->right = T2;

    // Mettre à jour les hauteurs
    updatehauteur(x);
    updatehauteur(y);

    return y;
}

// Fonction pour obtenir l'équilibre d'un nœud
int getBalance(pAVL node) {
    if (node == NULL)
        return 0;
    return gethauteur(node->right) - gethauteur(node->left);
}

// Fonction d'insertion dans un AVL
pAVL insertionAVL(pAVL root, int nb) {
    // Étape d'insertion normale
    if (root == NULL) {
        return creationAVL(nb);
    }

    if (nb < root->nb) {
        root->left = insertionAVL(root->left, nb);
    } else if (nb > root->nb) {
        root->right = insertionAVL(root->right, nb);
    } else {
        // Les nœuds avec la même clé ne sont pas autorisés dans les AVL
        return root;
    }

    // Mettre à jour la hauteur du nœud actuel
    updatehauteur(root);

    // Obtenir le facteur d'équilibre de ce nœud pour vérifier l'équilibre
    int balance = getBalance(root);

    // Cas de déséquilibre à gauche
    if (balance > 1 && nb < root->left->nb) {
        return rotateRight(root);
    }

    // Cas de déséquilibre à droite
    if (balance < -1 && nb > root->right->nb) {
        return rotateLeft(root);
    }

    // Cas de déséquilibre gauche-droite aka double droite
    if (balance > 1 && nb > root->left->nb) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Cas de déséquilibre droite-gauche aka double gauche
    if (balance < -1 && nb < root->right->nb) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

pAVL findMinNode(pAVL node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

pAVL suppressionAVL(pAVL root, int nb) {
    if (root == NULL) {
        return root;
    }

    if (nb < root->nb) {
        root->left = suppressionAVL(root->left, nb);
    } else if (nb > root->nb) {
        root->right = suppressionAVL(root->right, nb);
    } else {
        // Le nœud à supprimer est trouvé

        // Cas 1: Nœud avec un enfant ou aucun enfant
        if ((root->left == NULL) || (root->right == NULL)) {
            pAVL temp = root->left ? root->left : root->right;

            // Cas sans enfant
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // Cas d'un enfant
                *root = *temp; // Copie le contenu du successeur
            }

            free(temp);
        } else {
            // Cas 2: Nœud avec deux enfants
            pAVL temp = findMinNode(root->right);

            // Copier les données du successeur dans ce nœud
            root->nb = temp->nb;

            // Supprimer le successeur
            root->right = suppressionAVL(root->right, temp->nb);
        }
    }

    // Si l'arbre a un seul nœud, retourner le nœud
    if (root == NULL) {
        return root;
    }

    // Mettre à jour la hauteur du nœud actuel
    updatehauteur(root);

    // Obtenir le facteur d'équilibre de ce nœud pour vérifier l'équilibre
    int balance = getBalance(root);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        // Cas gauche-gauche ou gauche-droite
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    // Cas de déséquilibre à droite
    if (balance < -1) {
        // Cas droite-droite ou droite-gauche
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

int main() {
    // Votre code de test ici
    return 0;
}

