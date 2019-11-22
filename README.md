[![Codacy Badge](https://api.codacy.com/project/badge/Grade/76636b4d2fb74ecfb5cb7d0030db50df)](https://www.codacy.com/manual/MaxSob/SimpleGeneticAlgorithm?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=MaxSob/SimpleGeneticAlgorithm&amp;utm_campaign=Badge_Grade)
# Simple Genetic Algorithms
Basic implementation of a simple genetic algorithm in C++

## Classes
  * Coin: This class simulates a probability charged coin the coin is set to true if the probability exceeds the related parameter which is used to initialize the coin.
  * Individuals: This class simulates an individual in the spread, is represented as a vector of zeros and one.
  * SimpleGeneticAlgorithm: This class implements a genetic algorithm parametrized by the number of generations, the chromosome size.



## Algorithm
The algorithm is implemented following the next steps:
  * Evaluation
  * Selection
  * Cross
  * Mutation

## Use
You can extend the main class simple genetic algorithm to change the evaluation function in order to find the best individual that you are interested in. Below is an example of a calss extended from SimpleGeneticAlgorithm which finds individuals with the first seven digits set to 0's:

```javascript
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Individual.h"
#include "SimpleGeneticAlgorithm.h"

//Class looking for seven ones 
class SevenZeros: public SimpleGeneticAlgorithm {
   public:
   	SevenZeros(int chromosome_size, int population_size, int tournament_size, int generations, double mutation_probability, double cross_probability):  
   		SimpleGeneticAlgorithm(chromosome_size, population_size, tournament_size, generations, mutation_probability, cross_probability){}

    double evaluateIndividual(Individual ind) override {
    	double error = 0;
    	for(int i=0; i<7; i++)
    		if(ind.getBit(i))
    			error += 0.14;
		return error;
	}
};
```
