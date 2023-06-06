#include<iostream>
#include<cstring>
#include"vector.h"

#ifndef __VECTORARRAY__
#define __VECTORARRAY__

class VectorArray{
 private:
  int Rows;
  Vector *Element;
 public:
  //VectorArray(int rows=0);
  VectorArray(int rows=0, int cols=0);
  explicit VectorArray(int dim, const char *s);
  explicit VectorArray(const Vector &arg, const char *s);
  ~VectorArray(void);
  VectorArray(const VectorArray &arg);
  VectorArray &operator=(const VectorArray &arg);
  VectorArray(VectorArray &&arg);
  VectorArray &operator=(VectorArray &&arg);
  int rows(void) const;
  int cols(void) const;
  Vector operator[](int index) const;
  Vector &operator[](int index);
  VectorArray operator+(void) const;
  VectorArray operator-(void) const;
  VectorArray &operator+=(const VectorArray &rhs);
  VectorArray &operator-=(const VectorArray &rhs);
  VectorArray &operator*=(double rhs);
  VectorArray &operator/=(double rhs);
  VectorArray sub(int row_begin,
		   int row_end,
		   int col_begin,
		   int col_end) const;
  void set_sub(int row_begin,
	       int row_end,
	       int col_begin,
	       int col_end,
	       const VectorArray &arg);
};

VectorArray operator+(const VectorArray &lhs, const VectorArray &rhs);
VectorArray operator-(const VectorArray &lhs, const VectorArray &rhs);
VectorArray operator*(double lhs, const VectorArray &rhs);
Vector operator*(const VectorArray &lhs, const Vector &rhs);
VectorArray operator*(const VectorArray &lhs, const VectorArray &rhs);
VectorArray operator*(const VectorArray &lhs, double rhs);
VectorArray operator/(const VectorArray &lhs, double rhs);
std::ostream &operator<<(std::ostream &os, const VectorArray &rhs);
bool operator==(const VectorArray &lhs, const VectorArray &rhs);
double max_norm(const VectorArray &arg);
double frobenius_norm(const VectorArray &arg);
VectorArray transpose(const VectorArray &arg);
Vector diag(const VectorArray &arg);
VectorArray pow(const VectorArray &arg, double power);
VectorArray transpose(const Vector &arg);
VectorArray operator*(const Vector &lhs, const VectorArray &rhs);

#endif
