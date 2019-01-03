#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Individual.h"
#include "SimpleGeneticAlgorithm.h"

//Class looking for seven ones 
class SevenOnes: public SimpleGeneticAlgorithm {
   public:
   		SevenOnes(int chromosome_size, int population_size, int tournament_size, int generations, double mutation_probability, double cross_probability):  
   			SimpleGeneticAlgorithm(chromosome_size, population_size, tournament_size, generations, mutation_probability, cross_probability){}


      	double evaluateIndividual(Individual ind) override {
      		int zeros=0;
      		for(int i=0; i<this->chromosome_size; i++)
      			if(!ind.getBit(i))
      				zeros += 1;
      		double error = abs(zeros - 3) *0.1;
			return error;
		}
};