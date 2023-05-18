#ifndef _KDTREEH_
#define _KDTREEH_

typedef struct node{
	void *reg;
	struct node *pai;
	struct node *esq;
	struct node *dir;	
}no;

typedef struct _arv{
    no *r;
}arv;

void insere(arv *parv, void *preg);
arv* constroi(arv *parv);
no* busca(arv *parv, void *preg);
no* defineSucessor(arv *parv, no *ptr);
no* definePredecessor(arv *parv, no *ptr);
no* destroi(no *r);
float compara(const void *a, const void *b, int prof);

#endif