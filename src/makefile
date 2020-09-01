.DEFAULT_GOAL:= tp1

tp1: main.o CasaTabuleiro.o JogoDoPulo.o
	@echo "Unindo os arquivos..."
	g++ main.o CasaTabuleiro.o JogoDoPulo.o -o tp1

main.o: main.cpp
	@echo "Compilando..."
	g++ -c main.cpp

CasaTabuleiro.o: CasaTabuleiro.cpp CasaTabuleiro.h
	g++ -c CasaTabuleiro.cpp

JogoDoPulo.o: JogoDoPulo.cpp JogoDoPulo.h
	g++ -c JogoDoPulo.cpp

run: tp1
	@echo "Rodando..."
	./tp1

clean:
	@echo "Limpando..."
	rm *.o tp1