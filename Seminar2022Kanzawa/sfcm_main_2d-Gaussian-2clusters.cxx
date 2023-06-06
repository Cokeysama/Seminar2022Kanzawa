#include<iostream>
#include<fstream>
#include<cstdlib>
#include<random>
#include"sfcm.h"

#define MAX_ITERATES 100000
#define DIFF_FOR_STOP 1.0E-10

const int centers_number=2;

int main(void){
  std::string filenameData("2d-Gaussian-2clusters.dat");
#ifdef CHECK_ANSWER
  std::string filenameCorrectCrispMembership("2d-Gaussian-2clusters.correctCrispMembership");
#endif

  std::string::size_type filenameDataDotPosition=filenameData.find_last_of(".");
  if(filenameDataDotPosition==std::string::npos){
    std::cerr << "File:" << filenameData
	      << " needs \".\" and filename-extention." << std::endl;
    exit(1);
  }

  std::ifstream ifs(filenameData);
  if(!ifs){
    std::cerr << "File:" << filenameData
	      << " could not open." << std::endl;
    exit(1);
  }
  int data_number, data_dimension;
  ifs >> data_number;
  ifs >> data_dimension;
	
  Sfcm test(data_dimension, data_number, centers_number, 2.0);

  for(int cnt=0;cnt<data_number;cnt++){
    for(int ell=0;ell<data_dimension;ell++){
      ifs >> test.data(cnt, ell);
    }
  }

  /***Initial Centers Setting***/
  std::random_device rnd;
  std::mt19937 mt(rnd());
  std::uniform_int_distribution<> randDataNumber(0,test.data_number()-1);
  for(int i=0;i<test.centers_number();i++){
    test.centers(i)=test.data()[randDataNumber(mt)];
  }
#ifdef VERBOSE
  std::cout << "v:\n" << test.centers() << std::endl;
#endif

  test.iterates()=0;
  while(1){
    test.revise_dissimilarities();
#ifdef VERBOSE
    std::cout << "d:\n" << test.dissimilarities() << std::endl;
#endif
    test.revise_membership();
#ifdef VERBOSE
    std::cout << "u:\n" << test.membership() << std::endl;
#endif
    test.revise_centers();
#ifdef VERBOSE
    std::cout << "v:\n" << test.centers() << std::endl;
#endif

    double diff_u=max_norm(test.tmp_membership()-test.membership());
    double diff_v=max_norm(test.tmp_centers()-test.centers());
    double diff=diff_u+diff_v;
#ifdef DIFF
    std::cout << "#diff:" << diff << "\t";
    std::cout << "#diff_u:" << diff_u << "\t";
    std::cout << "#diff_v:" << diff_v << "\n";
#endif
    if(diff<DIFF_FOR_STOP)break;
    if(test.iterates()>=MAX_ITERATES)break;
    test.iterates()++;
  }
#ifdef VERBOSE
  std::cout << "v:\n" << test.centers() << std::endl;
#endif

#ifdef CHECK_ANSWER
  test.set_crispMembership();

  std::ifstream ifs_correctCrispMembership(filenameCorrectCrispMembership);
  if(!ifs_correctCrispMembership){
    std::cerr << "File:" << filenameCorrectCrispMembership
	      << " could not open." << std::endl;
    exit(1);
  }
  for(int i=0;i<test.centers_number();i++){
    for(int k=0;k<test.data_number();k++){
      ifs_correctCrispMembership >> test.correctCrispMembership(i, k);
    }
  }
  test.set_contingencyTable();
  std::cout << "Contingency Table:\n" << test.contingencyTable() << std::endl;
  std::cout << "ARI:" << test.ARI() << std::endl;
#endif
  
  std::string filenameResultMembership
    =std::string("sFCM-Em")+std::to_string(test.fuzzifierEm())+std::string("-")
    +filenameData.substr(0, filenameDataDotPosition)
    +std::string(".result_membership");
  std::ofstream ofs_membership(filenameResultMembership);
  if(!ofs_membership){
    std::cerr << "File:" << filenameResultMembership
	      << "could not open." << std::endl;
    exit(1);
  }

  for(int k=0;k<test.data_number();k++){
    for(int ell=0;ell<test.dimension();ell++){
      ofs_membership << test.data()[k][ell] << "\t";
    }
    for(int i=0;i<test.centers_number();i++){
      ofs_membership << test.membership()[i][k] << "\t";
    }
    ofs_membership << std::endl;
  }
  ofs_membership.close();

  std::string filenameResultCenters
    =std::string("sFCM-Em")+std::to_string(test.fuzzifierEm())+std::string("-")
    +filenameData.substr(0, filenameDataDotPosition)
    +std::string(".result_centers");
  std::ofstream ofs_centers(filenameResultCenters);
  if(!ofs_centers){
    std::cerr << "File:" << filenameResultCenters
	      << "could not open." << std::endl;
    exit(1);
  }
  for(int i=0;i<test.centers_number();i++){
    for(int ell=0;ell<test.dimension();ell++){
      ofs_centers << test.centers()[i][ell] << "\t";
    }
    ofs_centers << std::endl;
  }
  ofs_centers.close();

#ifdef CLASSIFICATION_FUNCTION
  //Classification Function
  if(test.dimension()>2){
    std::cerr << "Dimension:" << test.dimension()
	      << "is too high for classification function visualization."
	      << std::endl;
    exit(1);
  }
  Sfcm ClassFunction(test.dimension(), 1, test.centers_number(), test.fuzzifierEm());
  std::string filenameClassificationFunction
    =std::string("sFCM-Em")+std::to_string(test.fuzzifierEm())+std::string("-")
    +filenameData.substr(0, filenameDataDotPosition)
    +std::string(".result_classificationFunction");
  std::ofstream ofs_classificationFunction(filenameClassificationFunction);
  if(!ofs_classificationFunction){
    std::cerr << "File:" << filenameClassificationFunction
	      << "could not open." << std::endl;
    exit(1);
  }
  for(int i=0;i<test.centers_number();i++){
    ClassFunction.centers(i)=test.centers(i);
  }
  Vector Min(test.dimension(), DBL_MAX, "all");
  Vector Max(test.dimension(), -DBL_MAX, "all");
  for(int k=0;k<test.data_number();k++){
    for(int ell=0;ell<test.dimension();ell++){
      if(Min[ell]>test.data(k, ell)){
	Min[ell]=test.data(k, ell);
      }
      if(Max[ell]<test.data(k, ell)){
	Max[ell]=test.data(k, ell);
      }
    }
  }
  Vector Mid=0.5*(Max+Min);
  Vector Width=Max-Min;
  Min=Mid-Width;
  Max=Mid+Width;

  for(double x0=Min[0];x0<=Max[0];x0+=Width[0]/10.0){
    for(double x1=Min[1];x1<=Max[1];x1+=Width[1]/10.0){
#ifdef VERBOSE
      std::cout << "x0:" << x0 << "\t" << "x1:" << x1 << std::endl;
#endif
      ClassFunction.data(0,0)=x0;
      ClassFunction.data(0,1)=x1;
      while(1){
	ClassFunction.revise_dissimilarities();
	ClassFunction.revise_membership();
	double diff_u=frobenius_norm(ClassFunction.tmp_membership()-ClassFunction.membership());
#ifdef DIFF
	std::cout << "diff_u:" << diff_u << std::endl;
#endif
	if(diff_u<DIFF_FOR_STOP)break;
      }
      for(int ell=0;ell<ClassFunction.dimension();ell++){
	ofs_classificationFunction << ClassFunction.data()[0][ell] << "\t";
      }
      for(int i=0;i<ClassFunction.centers_number();i++){
	ofs_classificationFunction << ClassFunction.membership()[i][0] << "\t";
      }
      double max=0.0;
      for(int i=0;i<ClassFunction.centers_number();i++){
	if(max<ClassFunction.membership()[i][0]){
	  max=ClassFunction.membership()[i][0];
	}
      }
      ofs_classificationFunction << max << "\t";
      ofs_classificationFunction << std::endl;
    }
    ofs_classificationFunction << std::endl;
  }

#endif

  return 0;
}
