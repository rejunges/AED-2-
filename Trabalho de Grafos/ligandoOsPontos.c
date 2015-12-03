#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "biblioteca.h"

int main(){
	int numSardas, i, j, numArestas=0;
	GRAFO grafo;
	
	//Le o número de sardas
	scanf("%d", &numSardas);
	POSICAO sardas[numSardas];
	grafo.V=numSardas;
	grafo.A=numSardas*numSardas;
	grafo.aresta=malloc(sizeof(ARESTA)*grafo.A);
	
	//Le as coordenadas das sardas
	for (i=0; i<numSardas; i++){
		scanf("%f %f", &sardas[i].x, &sardas[i].y);
	}
	
	//preenche a estrutura grafo
	for (i=0; i<numSardas; i++){
		for (j=0; j<numSardas;j++){
			float distancia;
			grafo.aresta[numArestas].vertice1=i;
			grafo.aresta[numArestas].vertice2=j;
			distancia= sqrt(pow(sardas[j].x-sardas[i].x, 2)+pow(sardas[j].y-sardas[i].y,2));
			if (distancia!=0){
				grafo.aresta[numArestas].peso=distancia;
			}
			else{
				grafo.aresta[numArestas].peso=INF;
			}
			numArestas++;
		}
	}
	
	printf ("%.2f\n",kruskal(grafo));
	free(grafo.aresta);
	return 0;
}
