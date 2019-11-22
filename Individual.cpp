#include <iostream>
#include "Individual.h"
#include "Coin.h"

using namespace std;

Individual::Individual() {
	Individual(5);
}

Individual::Individual(int lenght) {
	Coin c = Coin(0.5);
	this->lenght = lenght;
	this->chromosome =  vector<bool>(lenght);
	this->evaluation = 0;
	for(int i=0; i<this->lenght;i++)
		this->setBit(i, c.toss());
}
  
void Individual::setBit(int n, bool value){ this->chromosome[n] = value; }
  
void Individual::toogleBit(int n) {
	if(this->chromosome[n])
		this->chromosome[n] = false;
	else
		this->chromosome[n] = true;
}

int Individual::size(){ return this->lenght; }
  
bool Individual::getBit(int n){ return this->chromosome[n]; }
  
Individual Individual::copy() {
	Individual copy = Individual(this->lenght);
	for(int i=0; i<this->lenght;i++)
		copy.setBit(i, this->getBit(i));
	return copy;
}
  
vector<Individual> Individual::cross(int n, Individual another) {
	vector<Individual> sons (2);
	sons[0] = this->copy();
	sons[1] = another.copy();
	for(int i=n; i<this->lenght; i++) {
		sons[0].setBit(i, another.getBit(i));
		sons[1].setBit(i, this->getBit(i));
	 }
	 return sons;
 }

string Individual::print() {
	string out = "";
	for(int i=0; i<this->lenght;i++)
		if(this->chromosome[i])
			out += "1";
		else
			out += "0";
	return out;
}
