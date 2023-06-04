#ifndef VIZINHOS_H
#define VIZINHOS_H
#include <math.h>
#include "kdtree.h"

typedef struct _uf{
	char nome[100];
	int codUF;
	char uf[3];
	float lat;
	float longt;
	char regiao[20];
}uf;

typedef struct _reg{
	int codIBGE;
	char nome[100];
	int codUF;
	int capital;
	float lat;
	float longt;
	int codSiafi;
	int ddd;
	char fuso[33];
}reg;

typedef struct _fastFood{
	char adress[200];
	char categ[200];
	char city[100];
	char contry[3];
	float lat;
	float longt;
	char nome[100];
	int postalCode;
	char province[3];
	char site[1000];
}regff;

int municipiosControler();
int fastFoodControler();
void lerCidades(reg* preg, arv **parv);
void lerFastFood(regff* preg, arv **parv);
void encontraVizinhosFastFood(arv *ptr_arv);
void encontrarVizinhosCidades(arv *parv);
float calculoDistanciaFF(no* p, no* b);
float calculoDistanciaMunicipio(no* p, no* b);

int op;

#endif
