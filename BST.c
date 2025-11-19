#include "BST_pri.h"

/* Criação de uma BST */
int cBST(ppBST pp, int sizedata) {
    if (sizedata <= 0) {
        printf("Passe sizedata maior que 0");
        return FAIL;
    }

    pBST p = malloc(sizeof(BST));

    if (!p) {
        printf("Erro ao criar a árvore.");
        return FAIL;
    }

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

/*
 * Limpeza de uma BST
 */
int cleanBST(pBST p) {
    if (!p) return FAIL;

    dBSTNode(p->root);

    p->root = NULL;
    p->size = 0;

    return SUCCESS;
}

/* Inserção em uma BST*/
int iBST(pBST p, void *new, int (*cmp)(void *p1, void *p2)) {
    if (!p || !new || !cmp) {
        return FAIL;
    }

    // Alocar memória para o nó
    NODE *new_node = malloc(sizeof(NODE));

    if (!new_node) {
        return FAIL;
    }

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
            p->size++;
            if (cmp(current_node->data, new_node->data) > 0) {
                if (current_node->left != NULL) {
                    current_node = current_node->left;
                } else {
                    stop_looping = 1;
                    current_node->left = new_node;
                }
            } else {
                if (current_node->right != NULL) {
                    current_node = current_node->right;
                } else {
                    stop_looping = 1;
                    current_node->right = new_node;
                }
            }
        }
    }
    return SUCCESS;
}

int rBST(pBST p, void *item, int (*cmp)(void *p1, void *p2)) {
    return SUCCESS;
}

int sBSTNode(NODE *node, void *item, int (*cmp)(void *p1, void *p2)) {
    if (!node) return FALSE;

    int exist = cmp(node->data, item);

    if (exist == 0) {
        return TRUE;
    }
    if (exist > 0) {
        return sBSTNode(node->left, item, cmp);
    }else {
       return sBSTNode(node->right,item,cmp);
    }
}

/*
 * Busca em uma BST: A função int sBST(pBST p, void *item, int (* cmp)(void *p1, void *p2))
 * deve buscar um elemento na BST e retornar um código indicando se o elemento foi encontrado ou não.
 *
 * O parâmetro item representa o elemento a ser buscado, enquanto cmp é a função de comparação utilizada
 * para comparar elementos na árvore.
 */

int sBST(pBST p, void *item, int (*cmp)(void *p1, void *p2)) {
    if (!p || !item || !cmp ) return FAIL;

    return sBSTNode(p->root, item, cmp);
}

/* Verificação de BST vazia */
int emptyBST(pBST p) {
    return p->size == 0 ? 0 : 1;
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
