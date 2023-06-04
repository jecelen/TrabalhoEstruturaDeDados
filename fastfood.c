#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vizinhos.h"


void lerFastFood(regff* preg, arv **parv){
	FILE *ptrarq;
    int result;
    char endereco[200];

	ptrarq = fopen("Fast_Food_Restaurants_US.csv", "r");

	if(ptrarq == NULL){
		printf("Problema ao abrir o arquivo Fast_Food_Restaurants_US");
	}

	else{
		char indice[1000];
		char lixo;
		int i;
		preg = (regff*) malloc(sizeof(regff)*10000); /*total de ff*/
		result = fscanf(ptrarq, " %[^\n]", indice);
		while((result = fscanf(ptrarq, "%d", &i))!= EOF){
            regff *ff;
			ff = &(preg[i]);

			result = fscanf(ptrarq, "%c", &lixo);

			result = fscanf(ptrarq, "%[^,]", endereco);
			strcpy(ff->adress, endereco);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", ff->categ);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", ff->city);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%c", &ff->contry[0]);
			result = fscanf(ptrarq, "%c", &ff->contry[1]);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &ff->lat);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &ff->longt);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", ff->nome);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &ff->postalCode);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%c", &ff->province[0]);
			result = fscanf(ptrarq, "%c", &ff->province[1]);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, " %[^\n]", ff->site);

			insere(*parv, ff);

		}


	}

    fclose(ptrarq);

}


float calculoDistanciaFF(no* p, no* b){
    float difLat, difLongt;
    regff* x = (regff*)(p->reg);
    regff* no = (regff*)(b->reg);

    if(no->lat>=x->lat){
        difLat =(no->lat - x->lat)*111.1;
    }
    else{
        difLat =(x->lat - no->lat)*111.1;
    }
    printf("%f", difLat);
    if(no->longt>=x->longt){
        difLongt = (no->longt - x->longt)*96.2;
}
    else{
         difLongt = (x->longt - no->longt)*96.2;
    }
    printf("%f", difLongt);
    return sqrt((pow(difLat,2))+(pow(difLongt,2)));

}

void encontraVizinhosFastFood(arv *ptr_arv){
    no *noBusca, *resultadoS1, *resultadoP1, *resultadoP2, *resultadoS2, *resultadoP3, *resultadoS3;
	float longff, latff, suc, pred;
	regff *v1, *v2, *v3, *v4, *v5, *preg;

	printf("Digite a latitude do restaurante para localizar seus vizinhos próximos:\n");
	scanf("%f", &latff);
	printf("Digite a longitude do restaurante para localizar seus vizinhos próximos:\n");
	scanf("%f", &longff);

	preg = (regff*) malloc(sizeof(regff));
	preg->longt = longff;
	preg->lat = latff;

	noBusca = busca(ptr_arv, preg);
	resultadoS1 = defineSucessor(noBusca);
	resultadoP1 = definePredecessor(noBusca);
	resultadoP2 = definePredecessor(resultadoP1);
	resultadoS2 = defineSucessor(resultadoS1);
	resultadoP3 = definePredecessor(resultadoP2);
	resultadoS3 = defineSucessor(resultadoS2);

	pred = calculoDistanciaFF(resultadoS3, noBusca);
	suc = calculoDistanciaFF(resultadoS3, noBusca);

	v1 = (regff*)(resultadoS1->reg);
	printf("\n\nVizinho 1:\nNome: %s\n", v1->nome);
	printf("Endereço: %s, %s, %s\n", v1->adress, v1->city, v1->province);
	printf("Codigo Postal: %d\n", v1->postalCode);
	printf("Website(s): %s\n", v1->site);

	v2 = (regff*)(resultadoP1->reg);
	printf("\n\nVizinho 2:\nNome: %s\n", v2->nome);
	printf("Endereço: %s, %s, %s\n", v2->adress, v2->city, v2->province);
	printf("Codigo Postal: %d\n", v2->postalCode);
	printf("Website(s): %s\n", v2->site);

	v3 = (regff*)(resultadoS2->reg);
	printf("\n\nVizinho 3:\nNome: %s\n", v3->nome);
	printf("Endereço: %s, %s, %s\n", v3->adress, v3->city, v3->province);
	printf("Codigo Postal: %d\n", v3->postalCode);
	printf("Website(s): %s\n", v3->site);

	v4 = (regff*)(resultadoP2->reg);
	printf("\n\nVizinho 4:\nNome: %s\n", v4->nome);
	printf("Endereço: %s, %s, %s\n", v4->adress, v4->city, v4->province);
	printf("Codigo Postal: %d\n", v4->postalCode);
	printf("Website(s): %s\n", v4->site);

	if(pred<suc){
        v5 = (regff*)(resultadoP3->reg);
	}
	else{
        v5 = (regff*)(resultadoS3->reg);
	}
	printf("\n\nVizinho 5:\nNome: %s\n", v5->nome);
	printf("Endereço: %s, %s, %s\n", v5->adress, v5->city, v5->province);
	printf("Codigo Postal: %d\n", v5->postalCode);
	printf("Website(s): %s\n\n", v5->site);

}

int fastFoodControler(){
	regff *preg;
	arv *ptr_arv;
	int opff;
	constroi(&ptr_arv);
	preg = NULL;
	lerFastFood(preg, &ptr_arv);

	encontraVizinhosFastFood(ptr_arv);

    printf("Deseja buscar os vizinhos de outro restaurante?\n");
    printf("1. Sim.\n2. Não. Retornar ao menu principal e destruir a árvore de restaurantes.\n");
    scanf("%d", &opff);

    if(opff == 2){
        destroi(ptr_arv->r);
    }
    return opff;
}
