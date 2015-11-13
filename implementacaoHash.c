#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bibliotecaHash.h"

//Funções relacionadas a hash
void liberaHash(HASH *hash, int tamanho){
	int i;
	HASH auxiliar;
	for (i=0; i<tamanho; i++){
		auxiliar=hash[i];
		while(auxiliar!=NULL){//entao tem algum elemento
			free(auxiliar);
			auxiliar = auxiliar->prox;
		}	
	}
	free(hash);
}
HASH* insere(HASH *hash, int numero, int* tamanho, int *numDeElementos){
	int indice;
	indice = funcaoHash(numero, *tamanho);
	HASH auxiliar = hash[indice]; //auxiliar recebe a posição do vetor que deve ser inserido o número
	/*Se 'auxiliar' não é NULL signica que tem números inseridos nessa posição, entao ele precisa verificar que não está
	 * inserindo um número que já existe, para isso ele precisa percorrer até o fim ou até encontrar o número igual.*/
	while (auxiliar != NULL ){
		if ( auxiliar->num == numero ){
			return hash; //Significa que tá inserindo um número duplicado
		}
		auxiliar= auxiliar->prox;
	}
	if (auxiliar == NULL){ 	// Se tentar inserir um número duplicado, não entrará aqui
		auxiliar = (HASH)malloc(sizeof(HASH)); //cria uma posição pra inserir o número 
		if (auxiliar == NULL){ 		//Tratamento de memória
			return NULL;
		}
		auxiliar->num= numero;
		auxiliar->prox= hash[indice];//Se a hash[indice] estiver vazia, auxiliar recebe NULL
		hash[indice]=auxiliar;
		(*numDeElementos)++; 
	}
	if (((float)*numDeElementos / *tamanho)>=0.6){
		hash= rehash(hash, *(&tamanho)); //Faz rehash caso o fator de carga seja >= que 0.6
	}
	return hash;
}
int removeNumero (HASH *hash, int numero, int tamanho, int *numDeElementos){
	int indice;
	indice=funcaoHash(numero, tamanho);
	HASH auxiliar = hash[indice];
	if (auxiliar == NULL ){
		return -1; //Número não existe
	}
	else{
		if ( auxiliar->num == numero){
			if(auxiliar->prox != NULL){   //Deseja excluir o primeiro elemento da lista
				hash[indice]=auxiliar->prox;
				free(auxiliar);
				(*numDeElementos)--;
			}
			else {	//Auxiliar->prox == NULL, significa que era o único elemento da lista encadeada
				hash[indice]=NULL;
				free(auxiliar); //Não sei se essa linha é necessária*********************
				(*numDeElementos)--;
			}		
		}
		else{
			HASH anterior=auxiliar;
			auxiliar=auxiliar->prox;
			while (auxiliar->num != numero ){
				anterior=auxiliar;
				auxiliar=auxiliar->prox;
				if (auxiliar==NULL){
					return -1;
				}
			}
			if (auxiliar->num == numero ){ // O número existe 
				anterior->prox=auxiliar->prox; //Deseja-se excluir o auxiliar
				free (auxiliar);
				(*numDeElementos)--;
			}
		}
	}
	return 1;
}
HASH* rehash(HASH *hash, int *tamanho){
	int i,numElementos=0;
	*tamanho*=2; //Dobra o tamanho
	HASH *novaHash=malloc(sizeof(HASH)*(*tamanho));
	if (novaHash == NULL){
		return NULL;
	}
	novaHash=criaHash(novaHash, *tamanho);
	for (i=0; i<(*tamanho/2); i++){
		HASH auxiliar=hash[i];
		while ( auxiliar!= NULL){
			novaHash=insere(novaHash, auxiliar->num, *(&tamanho), &numElementos);
			auxiliar=auxiliar->prox;
		}
	}
	liberaHash(hash, (*tamanho/2));//Desaloca toda hash
	hash=novaHash; //hash aponta para novaHash
	return hash; 
}
int funcaoHash(int numero, int tamanho){
	return abs(numero)%tamanho; //abs trata quando o número é negativo
}
HASH* criaHash(HASH *hash, int tamanho){
	int i;
	for (i=0; i<tamanho; i++){
		hash[i]= NULL; // NULL em todas as posições porque inicializa vazia
	}
	return hash;
}
void leOrdenado(HASH *hash, int tamanho){
	int *vetorOrdenado;
	int i,j=0;
	HASH auxiliar;
	for (i=0; i<tamanho; i++){
		auxiliar=hash[i];
		while(auxiliar!=NULL){
			if (j==0){
				vetorOrdenado=(int *)malloc(sizeof(int));
			}
			else{
				vetorOrdenado=(int *)realloc(vetorOrdenado,sizeof(int)*(j+1));
			}
			vetorOrdenado[j]=auxiliar->num;
			j++;
			auxiliar=auxiliar->prox;
		}
	}
	if(j>0){	//Garante que nao vai dar segmentation fault caso nao exista nenhum numero na hash
		qsort (vetorOrdenado, j, sizeof(int), compare);
	}
	for (i=0; i<j; i++){ 	//Ler o vetor
		printf("%d",vetorOrdenado[i]);
		if (i<j-1){ 		//se ainda tiver outro número a ser lido, então coloca virgula
			printf (",");
		}
	}
	if (j>0){
		printf("\n");	//dá a linha em branco após a leitura do vetor, se houver vetor
		free (vetorOrdenado);
	}
}
int compare(const void * a, const void * b){
  if (*(int*)a <  *(int*)b) return -1;
  if (*(int*)a >  *(int*)b) return 1;
}
HASH* uniaoHash( HASH *final,int *tamFinal, int *numDeElementos, HASH *hash, int tamHash){
	int i=0;
	HASH auxiliar;
	for (i=0; i<tamHash; i++){
		auxiliar=hash[i];
		while(auxiliar!=NULL){
			final=insere(final, auxiliar->num, *(&tamFinal), *(&numDeElementos));
			auxiliar=auxiliar->prox;
		}
	}
	return final;
}		
int existeNaHash(HASH *hash, int numero, int tamanho){
	int i=funcaoHash(numero, tamanho); //informa o indice onde estará o elemento caso ele exista
	HASH auxiliar=hash[i];
	while(auxiliar!= NULL){
		if(auxiliar->num == numero){
			return 1; //existe
		}
		auxiliar=auxiliar->prox;
	}
	return -1;
}

int criar(){
	int static numConj=0;
	if (numConj==50){
		return -1; //só podem ter 50 conjuntos, do 0 ao 49. O 50 já é um conjunto inválido
	}
	if (numConj==0){//primeira vez é malloc, depois é realloc
		conjuntos=(CONJUNTO*)malloc(sizeof(CONJUNTO)); //cria um conjunto vazio
	}
	else {
		conjuntos=(CONJUNTO*)realloc(conjuntos, (sizeof(CONJUNTO))*(numConj+1)); //aloca mais um espaço na memória
	}
	if (conjuntos==NULL){
		return -1; //erro ao alocar o conjunto
	}
	conjuntos[numConj].numConjunto = numConj; //numero do conjunto é salvo em numConjunto
	conjuntos[numConj].numElementosNaHash=0;
	conjuntos[numConj].tamanhoHash = 50; //Todos os conjuntos iniciam com uma hash de tamanho 50
	conjuntos[numConj].hash = malloc(sizeof(HASH)*(conjuntos[numConj].tamanhoHash)); //Inicializa ela
	if (conjuntos[numConj].hash == NULL){
		return -1; //faltou memoria para alocar a hash
	}
	conjuntos[numConj].hash = criaHash(conjuntos[numConj].hash, conjuntos[numConj].tamanhoHash); 
	return numConj++; //criou com sucesso, incrementa numConj após o retorno
}
int inserir(int elemento, int conjunto){
	if (numeroDeConjuntos()==0 || conjuntos[conjunto].numConjunto!=conjunto){
		return -1;//Caso o conjunto não tenha sido criado ou caso nao existam conjuntos, retorna erro
	}
	conjuntos[conjunto].hash=insere(conjuntos[conjunto].hash, elemento, &conjuntos[conjunto].tamanhoHash, &conjuntos[conjunto].numElementosNaHash);
	if (conjuntos[conjunto].hash == NULL ){//Algo deu errado no insere
		return -1;
	}
	return 1; //ocorreu tudo bem
}
int existe (int elemento, int conjunto){
	//Caso o conjunto não tenha sido criado ou caso nao existam conjuntos, retorna erro
	if (numeroDeConjuntos()==0 || conjuntos[conjunto].numConjunto!=conjunto){
		return -1;
	}
	return existeNaHash(conjuntos[conjunto].hash, elemento, conjuntos[conjunto].tamanhoHash);
}
int excluir (int elemento, int conjunto){
	//Faz o segundo teste apenas para garantir que o conjunto nao existe
	if (numeroDeConjuntos()==0 || conjuntos[conjunto].numConjunto != conjunto ){
		//Conjunto não existe, NAO CAUSA ERRO
		return 1;
	}
	return removeNumero(conjuntos[conjunto].hash, elemento, conjuntos[conjunto].tamanhoHash, &conjuntos[conjunto].numElementosNaHash);	
}
int unir (int conjunto1, int conjunto2){
	int i;
	i=criar();//cria o conjunto que será a uniao
	//Faz a uniao da primeira hash e depois da segunda, retorna a hash "final", e o seu tamanho retorna por "referencia" 
	conjuntos[i].hash = uniaoHash(conjuntos[i].hash, &conjuntos[i].tamanhoHash,&conjuntos[i].numElementosNaHash, conjuntos[conjunto1].hash, conjuntos[conjunto1].tamanhoHash);
	conjuntos[i].hash = uniaoHash(conjuntos[i].hash, &conjuntos[i].tamanhoHash,&conjuntos[i].numElementosNaHash, conjuntos[conjunto2].hash, conjuntos[conjunto2].tamanhoHash);
	return i;
}
int numeroDeConjuntos(){
	int i=0;
	//Para descobrir o número do conjunto ( não pode aproveitar o identificadores)
	if(conjuntos==NULL){
		return 0;
	}
	else {
		while(conjuntos[i].numConjunto == i){
			i++;
		}
	}
	return i;
}
void listar( int conjunto){
	if(numeroDeConjuntos()!=0 && conjuntos[conjunto].numConjunto==conjunto){
		leOrdenado(conjuntos[conjunto].hash, conjuntos[conjunto].tamanhoHash);
	}
}
void fim(){
	int i,j;
	i=numeroDeConjuntos();
	for (j=0; j<i; j++){
		liberaHash(conjuntos[j].hash, conjuntos[j].tamanhoHash);
	}
	if (i>0){//Tratando o caso de encerrar programa sem nenhum conjunto
		free(conjuntos);
	}
}
