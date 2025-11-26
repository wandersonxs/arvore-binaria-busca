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
    new_node->height = 0; // folha na AVL

    if (p->root == NULL) {
        p->root = new_node;
        p->size = 1;
    } else {
        p->root = insertNodeAVL(p->root, new_node, cmp);
        p->size++;
    }

    return SUCCESS;
}

/* Inserção em uma BST (SEM BALANCEAMENTO) */
// int iBST(pBST p, void *new, int (*cmp)(void *p1, void *p2)) {
//     if (!p || !new || !cmp) return FAIL;
//
//     // Alocar memória para o nó
//     NODE *new_node = malloc(sizeof(NODE));
//
//     if (!new_node) return FAIL;
//
//     // Alocar memória para a área de dados genérica
//     new_node->data = malloc(p->sizedata);
//
//     if (!new_node->data) {
//         free(new_node);
//         return FAIL;
//     }
//
//     // Copiar o valor para a área de dados
//     memcpy(new_node->data, new, p->sizedata);
//
//     new_node->left = NULL;
//     new_node->right = NULL;
//
//     NODE *current_node = p->root;
//     int stop_looping = 0;
//
//     if (current_node == NULL) {
//         p->root = new_node;
//         p->size = 1;
//     } else {
//         while (stop_looping == 0) {
//             if (cmp(current_node->data, new_node->data) > 0) {
//                 if (current_node->left != NULL) {
//                     current_node = current_node->left;
//                 } else {
//                     stop_looping = 1;
//                     current_node->left = new_node;
//                     p->size++;
//                 }
//             } else {
//                 if (current_node->right != NULL) {
//                     current_node = current_node->right;
//                 } else {
//                     stop_looping = 1;
//                     current_node->right = new_node;
//                     p->size++;
//                 }
//             }
//         }
//     }
//     return SUCCESS;
// }

/*
 // Remover árvore (NÃO BALANCEADA)
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
        } else {
            // result > 0
            node_father = node_current;
            node_current = node_current->right;
        }
    }

    if (!node_current) return FAIL;

    // Verificar filhos do nó localizado
    int has_node_left = (node_current->left != NULL) ? TRUE : FALSE;
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
    else if (has_node_left != has_node_right) {
        // XOR: exatamente 1 filho
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
}*/

int rBST(pBST p, void *item, int (*cmp)(void *p1, void *p2)) {
    if (!p || !item || !cmp) return FAIL;

    int removed = 0;

    p->root = removeNodeAVL(p->root, item, cmp, p->sizedata, &removed);

    if (removed) {
        p->size--;
        return SUCCESS;
    }

    return FAIL;
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

// Métodos de balanceamento
int height(NODE *node) {
    if (!node) {
        return -1;
    } else {
        return node->height;
    }
}

int updateHeight(NODE *node) {
    if (!node) return FAIL;
    int node_left_height = height(node->left);
    int node_right_height = height(node->right);
    node->height = 1 + (node_left_height > node_right_height ? node_left_height : node_right_height);
    return node->height;
}

/*
	•	Se o filho esquerdo é mais alto → fator positivo
    •	Se o filho direito é mais alto → fator negativo
    •	Se a diferença atingir +2 ou –2, o nó precisa de rotação

    Os valores possíveis e seus significados:
    •	0 → balanceado
    •	+1 → um pouco mais alto à esquerda (OK)
    •	–1 → um pouco mais alto à direita (OK)
    •	+2 → desbalanceado para a esquerda (precisa rotação)
    •	–2 → desbalanceado para a direita (precisa rotação)
 */
int balanceFactor(NODE *node) {
    if (!node) return 0;

    int node_left_height = height(node->left);
    int node_right_height = height(node->right);
    return node_left_height - node_right_height;
}

/*  A rotação à esquerda é usada quando:
    O fator de balanceamento do nó é –2, ou seja, mais pesado à direita.
    X - NODE
     \
      Y - NODE_CHILD
       \
        Z
*/
NODE *rotateLeft(NODE *node) {
    NODE *node_child = node->right;

    if (!node_child) {
        // Opcional: logar erro aqui, porque isso não deveria acontecer
        return node; // não rotaciona nada
    }

    NODE *node_temp = node_child->left;

    node_child->left = node;
    node->right = node_temp;

    updateHeight(node); // primeiro quem desceu (X)
    updateHeight(node_child); // depois quem subiu (Y)

    return node_child; // nova raiz da subárvore
}

/*  A rotação à direita é usada quando:
    O fator de balanceamento do nó é +2, ou seja, mais pesado à esquerda.
           X - NODE
         /
       Y - NODE_CHILD
      /
    Z
*/
NODE *rotateRight(NODE *node) {
    if (!node) return NULL;

    NODE *node_child = node->left;

    if (!node_child) {
        // Opcional: logar erro aqui, porque isso não deveria acontecer
        return node; // não rotaciona nada
    }

    NODE *node_temp = node_child->right;

    node_child->right = node;
    node->left = node_temp;

    updateHeight(node);
    updateHeight(node_child);

    return node_child;
}

NODE *rotateLeftRight(NODE *node) {
    if (!node) return NULL;
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

NODE *rotateRightLeft(NODE *node) {
    if (!node) return NULL;

    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

NODE *insertNodeAVL(NODE *node, NODE *new_node, int (*cmp)(void *p1, void *p2)) {
    if (node == NULL) return new_node;

    if (cmp(node->data, new_node->data) > 0) {
        // new_node vai para a esquerda
        node->left = insertNodeAVL(node->left, new_node, cmp);
    } else {
        node->right = insertNodeAVL(node->right, new_node, cmp);
    }

    // Atualiza altura deste nó
    updateHeight(node);
    return applyBalancing(node);
}

NODE *removeNodeAVL(NODE *node, void *item, int (*cmp)(void *, void *), int sizedata, int *removed_flag) {
    if (node == NULL) return NULL;

    int result = cmp(item, node->data);

    if (result < 0) {
        // item menor -> está na esquerda
        node->left = removeNodeAVL(node->left, item, cmp, sizedata, removed_flag);
    } else if (result > 0) {
        // item maior -> está na direita
        node->right = removeNodeAVL(node->right, item, cmp, sizedata, removed_flag);
    } else {
        *removed_flag = 1;

        // CASO 1: nó com 0 ou 1 filho
        if (node->left == NULL || node->right == NULL) {
            NODE *child = node->left ? node->left : node->right; // pode ser NULL

            // libera o nó atual
            free(node->data);
            free(node);

            // retorna o filho (pode ser NULL) para ligar na árvore
            return child;
        }

        // CASO 2: nó com DOIS filhos:
        // Usa o SUCESSOR (menor nó da subárvore direita)
        NODE *succ = node->right;
        while (succ->left != NULL) {
            succ = succ->left;
        }
        memcpy(node->data, succ->data, sizedata);

        // Remove o sucessor na subárvore direita
        int dummy_removed = 0;
        node->right = removeNodeAVL(node->right, succ->data, cmp, sizedata, &dummy_removed);
    }

    // Se chegamos aqui, node pode ter ficado NULL (se era folha com 0/1 filho)
    if (node == NULL) return NULL;

    updateHeight(node);
    return applyBalancing(node);
}

NODE *applyBalancing(NODE *node) {
    int bf = balanceFactor(node);

    // LL: pesado à esquerda, filho esquerdo não aponta à direita
    if (bf > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // LR: pesado à esquerda, filho esquerdo pesado à direita
    if (bf > 1 && balanceFactor(node->left) < 0) {
        return rotateLeftRight(node);
    }

    // RR: pesado à direita, filho direito não aponta à esquerda
    if (bf < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // RL: pesado à direita, filho direito pesado à esquerda
    if (bf < -1 && balanceFactor(node->right) > 0) {
        return rotateRightLeft(node);
    }

    // se não precisou rotacionar
    return node;
}
