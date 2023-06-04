#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vizinhos.h"

float compara(const void *a, const void *b, int prof){
	int dimensao = (prof%2);
    if(op == 1){
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

    else{
        if (dimensao==0){
            if ((*(regff*)a).longt < (*(regff*)b).longt){
                return -1;
            }
            else if ((*(regff*)a).longt > (*(regff*)b).longt){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            if ((*(regff*)a).lat < (*(regff*)b).lat){
                return -1;
            }
            else if ((*(regff*)a).lat > (*(regff*)b).lat){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
}


int main(){
    int opcid;
    int opff;

    do{
        printf("1. Encontrar o vizinho mais próximo de um município.\n");
        printf("2. Encontrar os cinco vizinhos mais próximos de um restaurante de fast food.\n");
        printf("3. Encerrar.\n");

        scanf("%d", &op);

        if(op == 1){

            do{
               opcid = municipiosControler();
            }while(opcid != 2);

        }
        else if(op == 2){
            do{
               opff = fastFoodControler();
            }while(opff != 2);
        }

    }while(op!=3);

    return 0;
}
