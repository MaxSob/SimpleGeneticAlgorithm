all: main

main: Individual.o Coin.o SimpleGeneticAlgorithm.o SevenOnes.o SevenZeros.o
	g++ Coin.o Individual.o SimpleGeneticAlgorithm.o main.cpp -o main

SevenOnes.o: SevenOnes.h
	g++ -std=c++11 -c SevenOnes.h -o SevenOnes.o 

SevenZeros.o: SevenZeros.h
	g++ -std=c++11 -c SevenZeros.h -o SevenZeros.o 

SimpleGeneticAlgorithm.o: SimpleGeneticAlgorithm.cpp
	g++ -std=c++11 -c SimpleGeneticAlgorithm.cpp -o SimpleGeneticAlgorithm.o 
	
	
Individual.o: Individual.cpp
	g++ -c Individual.cpp -o Individual.o

Coin.o: Coin.cpp
	g++ -c Coin.cpp -o Coin.o

clean:
	rm *o main
