#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>


int main(int argc, char** argv){

	double pi_ref = 3.14159265359;

	if(argc != 2){
		std::cerr << "Needs number of iteration for loop!!" << std::endl;
		return 1;
	}
	time_t t0 = time(0);
	size_t num_iter = atol(argv[1]);

	double in_count=0;

	srand (time(NULL));

  int tid=0;

	#pragma omp parallel for  
 	for(size_t i=0; i<num_iter;++i){

    if(i==0) tid = omp_get_num_threads();
 
 		double x = ((double) rand() / (RAND_MAX));
 		double y = ((double) rand() / (RAND_MAX));
 
 		if(sqrt(x*x + y*y) <= 1){
      #pragma omp atomic
      in_count++;
    }
 	}
	double pi=4.0*( in_count / num_iter) ;

	std::cout << std::fixed << std::setprecision(8);

	std::cout <<  "pi= ";
	std::cout << std::setprecision(10);
	std::cout << std::fixed << pi << std::endl;
	std::cout << "Error wrt reference: " << std::scientific << pi - pi_ref << std::endl;
  time_t t1 = time(0);
	std::cout << "This took " << std::setprecision(3) << std::fixed <<  difftime(t1, t0) << " s running on " << tid << " thread(s)" << std::endl; 

		
	return 0;
}
	
