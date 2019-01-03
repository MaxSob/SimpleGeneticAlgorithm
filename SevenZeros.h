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