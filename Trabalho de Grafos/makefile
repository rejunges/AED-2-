ligandoOsPontos : ligandoOsPontos.o implementacaoBiblioteca.o
	gcc -o ligandoOsPontos ligandoOsPontos.o implementacaoBiblioteca.o -lm
ligandoOsPontos.o: ligandoOsPontos.c biblioteca.h
	gcc -c ligandoOsPontos.c 
implementacaoBiblioteca.o: implementacaoBiblioteca.c biblioteca.h
	gcc -c implementacaoBiblioteca.c 
clean:
	rm -r ligandoOsPontos ligandoOsPontos.o implementacaoBiblioteca.o
