#ifndef _SIMPLEGENETICALGORITHM_H_
#define _SIMPLEGENETICALGORITHM_H_

#include "Coin.h"
#include "Individual.h"
#include <string>
#include <vector>

class SimpleGeneticAlgorithm {
	protected:
		int population_size;
		int tournament_size;
		int generations;
		int chromosome_size;
		double mutation_probability;
		double cross_probability;
		double mse;
	
	public:
    	double best_output;
		Individual best;
		std::vector<Individual> population;
		SimpleGeneticAlgorithm(int chromosome_size, int population_size, 
			int tournament_size, int generations, double mutation_probability, 
			double cross_probability);
		~SimpleGeneticAlgorithm();
		int getRandomNumber(int low, int high);
		void initializePopulation();
		double virtual evaluateIndividual(Individual i);
		std::string virtual getFenotype(Individual i);
		double evaluate();
		void select();
		void cross();
		void mutate();
		double runGeneration();
		std::vector<double> crosssValidation();
};

#endif
