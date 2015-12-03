#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#define INF 9999999999 

typedef struct{
	float x,y;
}POSICAO;

typedef struct{
	int vertice1,vertice2;
	float peso;
}ARESTA;

typedef struct{
	int V, A;
	ARESTA *aresta;
}GRAFO;

typedef struct{
	int conjunto;
	int arvoresTamanho;
}CONJUNTOS; 

int compare(const void* a, const void* b);
float kruskal(GRAFO grafo);
int descobreRaiz(CONJUNTOS* conjunto, int vertice);
void uniaoConjuntos(CONJUNTOS* conjunto, int arv1, int arv2);

#endif 
