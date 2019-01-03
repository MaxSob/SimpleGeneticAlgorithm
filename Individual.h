#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_
#include <vector>
#include <string>

class Individual {
  int lenght;
  std::vector<bool> chromosome;
  
  public:
  double evaluation;
  Individual();
  Individual(int lenght);
  void setBit(int n, bool value);
  void toogleBit(int n);
  bool getBit(int n);
  Individual copy();
  int size();
  std::vector<Individual> cross(int n, Individual another);
  std::string print();
};

#endif
