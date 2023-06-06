#include<random>
#include<iostream>

int main(void){
  std::random_device rnd;
  std::mt19937 mt(rnd());
  std::normal_distribution<> normDist(0.0, 1.0);

  const int dimension=2, eachDataNum=50, clusterNum=2;
  const double means[clusterNum][dimension]={
    {-1,-1},{1,1}};
  const double stddevs[clusterNum][dimension]={
    {0.3,0.3},{0.3,0.3}};

  std::cout << eachDataNum*clusterNum << "\t" << dimension << std::endl;

  for(int i=0;i<clusterNum;i++){
    for(int k=0;k<eachDataNum;k++){
      for(int ell=0;ell<dimension;ell++){
	std::cout << normDist(mt)*stddevs[i][ell]+means[i][ell] << "\t";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
