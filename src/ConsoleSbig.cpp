#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>


using namespace std;


int main(){
	
	time_t timer1, timer2, timer3, timer4;


	timer1 = time(NULL);
	for(int k=0; k<100000000; ++k){
		std::vector<int> v;
		for(int i=0; i<1000; ++i)
			v.push_back(i);
	}
	timer2 = time(NULL);
	
	cout << "C++11 allocation time: " << difftime(timer1,timer2) << endl;

	timer3 = time(NULL);
	for(int k=0; k<100000000; ++k){
		int * v2;
		v2=(int*)malloc(1000*sizeof(int));
		for(int i=0; i<1000; ++i)
			v2[i]=i;
		delete(v2);
	}
	timer4 = time(NULL);
	
	cout << "malloc allocation time: "<< difftime(timer3,timer4) << endl;




	return 0;
}





