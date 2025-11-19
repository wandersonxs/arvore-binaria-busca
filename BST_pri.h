#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "BST_pub.h"

typedef struct NODE {
    void* data; // Dado
    struct NODE* left; // Nó a esquerda da árvore
    struct NODE* right; // Nó a direita da árvore

} NODE;

typedef struct BST {
    int sizedata; // Tamado de dados do nó
    int size; // Quantidade de nós
    NODE* root; // Raiz da árvore
} BST;

void dBSTNode(NODE* node);
void orderPathNode(NODE *node, void (*process)(void *p));
void preorderNode(NODE *node, void (*process)(void *p));
void postorderPathNode(NODE *node, void (*process)(void *p));

