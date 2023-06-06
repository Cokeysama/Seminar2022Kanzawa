#include<cmath>
#include<cfloat>
#include"vectorArray.h"
#include"hcm.h"

#ifndef __SFCM__
#define __SFCM__

class Sfcm: public Hcm{
private:
  double FuzzifierEm;
public:
  Sfcm(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm);
  double &fuzzifierEm(void);
  void revise_membership(void);
  void revise_centers(void);
};

#endif

