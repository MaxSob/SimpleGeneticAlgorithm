#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Individual.h"
#include "SimpleGeneticAlgorithm.h"

using namespace std;

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

  //This function converts a bit_Srting into an int
      int toInt(string bit_string, int length){
          int temp;
          int num=0;
          for(int i=0; i<length; i++){
              temp=bit_string[i]-'0';
              num |= (1 << (length-1-i)) * temp;
          }
          return num;
      }

      //This function obtains the fenotype of an individual
      string getFenotype(Individual ind) {    
           string fenotype = "";

          for(int i=0; i<ind.size(); i++) {
            if(ind.getBit(i))
               fenotype += "1";
            else
               fenotype += "0";
         }
         
         return fenotype + " --> " + to_string(toInt(fenotype, 10)) + " -- ";
      }
};