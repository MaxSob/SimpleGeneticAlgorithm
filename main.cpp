#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Coin.h"
#include "Individual.h"
#include "SimpleGeneticAlgorithm.h"
#include "SevenOnes.h"
#include "SevenZeros.h"

using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int wait = 1;
   //All ones
   SimpleGeneticAlgorithm sga = SimpleGeneticAlgorithm(10, 101, 5, 30, 0.05, 0.95);
   sga.crosssValidation();
   cout << "Best individual all ones " << sga.best.print() << " -> Score: " << sga.best_output << endl;
   cin >> wait;
   //Exactly seven ones
   SevenOnes sones = SevenOnes(10, 99, 5, 30, 0.05, 0.95);
   sones.crosssValidation();
   cout << "Best individual exactly seven ones " << sones.best.print() << " -> Score: " << sones.best_output << endl;
   cin >> wait;
   //The first seven must be zeros
   SevenZeros szeros = SevenZeros(10, 100, 5, 30, 0.05, 0.95);
   szeros.crosssValidation();  
   cout << "Best individual first seven zeros " << szeros.best.print() << " -> Score: " << szeros.best_output << endl;
   cin >> wait;
  return 0;
}

