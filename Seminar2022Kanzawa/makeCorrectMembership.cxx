#include<iostream>

int main(void){
  const int eachDataNum[]={50, 50};
  const int clusterNum=sizeof(eachDataNum)/sizeof(eachDataNum[0]);

  for(int i=0;i<clusterNum;i++){
    int pos=0;
    for(int j=0;j<clusterNum;j++){
      if(i==j){
	for(int k=pos;k<eachDataNum[i];k++){
	  std::cout << 1 << "\t";
	}
      }
      else{
	for(int k=pos;k<eachDataNum[i];k++){
	  std::cout << 0 << "\t";
	}
      }
    }
    std::cout << std::endl;
    pos=eachDataNum[i];
  }//i
  return 0;
}
