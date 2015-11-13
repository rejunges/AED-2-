#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bibliotecaHash.h"
int main(){
	char instrucao[10], *numero1, *numero2, c;
	int i;
	do{
		i=0;
		scanf("%c", &c);
		while( c!='('){//enquanto a leitura for diferente de ( continuar lendo a isntrução
			instrucao[i]=c;
			i++;
			scanf("%c", &c);
		}
		instrucao[i]='\0';
		if (strcmp(instrucao,"criar")==0){
			printf("%d\n",criar());
		}
		else{
			if(strcmp(instrucao, "fim")!=0){//Se a instrucao nao for criar ou fim, entao procura os numeros 
				numero1=(char*)malloc(sizeof(char)*sizeof(int));// esse char pode ser do tamanho de um inteiro
				i=0;
				scanf("%c", &c);
				while(c!=',' && c!=')'){//pega o primeiro numero da instrucao, le até quando o 'c' vira '('
					numero1[i]=c;
					i++;
					scanf("%c", &c);
				}
				numero1[i]='\0';
				if(strcmp(instrucao, "listar")==0){
					listar( atoi(numero1));
					free(numero1);
				}
				else{//precisa de mais de um numero
					numero2=(char*)malloc(sizeof(char)*sizeof(int));// esse char pode ser do tamanho de um inteiro
					i=0;
					scanf("%c", &c);
					while(c!=')'){//pega o primeiro numero da instrucao, encontrou o ')', para a procura 
						numero2[i]=c;
						i++;
						scanf("%c", &c);
					}
					numero2[i]='\0';
					//procura função
					if (strcmp(instrucao, "inserir")==0){
						printf("%d\n", inserir(atoi(numero1), atoi(numero2)));
					}
					else if (strcmp(instrucao, "existe")==0){
						printf("%d\n", existe(atoi(numero1), atoi(numero2)));
					}
					else if	(strcmp(instrucao, "excluir")==0){
						printf("%d\n", excluir(atoi(numero1), atoi(numero2)));
					}
					else if(strcmp(instrucao, "unir")==0){
						printf("%d\n", unir(atoi(numero1), atoi(numero2)));
					}
					free(numero1);
					free(numero2);
				}
			}
		}
		scanf("%c", &c); //Le o ) ou \n
		while (c!='\n'){
			scanf("%c", &c);
		}
	}while(strcmp(instrucao,"fim")!=0);//se for igual a instrucao fim para
	fim();
	return 0;
}
