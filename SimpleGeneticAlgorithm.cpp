#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Individual.h"
#include "SimpleGeneticAlgorithm.h"


using namespace std;

//Constructor of the class SimpleGeneticAlgorithm
SimpleGeneticAlgorithm::SimpleGeneticAlgorithm(int chromosome_size, int population_size, int tournament_size, int generations, double mutation_probability, double cross_probability) {
	this->chromosome_size = chromosome_size;
	this->population_size = population_size;
	this->tournament_size = tournament_size;
	this->generations = generations;
	this->mutation_probability = mutation_probability;
	this->cross_probability = cross_probability;
	
	this->population = vector<Individual>(this->population_size);
	this->initializePopulation();
    this->best_output = this->evaluateIndividual(this->best);
    this->best.evaluation = this->best_output;
	cout << "Best individual of generation 0 " << this->best.print() << endl;
}

//Destructor of the class SimpleGeneticAlgorithm
SimpleGeneticAlgorithm::~SimpleGeneticAlgorithm() { this->population.resize(0); }

//This function return a random number in an interval between to integers
int SimpleGeneticAlgorithm::getRandomNumber(int low, int high){ return ((int) rand() / RAND_MAX) * (high-low) + low; }

//This function initializes the population of the algorithm
void SimpleGeneticAlgorithm::initializePopulation() {
	for(int i=0; i < this->population_size; i++)
		this->population[i] = Individual(this->chromosome_size);
	this->best = this->population[0];
}

//This function obtains the fenotype of an individual
string SimpleGeneticAlgorithm::getFenotype(Individual ind) {    
     string fenotype = "";

    for(int i=0; i<ind.size(); i++) {
		if(ind.getBit(i))
			fenotype += "1";
		else
			fenotype += "0";
	}
    return fenotype;
}

//Returns thwe string representation of the best individual of a given generation
string getBestLine(int i, Individual best, double error) {
    string representation = "";
    representation += to_string(i) + "," + best.print() + ",";
    representation += to_string(1.0 - error);
	return representation;	
}


//This function get the error of a single individual
double SimpleGeneticAlgorithm::evaluateIndividual(Individual ind) {
	double errors = 0;
    for(int i=0; i<this->chromosome_size; i++)
		if(!ind.getBit(i))
			errors += 0.1;
	return errors;
}

double SimpleGeneticAlgorithm::evaluate() {
	double min_error = 100.0;
	double sum_error = 0.0;
	
	for(int i=0; i < this->population_size; i++) {
		double error = this->evaluateIndividual(this->population[i]);
        this->population[i].evaluation = error;
        //cout << "Evaluating individual " << i << " ->" << this->population[i].print() << " Score: " << this->population[i].evaluation  << endl;
        cout << "Evaluating individual " << i << " ->" << this->getFenotype(this->population[i]) << " Score: " << this->population[i].evaluation  << endl;
        if(error < min_error) {
			min_error = error;
			if(this->best_output >= error)
				this->best = this->population[i];
                this->best_output = error;
		}//End in case the error is less than min
		sum_error += error;
	}//End foreach individual in the population
	this->mse = sum_error/(double)this->population_size;
	return this->mse;
}

//We select the best individuals for a tournament
void SimpleGeneticAlgorithm::select() {
	vector<Individual> new_population(this->population_size);
	int individuals[this->tournament_size];
	for(int i=0; i<this->population_size; i++) {
		for(int j=0; j<this->tournament_size; j++)
			if(i+j >= this->population_size)
				individuals[j] = i+j - population_size;
			else
				individuals[j] = i+j;
		int local_best = individuals[0];
		for(int j=1; j<this->tournament_size; j++) {
			//cout << "Evaluating " << local_best << " against " << individuals[j] << endl;
			double local_best_error = this->population[local_best].evaluation;
			if(this->population[individuals[j]].evaluation <= local_best_error) {
				local_best = individuals[j]; 
				//cout << "New Local Best " << local_best << " chromosome " << this->population[individuals[j]].print() << endl;
			}
		}
		new_population[i] = this->population[local_best].copy();
	}//End population size
	this->population = new_population;
}

//We cross the population and make a new population
void SimpleGeneticAlgorithm::cross() {
	Coin c = Coin(this->cross_probability);
	//Shuffle index
	vector<Individual> new_population(this->population_size);
	
	for(int i=0; i<this->population_size/2;i++) {
		Individual i1 = this->population[2*i];
		Individual i2 = this->population[2*i + 1];
		if(c.toss()) {
			int cross_point = this->getRandomNumber(0, this->chromosome_size);
			vector<Individual> c =i1.cross(cross_point, i2);
			i1 = c[0];
			i2 = c[1];
		}
		new_population[2*i] = i1;
		new_population[2*i + 1] = i2;
	}
	this->population = new_population;
}

//We pass for each individual and chromosome and check if it should be mutated
void SimpleGeneticAlgorithm::mutate() {
	Coin c = Coin(this->mutation_probability);
	for(int i=0; i<this->population_size;i++)
		for(int j=0; j<this->chromosome_size; j++)
			if(c.toss()) {
				this->population[i].toogleBit(j);
				//cout << "Mutating individual " << i << " and chromosome bit " << j << endl;
			}
}

double SimpleGeneticAlgorithm::runGeneration() {
	this->evaluate();
	this->select();
	this->cross();
	this->mutate();
	return this->mse;
}

vector<double> SimpleGeneticAlgorithm::crosssValidation() {
	ofstream error, individuals;
	error.open ("error.txt");
    individuals.open ("individuals.txt");
	vector<double> errorSum(this->generations);
	for(int i=0; i<this->generations -1; i++) {
        errorSum[i] =this->runGeneration();
		cout << "Error " << this->mse << endl;
		cout << "Best individual of generation " << i << " " << this->best.print() << endl;
		error << this->mse << ",";
        individuals << getBestLine(i, this->best, best_output) << "\n";
	}
	errorSum[this->generations -1] =this->runGeneration();
	error << this->mse << "\n";
    individuals << getBestLine(this->generations, this->best, this->best_output) << "\n";
	error.close();
    individuals.close();
	return errorSum;
}
