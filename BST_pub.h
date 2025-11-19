#ifndef _BST_INTERFACE_H_
#define _BST_INTERFACE_H_

#define SUCCESS 0
#define FAIL 1

#define FALSE 0
#define TRUE 1

typedef struct BST *pBST, **ppBST;

int cBST(ppBST pp, int sizedata);
int dBST(ppBST pp);
int cleanBST(pBST p);
int iBST(pBST p, void *new, int (* cmp)(void *p1, void *p2));
int rBST(pBST p, void *item, int (* cmp)(void *p1, void *p2));
int sBST(pBST p, void *item, int (* cmp)(void *p1, void *p2));
int emptyBST(pBST p);
int orderPath(pBST pa, void (* process)(void *p));
int preorderPath(pBST pa, void (* process)(void *p));
int postorderPath(pBST pa, void (* process)(void *p));

#endif