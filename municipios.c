#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vizinhos.h"

void lerCidades(reg* preg, arv **parv){
	FILE *ptrarq;
	int result;
	char nome[100];

	ptrarq = fopen("municipios.csv", "r");

	if(ptrarq == NULL){
		printf("Problema ao abrir o arquivo municipios");
	}

	else{
		char indice[1000];
		char lixo;
		int i = 0;
		preg = (reg*) malloc(sizeof(reg)*5570);  /*total de cidades*/
		result = fscanf(ptrarq, " %[^\n]", indice);

		while((result = fscanf(ptrarq, "%d", &preg[i].codIBGE)) != EOF){
            reg *cidade;
            cidade = &(preg[i]);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", nome);
			strcpy(cidade->nome, nome);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &cidade->lat);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &cidade->longt);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->capital);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->codUF);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->codSiafi);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->ddd);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, " %[^\n]", cidade->fuso);

			insere(*parv, cidade);
            i++;
		}

	}

    fclose(ptrarq);

}

float calculoDistanciaMunicipio(no* p, no* b){
    float difLat, difLongt;
    reg* x = (reg*)(p->reg);
    reg* no = (reg*)(b->reg);

    if(no->lat>=x->lat){
        difLat =(no->lat - x->lat)*111.1;
    }
    else{
        difLat =(x->lat - no->lat)*111.1;
    }
    if(no->longt>=x->longt){
        difLongt = (no->longt - x->longt)*96.2;
}
    else{
        difLongt = (x->longt - no->longt)*96.2;
    }

    return sqrt((pow(difLat,2))+(pow(difLongt,2)));

}

void encontrarVizinhosCidades(arv *parv){
    no *noBusca, *resultadoS, *resultadoP;
    reg *preg, *registro;
	float longCidade, latCidade, pred, suc;

	printf("\nDigite a latitude do município para localizar seu vizinho próximo:\n");
	scanf("%f", &latCidade);
	printf("\nDigite a longitude do município para localizar seu vizinho próximo:\n");
	scanf("%f", &longCidade);

	preg = (reg*) malloc(sizeof(reg));
	preg->longt = longCidade;
	preg->lat = latCidade;

	noBusca = busca(parv, preg);
	resultadoS = defineSucessor(noBusca);
	resultadoP = definePredecessor(noBusca);

	pred = calculoDistanciaMunicipio(resultadoP, noBusca);
	suc = calculoDistanciaMunicipio(resultadoS, noBusca);

	if(pred<suc){
        registro = (reg*)(resultadoP->reg);
	}
	else{
        registro = (reg*)(resultadoS->reg);
	}
	printf("\n\nVizinho mais próximo:\n\nNome: %s\n", registro->nome);
	printf("Código IBGE: %d\n", registro->codIBGE);
	printf("Latitude: %f Longitude: %f\n", registro->lat, registro->longt);
	printf("Código UF: %d\n", registro->codUF);
	printf("Código Siafi: %d\n", registro->codSiafi);
	printf("DDD: %d\n", registro->ddd);
	printf("Capital: %d\n", registro->capital);
	printf("Fuso Horário: %s\n\n", registro->fuso);
}

int municipiosControler(){
    reg *preg;
    arv *parv;
    int opcid;
    constroi(&parv);
    preg = NULL;
    lerCidades(preg, &parv);
    encontrarVizinhosCidades(parv);

    printf("Deseja buscar o vizinho de um novo município?\n");
    printf("1. Sim.\n2. Não: Retornar ao menu principal e destruir árvore de municípios.\n");
    scanf("%d", &opcid);

    if(opcid == 2){
        destroi(parv->r);
    }
    return opcid;
}
