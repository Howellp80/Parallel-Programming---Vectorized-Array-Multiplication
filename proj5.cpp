/*******************************************************************************
* Parker Howell
* CS 475 - Project 5
* Vectorized Array Multiplication
* 5-21-18
* 
*******************************************************************************/


#include "simd.p5.h"
#include <iostream>


unsigned int seed = 0;			// seed value for rand

float *A = new float [NUMS];  // arrays to hold random values
float *B = new float [NUMS];
float *C = new float [NUMS];




// multiplies arrays A * B and stores in C
void Mult(float *A, float *B, float *C) {
    for (int i = 0; i < NUMS; i++) {
        C[i] = A[i] * B[i];
    }
}




// like above but returns the sum of array C
float MultSum(float *A, float *B){
    float sum = 0.;
    for (int i = 0; i < NUMS; i++){
        sum += A[i] * B[i];
    }
    return sum;
}




// returns random float values to populate arrays
float Ranf( unsigned int *seedp,  float low, float high ){
	float r = (float) rand_r( seedp );     // 0 - RAND_MAX

	return(low + r * (high - low) / (float)RAND_MAX);
}




// runs appropriate functions 
int main( int argc, char *argv[ ] ){

// OpenMP check
	#ifndef _OPENMP
	fprintf(stderr, "OpenMP not supported - Sorry!\n");
	#endif  


	int i;  				// for looping
	
	float total,			// for sum functions
			megaCalcs,		// for performance 
			sumMegaCalcs,
			avgMegaCalcs,	
			bestMegaCalcs;

	double 	t0,  		// for timing
				t1, 
				runTime, 
				sumTime, 
				avgTime, 
				bestTime;  


	// init arrays with random values
	for (i = 0; i < NUMS; i++){
		A[i] = Ranf(&seed, 0.1f, 1.f);
		B[i] = Ranf(&seed, 0.1f, 1.f);
	}


	// run selected function AVGRUNS times
	for(i = 0; i < AVGRUNS; i++){

		// start timer
		t0 = omp_get_wtime();

		// swithch to run proper function
		switch (FUNCTION){
			case 1: 	
						SimdMul(A, B, C, NUMS);
						break;
			case 2: 
						Mult(A, B, C);
						break;
			case 3: 
						SimdMulSum(A, B, NUMS);
						break;
			case 4: 
						MultSum(A, B);
						break;				
		}

		// stop timer
		t1 = omp_get_wtime();
		
		// process results
		runTime = (t1 - t0) * 10;
		megaCalcs = (float)NUMS / runTime / 1000000.;

		if(i == 0){
			bestTime = runTime;
			sumTime = 0.;
			bestMegaCalcs = megaCalcs;
			sumMegaCalcs = 0.;
		}

		if(runTime < bestTime)
			bestTime = runTime;

		if(megaCalcs > bestMegaCalcs)
			bestMegaCalcs = megaCalcs;

		sumTime += runTime;
		sumMegaCalcs += megaCalcs;
	}

	avgTime = sumTime / AVGRUNS;
	avgMegaCalcs = sumMegaCalcs / AVGRUNS;


	// print results
	switch (FUNCTION){
		case 1: 	
					std::cout << "SimdMul " << NUMS << std::endl;
					break;
		case 2: 
					std::cout << "Mul " << NUMS << std::endl;
					break;
		case 3: 
					std::cout << "SimdMulSum " << NUMS << std::endl;
					break;
		case 4: 
					std::cout << "MulSum " << NUMS << std::endl;
					break;				
	}

	std::cout << "Average megaCalcs: " << avgMegaCalcs 
				 << " in avg time: " << avgTime << " seconds."
				 << "   Total: " << sumTime << std::endl;
	std::cout << "Peak meagCalcs: " << bestMegaCalcs 
				 << " in peak time: " << bestTime << " seconds. " 
				 << "   Ratio: " << bestTime/avgTime  << "\n\n";
 


	return 0;
}