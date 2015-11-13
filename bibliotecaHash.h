#ifndef BIBLIOTECAHASH_H
#define BIBLIOTECAHASH_H
//Estruturas que usam o typedef são escritas em maiúsculas(convenção)
struct elementos{
  int num;
  struct elementos *prox;
};
typedef struct elementos DADOS;
typedef DADOS* HASH;//Hash é um Ponteiro de Dados
typedef struct{
	HASH *hash;
	int tamanhoHash;
	int numElementosNaHash;
	int numConjunto; //cada conjunto terá um número diferente
}CONJUNTO;
//Declaração de Variaveis
CONJUNTO *conjuntos;
//Declaração de Funcoes da estrutura hash
int existeNaHash(HASH *hash, int numero, int tamanho);
int funcaoHash(int numero, int tamanho);
HASH* criaHash(HASH *hash, int tamanho);
float fatorDeCarga (int tamanho, int numDeElementos);
HASH* insere(HASH *hash, int numero, int* tamanho, int *numDeElementos);
HASH* rehash(HASH *hash, int *tamanho);
void liberaHash(HASH *hash, int tamanho);
int removeNumero (HASH *hash, int numero, int tamanho, int *numDeElementos);
HASH* uniaoHash( HASH *final,int *tamFinal,int *numDeElementos, HASH *hash, int tamHash);
void leOrdenado(HASH *hash, int tamanho);
int compare(const void * a, const void * b);
//Declaração de Funções do trabalho de aed2
int criar();
int inserir(int elemento, int conjunto);
int existe (int elemento, int conjunto);
int excluir (int elemento, int conjunto);
int unir ( int conjunto1, int conjunto2);
void listar( int conjunto);
void fim();
int numeroDeConjuntos();
#endif 
