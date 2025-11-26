#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "BST_pub.h"

typedef struct NODE {
    int height;
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
int sBSTNode(NODE *node, void *item, int (*cmp)(void *p1, void *p2));
void orderPathNode(NODE *node, void (*process)(void *p));
void preorderNode(NODE *node, void (*process)(void *p));
void postorderPathNode(NODE *node, void (*process)(void *p));

// Balanceamento AVL
int height(NODE *node);
int updateHeight(NODE *node);
int balanceFactor(NODE *node);
NODE* rotateLeft(NODE *node);
NODE* rotateRight(NODE *node);
NODE* rotateLeftRight(NODE *node);
NODE* rotateRightLeft(NODE *node);
NODE* insertNodeAVL(NODE *node, NODE *new_node, int (*cmp)(void *p1, void *p2));
NODE* removeNodeAVL(NODE *node, void *item, int (*cmp)(void*, void*), int sizedata, int *removed_flag);
NODE* applyBalancing(NODE *node);