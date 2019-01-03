#include <math.h>
#include <stdlib.h>
#include "Coin.h"

Coin::Coin(double p) { this->probability = p; }	

bool Coin::toss() {
  double result = (double)rand()/RAND_MAX; 
  if(result <= this->probability)
	return true;
  return false;
}
