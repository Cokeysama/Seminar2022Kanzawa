#include<cmath>
#include<cfloat>
#include"vectorArray.h"

#ifndef __HCM__
#define __HCM__

class Hcm{
 protected:
  VectorArray Data, Centers, Tmp_Centers;
  VectorArray Membership, Tmp_Membership, Dissimilarities;
  VectorArray CrispMembership, CorrectCrispMembership, ContingencyTable;
  int Iterates;
  double Objective;
 public:
  Hcm(int dimension,
      int data_number,
      int centers_number);
  virtual void revise_membership(void);
  virtual void revise_dissimilarities(void);
  virtual void revise_centers(void);
  int dimension(void) const;
  int data_number(void) const;
  int centers_number(void) const;
  VectorArray centers(void) const;
  VectorArray tmp_centers(void) const;
  VectorArray data(void) const;
  VectorArray membership(void) const;
  VectorArray tmp_membership(void) const;
  int &iterates(void);
  VectorArray dissimilarities(void) const;
  double &data(int index1, int index2); 
  Vector &data(int index1); 
  double &centers(int index1, int index2); 
  Vector &centers(int index1); 
  double &membership(int index1, int index2); 
  double &dissimilarities(int index1, int index2);
  void set_objective(void);
  double objective(void) const;
  void set_crispMembership(void);
  VectorArray crispMembership(void) const;
  double &crispMembership(int index1, int index2);
  VectorArray correctCrispMembership(void) const;
  double &correctCrispMembership(int index1, int index2);
  void set_contingencyTable(void);
  VectorArray contingencyTable(void) const;
  double ARI(void) const;
};

#endif
