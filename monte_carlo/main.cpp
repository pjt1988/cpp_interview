#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <omp.h>
#include <math.h>
#include <string>
#include <vector>


int main(int argc, char** argv){

	double pi_ref = 3.14159265359;

	if(argc != 2 && argc != 3){
		printf("Needs number of iteration for loop!!\n");
		return 1;
	}
    if(std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"){
        printf("Help: \n");
        printf("        <iteration> <num threads> \n");
        return 0;
    }

	size_t num_iter = atol(argv[1]);
    int nthreads = omp_get_max_threads();
    if(argc == 3){
        int num_threads_supplied = atoi(argv[2]);
        if(num_threads_supplied > nthreads)
            printf("Too many threads requested. Staying with %i threads \n", nthreads);
        else
            nthreads = num_threads_supplied;
    }

    std::vector<size_t> in_count(nthreads,0);
    printf("we should be running %i threads \n", nthreads);

	srand (time(NULL));
    int threads_used =0;

    auto t0 = std::chrono::steady_clock::now();
	#pragma omp parallel for num_threads(nthreads) schedule(dynamic) default(shared)
 	for(size_t i=0; i<num_iter;++i){
        int tid = omp_get_thread_num();
        if(tid==0) threads_used = omp_get_num_threads();
 
 	    double x = ((double) rand() / (RAND_MAX));
 	    double y = ((double) rand() / (RAND_MAX));

 	    if(sqrt(x*x + y*y) <= 1){
           in_count[tid]++;
        }
 	}
    double total_in_count = 0.0;
    for(auto& ii : in_count) total_in_count+=double(ii);
	double pi=4.0*( total_in_count / num_iter) ;

    printf("Computed PI = %.10e \n", pi);
	printf("Error wrt reference: %.10e \n", pi-pi_ref );
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = t1 - t0;
    printf("The computation needed %.3f s running on %i thread(s)\n", elapsed.count(), threads_used);

		
	return 0;
}
	
