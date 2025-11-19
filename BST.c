#include "BST_pri.h"

/* Criação de uma BST */
int cBST(ppBST pp, int sizedata) {
    if (sizedata <= 0) return FAIL;

    pBST p = malloc(sizeof(BST));

    if (!p) return FAIL;

    p->sizedata = sizedata;
    p->root = NULL;
    p->size = 0;

    *pp = p;

    return SUCCESS;
}

/* Destruição de uma BST */
int dBST(ppBST pp) {
    // Verifica se o ponteiro é válido
    if (!pp || !*pp) return FAIL;

    // Destrói a árvore diretamente, pois não tem nós
    if ((*pp)->root == NULL || (*pp)->size == 0) {
        free(*pp);
    } else {
        // Destrói os nodes e seus dados
        dBSTNode((*pp)->root);
        // Destrói a árvore
        free(*pp);
    }
    return SUCCESS;
}

/* Limpeza de uma BST */
int cleanBST(pBST p) {
    if (!p) return FAIL;

    dBSTNode(p->root);
    p->root = NULL;
    p->size = 0;

    return SUCCESS;
}

/* Inserção em uma BST */
int iBST(pBST p, void *new, int (*cmp)(void *p1, void *p2)) {
    if (!p || !new || !cmp) return FAIL;

    // Alocar memória para o nó
    NODE *new_node = malloc(sizeof(NODE));

    if (!new_node) return FAIL;

    // Alocar memória para a área de dados genérica
    new_node->data = malloc(p->sizedata);

    if (!new_node->data) {
        free(new_node);
        return FAIL;
    }

    // Copiar o valor para a área de dados
    memcpy(new_node->data, new, p->sizedata);

    new_node->left = NULL;
    new_node->right = NULL;

    NODE *current_node = p->root;
    int stop_looping = 0;

    if (current_node == NULL) {
        p->root = new_node;
        p->size = 1;
    } else {
        while (stop_looping == 0) {
            if (cmp(current_node->data, new_node->data) > 0) {
                if (current_node->left != NULL) {
                    current_node = current_node->left;
                } else {
                    stop_looping = 1;
                    current_node->left = new_node;
                    p->size++;
                }
            } else {
                if (current_node->right != NULL) {
                    current_node = current_node->right;
                } else {
                    stop_looping = 1;
                    current_node->right = new_node;
                    p->size++;
                }
            }
        }
    }
    return SUCCESS;
}

int rBST(pBST p, void *item, int (*cmp)(void *p1, void *p2)) {
    if (!p || !item || !cmp) return FAIL;

    NODE *node_father = NULL;
    NODE *node_current = p->root;

    // Localizar o nó a ser removido
    while (node_current != NULL) {
        int result = cmp(item, node_current->data);
        if (result == 0) {
            break;
        } else if (result < 0) {
            node_father = node_current;
            node_current = node_current->left;
        } else { // result > 0
            node_father = node_current;
            node_current = node_current->right;
        }
    }

    if (!node_current) return FAIL;

    // Verificar filhos do nó localizado
    int has_node_left  = (node_current->left  != NULL) ? TRUE : FALSE;
    int has_node_right = (node_current->right != NULL) ? TRUE : FALSE;

    // CASO 1: nó sem filhos (folha)
    if (!has_node_left && !has_node_right) {
        if (!node_father) {
            // Nó folha é a raiz
            p->root = NULL;
        } else {
            if (node_father->left == node_current) {
                node_father->left = NULL;
            } else {
                node_father->right = NULL;
            }
        }
        free(node_current->data);
        free(node_current);
        p->size--;
        return SUCCESS;
    }
    // CASO 2: nó com apenas UM filho
    else if (has_node_left != has_node_right) { // XOR: exatamente 1 filho
        NODE *node_unique_child = NULL;

        if (has_node_left == TRUE) {
            node_unique_child = node_current->left;
        } else {
            node_unique_child = node_current->right;
        }

        if (!node_father) {
            // Nó com 1 filho é a raiz
            p->root = node_unique_child;
        } else {
            if (node_father->left == node_current) {
                node_father->left = node_unique_child;
            } else {
                node_father->right = node_unique_child;
            }
        }

        free(node_current->data);
        free(node_current);
        p->size--;
        return SUCCESS;
    }
    // CASO 3: nó com DOIS filhos
    else {
        // Estratégia: usar o SUCESSOR (menor nó da subárvore direita)
        NODE *node_sucessor_father = node_current;
        NODE *node_successor = node_current->right;

        // Descer até o mais à esquerda da subárvore direita
        while (node_successor->left != NULL) {
            node_sucessor_father = node_successor;
            node_successor = node_successor->left;
        }

        // Copiar o dado do sucessor para o nó atual
        memcpy(node_current->data, node_successor->data, p->sizedata);

        // Agora remover fisicamente o sucessor: ele terá no máximo um filho (à direita)
        NODE *node_sucessor_child = node_successor->right; // pode ser NULL

        // Ajustar ponteiro no pai do sucessor
        if (node_sucessor_father->left == node_successor) {
            node_sucessor_father->left = node_sucessor_child;
        } else {
            node_sucessor_father->right = node_sucessor_child;
        }

        free(node_successor->data);
        free(node_successor);
        p->size--;
        return SUCCESS;
    }
}

/* Busca em uma BST */
int sBST(pBST p, void *item, int (*cmp)(void *p1, void *p2)) {
    if (!p || !item || !cmp) return FAIL;
     return sBSTNode(p->root, item, cmp);
}

/* Verificação de BST vazia */
int emptyBST(pBST p) {
    return p->size == 0 ? FALSE : TRUE;
}

/* Percurso In-order (Esquerda → Raiz → Direita) */
int orderPath(pBST pa, void (*process)(void *p)) {
    if (!pa || !process) return FAIL;
    orderPathNode(pa->root, process);
    return SUCCESS;
}

/* Percurso pre-order (Nó Atual → Esquerda → Direita) */
int preorderPath(pBST pa, void (*process)(void *p)) {
    if (!pa || !process) return FAIL;
    preorderNode(pa->root, process);
    return SUCCESS;
}

/* Percurso Post-order (Esquerda → Direita → Nó Atual) */
int postorderPath(pBST pa, void (*process)(void *p)) {
    if (!pa || !process) return FAIL;
    postorderPathNode(pa->root, process);
    return SUCCESS;
}

void orderPathNode(NODE *node, void (*process)(void *p)) {
    if (!node) return;
    orderPathNode(node->left, process);
    process(node->data);
    orderPathNode(node->right, process);
}

void preorderNode(NODE *node, void (*process)(void *p)) {
    if (!node) return;
    process(node->data);
    preorderNode(node->left, process);
    preorderNode(node->right, process);
}

void postorderPathNode(NODE *node, void (*process)(void *p)) {
    if (!node) return;
    postorderPathNode(node->left, process);
    postorderPathNode(node->right, process);
    process(node->data);
}

void dBSTNode(NODE *node) {
    if (!node) return;
    dBSTNode(node->left);
    dBSTNode(node->right);
    free(node->data);
    free(node);
}

int sBSTNode(NODE *node, void *item, int (*cmp)(void *p1, void *p2)) {
    if (!node) return FAIL;

    int exist = cmp(node->data, item);

    if (exist == 0) return SUCCESS;

    if (exist > 0) {
        return sBSTNode(node->left, item, cmp);
    } else {
        return sBSTNode(node->right, item, cmp);
    }
}
