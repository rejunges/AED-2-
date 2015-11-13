hash : conjuntoHash.o implementacaoHash.o
	gcc -o hash conjuntoHash.o implementacaoHash.o
conjuntoHash.o: conjuntoHash.c bibliotecaHash.h
	gcc -c conjuntoHash.c
implementacaoHash.o: implementacaoHash.c bibliotecaHash.h
	gcc -c implementacaoHash.c
clean:
	rm hash conjuntoHash.o implementacaoHash.o
