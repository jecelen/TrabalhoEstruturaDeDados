#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"
#include <assert.h>

typedef struct _reg{
	float lat;
	float longt;
	int codIBGE;
	char nome[50];
	int codUF;
	char uf[3];
	char regiao[20];
	int ddd[3];
	char fuso[30];
}reg;

float compara(const void *a, const void *b, int prof){
	int dimensao = (prof%2);

	if (dimensao==0){
		if ((*(reg*)a).longt < (*(reg*)b).longt){
			return -1;
		}
		else if ((*(reg*)a).longt > (*(reg*)b).longt){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if ((*(reg*)a).lat < (*(reg*)b).lat){
			return -1;
		}
		else if ((*(reg*)a).lat > (*(reg*)b).lat){
			return 1;
		}
		else{
			return 0;
		}
	}
}

void teste_constroi(arv **parv){
	*parv = constroi(*parv);
	assert((*parv)->r == NULL); /*teste inicialização da árvore*/
}

void teste_inserir(arv **parv){
	reg *preg, *preg1, *preg2, *preg3;
	no* raiz = (*parv)->r;

	preg = (reg*) malloc(sizeof(reg));
	preg->lat = -12.9551;
	preg->longt = -60.8947;
	strcpy(preg->nome, "Corumbiara");
	assert(strcmp(preg->nome, "Corumbiara") == 0);
	insere(*parv, preg);
	assert(compara((*parv)->r->reg, preg, 0) == 0); /*teste inserção nó raiz*/

	/*nós exemplo para teste*/
	preg1 = (reg*) malloc(sizeof(reg));
	preg1->lat = -26.9155;
	preg1->longt = -49.0709;
	strcpy(preg1->nome, "Blumenau");
	insere((*parv), preg1);

	preg2 = (reg*) malloc(sizeof(reg));
	preg2->lat = -24.2868;
	preg2->longt = -53.8404;
	strcpy(preg2->nome, "Palotina");
	insere(*parv, preg2);

	preg3 = (reg*) malloc(sizeof(reg));
	preg3->lat = -4.88161;
	preg3->longt = -64.3953;
	strcpy(preg3->nome, "Canutama");
	insere(*parv, preg3);

	/*testes após inserção dos nós*/
	assert(raiz->esq->esq == NULL);
	assert(raiz->dir->esq == NULL);
	assert(compara(raiz->reg, preg, 0) == 0);
	assert(compara(raiz->dir->reg, preg2, 1) == -1);
}

void teste_def_sucessor(arv *parv){
	/*teste função defineSucessor*/
	no* p = defineSucessor(parv, parv->r);
	assert(compara(p->reg, parv->r->dir->reg, 1)==0);
	assert(compara(p->reg, parv->r->dir->reg, 0)==0);
}

void teste_def_predecessor(arv *parv){
	/*teste função definePredecessor*/
	no* p = definePredecessor(parv, parv->r);
	assert(compara(p->reg, parv->r->esq->reg, 1)==0);
	assert(compara(p->reg, parv->r->esq->reg, 0)==0);
}

void teste_destroi(arv **parv){
	(*parv)->r = destroi((*parv)->r);
	assert((*parv)->r == NULL);
}


