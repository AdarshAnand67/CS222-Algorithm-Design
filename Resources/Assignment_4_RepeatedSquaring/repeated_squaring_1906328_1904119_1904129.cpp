/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment 4 : Fibonacci series using repeated squaring

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 26rd February 2021             

This file contains a C++ program that which prints first 40 fibonacci numbers using the method of repeated squaring of matrices.
*/

// Including all the required Libraries and Namespaces.
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <cstring>
using namespace std;
using namespace std::chrono;

// Short hand notation of the below data type.
typedef long long int ll_int;

/*
Function for 2x2 matrix multipilication.
Assuming M(n) is the time complexity of multiplying two integers of n bits,
We can say Time complexity of this Multiplication function is O(M(n)) 
*/
void multiply(ll_int a[2][2],ll_int b[2][2], ll_int c[2][2]){
	
	c[0][0]=(a[0][0]*b[0][0])+(a[0][1]*b[1][0]);
	
	c[0][1]=(a[0][0]*b[0][1])+(a[0][1]*b[1][1]);
	
	c[1][0]=(a[1][0]*b[0][0])+(a[1][1]*b[1][0]);
	
	c[1][1]=(a[1][0]*b[0][1])+(a[1][1]*b[1][1]);
	
}

// Function that calculates the nth power of the matrix using repeated square method.
void X_power_n(ll_int (&base_matrix)[2][2] ,ll_int (&output)[2][2], int n){

	// Variable initialization
	ll_int prod[2][2] = {{1,0},{0,1}};
	
	// Looping for dividing power into bits representation.
	while(n > 0){

		if (n%2 == 1){
			
			// Multiplying that powers of X into final product which sum up to n.
			ll_int intermediate[2][2] = {{1,0},{0,1}};
			
			// Calling multiply function for multiplying prod matrix to base matrix.
			multiply(prod, base_matrix, intermediate);
	
			// Copying into final product.
			memcpy (prod,intermediate, 2*2*sizeof(ll_int));
			
			}
	
		n = (n/2);
		
		ll_int intermediate_2[2][2] = {{1,0},{0,1}};
		
		// Calling multiply function for squaring the base matrix.
		multiply( base_matrix, base_matrix, intermediate_2);
		
		// Copying into final product.
		memcpy (base_matrix, intermediate_2, 2*2*sizeof(ll_int));
		
	}	
		
	// Copying final product to output 
	memcpy (output, prod, 2*2*sizeof(ll_int));

}

// Function that calculates the n-th fibonacci number using the repeated squaring of a matrix method.
void fibonacci(int n){
	
	// Let us call the Base Matrix as X
	ll_int X[2][2] = {{0,1},{1,1}};
	
	ll_int Final[2][2]= {{0,0},{0,0}} ;
	
	// Evaluating the nth power of matrix X.
	X_power_n( X, Final, n);
	
	// Printing the nth fibonacci number.
	printf("%ld\n",Final[0][1]);
	
}

int main(){
	
	// For printing the values of first 40 fibonacci numbers.
	for (int n = 0; n < 40; n++){
			fibonacci(n);
	}
	return 0;
}
