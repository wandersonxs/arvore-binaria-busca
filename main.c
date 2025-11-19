#include "main.h"

int comparaDados(void *dado1, void *dado2) {
    int n1 = *((int *)dado1);
    int n2 = *((int *)dado2);
    if (n1 < n2) return -1;
    if (n1 > n2) return 1;
    return 0;
}

void process(void *p) {
    printf("%d ", *(int *)p);
}

int main(int argc, char *argv[]) {

    pBST pBST = NULL;
    int novo_elemento;
    int elements[] = {30, 25, 27, 28, 26, 12, 15, 10, 50, 60, 40, 35, 42, 65, 58};

    // Cria a árvore
    if (cBST(&pBST, sizeof(int)) == FAIL) return FAIL;

    for (int i = 0; i < sizeof(elements)/sizeof(elements[0]); i++) {
        novo_elemento = elements[i];
        if((iBST(pBST, &novo_elemento, comparaDados)) == FAIL) {
            printf("Erro na insercao\n");
            dBST(&pBST);
            return FAIL;
        }
    }

    printf("\nIn-order traversal: ");
    orderPath(pBST, process);

    printf("\nPre-order traversal: ");
    preorderPath(pBST, process);

    printf("\nPost-order traversal: ");
    postorderPath(pBST, process);

    // Buscar elemento na raiz = 30
    int elemento_busca = 65;

    printf("\nBuscar elemento %d ", elemento_busca);

    if (sBST(pBST, &elemento_busca, comparaDados) == SUCCESS) {
        printf("\nEncontrou elemento %d ", elemento_busca);
    }else {
        printf("\nNão encontrou elemento %d", elemento_busca);
    }

    printf("\nRemover elemento %d ", elemento_busca);

    // remove a raiz da árvore
    rBST(pBST, &elemento_busca , comparaDados);

    printf("\nBuscar elemento %d ", elemento_busca);

    if (sBST(pBST, &elemento_busca, comparaDados) == SUCCESS) {
        printf("\nEncontrou elemento %d ", elemento_busca);
    }else {
        printf("\nNão encontrou elemento %d", elemento_busca);
    }
    // Limpar a árvore
    printf("\nLimpa a árvore");
    cleanBST(pBST);

    // Verifica se a árvore está limpa
    emptyBST(pBST) == 0 ? printf("\nÁrvore limpa\n") : printf("\nArvore NÃO limpa\n");

    // Destrói a árvore
    if (dBST(&pBST) == FAIL) return FAIL;

    return 0;
}
