#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "biblioteca.h"

int compare(const void* a, const void* b){
    ARESTA* a1 = (ARESTA*)a;
    ARESTA* b1 = (ARESTA*)b;
    return a1->peso > b1->peso;
}
float kruskal(GRAFO grafo){
	int i,arestasEncontradas=0, arv1, arv2;
	float distancia=0;
	CONJUNTOS conjuntos[grafo.V];
	
	//cria os conjuntos disjuntos
	for (i=0; i<grafo.V; i++){
		conjuntos[i].conjunto=i; 
		conjuntos[i].arvoresTamanho=0;
	}
	//ordena as arestas do grafo
	qsort(grafo.aresta, grafo.A, sizeof(ARESTA), compare);
	
	//o numero arestas que devem ser encontras é num de Vertices-1
	i=0; //i vai ser a variavel q vai incrementar a próxima aresta
	while(arestasEncontradas < grafo.V-1){
		ARESTA proxAresta=grafo.aresta[i];
		i++;
		arv1=descobreRaiz(conjuntos, proxAresta.vertice1);
		arv2=descobreRaiz(conjuntos, proxAresta.vertice2);
		
		/* Se os vertices não estão na mesma árvore, eles
		 * devem se unir e a menor arvore apontar para a maior*/
		if (arv1!=arv2){
			distancia+=proxAresta.peso;
			arestasEncontradas++;
			uniaoConjuntos(conjuntos, arv1, arv2);
		}
	}
	return distancia;
}
int descobreRaiz(CONJUNTOS* conjunto, int vertice){
	/*Se o conjunto não é o próprio conjunto entao tem que buscar
	 * qual é a raiz dessa arvore */
	while(conjunto[vertice].conjunto!=vertice){
		vertice = conjunto[vertice].conjunto;
	}
	return conjunto[vertice].conjunto;
}
void uniaoConjuntos(CONJUNTOS* conjunto, int arv1, int arv2){
	int raiz1, raiz2;
	
	raiz1=descobreRaiz(conjunto, arv1);
	raiz2=descobreRaiz(conjunto, arv2);
	
	//Se os tamanhos forem iguais, a arvore aumenta 1 nivel
	if(conjunto[raiz1].arvoresTamanho == conjunto[raiz2].arvoresTamanho){
		conjunto[raiz2].conjunto= raiz1;
		conjunto[raiz1].arvoresTamanho++;
	}//Se os tamanhos forem diferentes, arvore mantem o nivel, mas a menor aponta para a maior
	else{
		if(conjunto[raiz1].arvoresTamanho > conjunto[raiz2].arvoresTamanho){
			conjunto[raiz2].conjunto= raiz1;
		}
		else{
			conjunto[raiz1].conjunto= raiz2;
		}
	}
}
