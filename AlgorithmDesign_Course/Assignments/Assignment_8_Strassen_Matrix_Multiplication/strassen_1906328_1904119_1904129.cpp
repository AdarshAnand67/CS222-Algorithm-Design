/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment  8 : Strassen’s matrix multiplication

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 18th April 2021

This file contains a recursive function which, on an input of two n × n matrices, outputs their
product using Strassen’s method. It uses Divide and Conquer Paradigm. 
*/


// Including all the required Libraries and Namespaces.
#include<iostream>
#include<cstdlib>
#include<vector>
#include<chrono>
#include<cmath>
using namespace std;
using namespace std::chrono;

// Defining a shortname for a datatype of vector of integers. (Similar to 1D array)
typedef vector< int > vi;

// Defining a shortname for a datatype of vector of vector of integers. (Similar to 2D array)
typedef vector< vi  > vvi;


// It is used to generate matrix where the entries are allowed to be 0 or 1.
void matrix_generator(int n, vector<vi > &matrix ){
	for (int x = 0; x<n; x++){
		for (int y = 0; y<n; y++){

			// Reminder obtained upon dividing an integer by 2 is either 0/1
			matrix[x][y] = rand() % 2; 
		}
	}
}


// It is used to divide the given matrix (say of n*n) into 4 equal parts each of (n/2)*(n/2)
void matrix_disassembler(int n, vvi &input_matrix, vvi &part1, vvi &part2, vvi &part3, vvi &part4) {

	for (int i = 0; i < n; i++){
		for (int j=0; j < n; j++){

			part1[i][j] = input_matrix[i][j];
			 
			part2[i][j] = input_matrix[i][j+n];
			 
			part3[i][j] = input_matrix[i+n][j];
			 
			part4[i][j] = input_matrix[i+n][j+n];
			 
		}
	}
	 	
}


// It is used to combine the given 4 equal matrices each of (n/2)*(n/2) into a matrix of n*n 
void matrix_assembler(int n, vvi &input_matrix, vvi &part1, vvi &part2, vvi &part3, vvi &part4) {

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			input_matrix[i][j] = part1[i][j];
			 
			input_matrix[i][j+n] = part2[i][j];
			 
			input_matrix[i+n][j] = part3[i][j];
			 
			input_matrix[i+n][j+n] = part4[i][j];
			 
		}
	}
	 	
}


// It is used to add the given 2 input matrices and saves the result into the output matrix.
void adder(int n, vvi &input_matrix_1, vvi &input_matrix_2, vvi &output_matrix){
	for (int i = 0; i  < n; i++ ){
		for (int j = 0; j  < n; j++ ){
			output_matrix[i][j] = input_matrix_1[i][j]+input_matrix_2[i][j];
		}
	}
}


// It is used to negate the values in the given matrix.
void negator(int n, vvi &input_matrix, vvi &output_matrix){
	for (int i = 0; i  < n; i++ ){
		for (int j = 0; j  < n; j++ ){
			output_matrix[i][j] = (-1)*(input_matrix[i][j]);
		}
	}
}


// This just prints the matrix.
void matrix_print(int n, vvi &matrix){

	for (int i=0; i < n; i++){
		for (int j=0; j < n; j++){
			printf("%d",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}


// It is used to multiply the given 2 input matrices and saves the result into the output matrix by using
// Strassen's Multiplication method with Divide and Conquer paradigm. 
void strassen_multiplier(int n, vvi &mat1, vvi &mat2, vvi &output_matrix){

	// Base Case 
	if (n == 1){
		output_matrix[0][0] = mat1[0][0]*mat2[0][0];
		return;
	}
	
	// Base Case 
	if (n == 2){
		int p1,p2,p3,p4,p5,p6,p7;
		
		p1 = (mat1[0][0])*(mat2[0][1] - mat2[1][1]);
		p2 = (mat1[0][0] + mat1[0][1])*(mat2[1][1] );
		p3 = (mat1[1][0] + mat1[1][1])*(mat2[0][0]);
		p4 = (mat1[1][1])*(-mat2[0][0] + mat2[1][0]);
		p5 = (mat1[0][0] + mat1[1][1])*(mat2[0][0] + mat2[1][1]);
		p6 = (mat1[0][1] - mat1[1][1])*(mat2[1][0] + mat2[1][1]);
		p7 = (mat1[0][0] - mat1[1][0])*(mat2[0][0] + mat2[0][1]);
		
		output_matrix[0][0] = p5+p4-p2+p6;
		output_matrix[0][1] = p1+p2;
		output_matrix[1][0] = p3+p4;
		output_matrix[1][1] = p1+p5-p3-p7;
	}

	// Recursive Step
	else{
		
		// Initialising the 2d vectors for storing the 4 parts of matrix1.
		vvi  mat1_part1( n/2 ,vi (n/2, 0) );
		vvi  mat1_part2( n/2 ,vi (n/2, 0) );
		vvi  mat1_part3( n/2 ,vi (n/2, 0) ); 
		vvi  mat1_part4( n/2 ,vi (n/2, 0) );
		
		// Disassembling the matrix 1 into 4 symmetrical parts.
		matrix_disassembler(n/2, mat1, mat1_part1, mat1_part2, mat1_part3, mat1_part4);

		// Initialising the 2d vectors for storing the 4 parts of matrix2.
		vvi mat2_part1( n/2 ,vi (n/2, 0) );
		vvi mat2_part2( n/2 ,vi (n/2, 0) );
		vvi mat2_part3( n/2 ,vi (n/2, 0) ); 
		vvi mat2_part4( n/2 ,vi (n/2, 0) );

		// Disassembling the matrix 1 into 4 symmetrical parts.
		matrix_disassembler(n/2, mat2, mat2_part1, mat2_part2, mat2_part3, mat2_part4);

		// Initialising the 2d vectors for computing the 7 parts of the multiplication algo.
		vvi prod1( n/2 ,vi (n/2, 0) );
		vvi prod2( n/2 ,vi (n/2, 0) );
		vvi prod3( n/2 ,vi (n/2, 0) ); 
		vvi prod4( n/2 ,vi (n/2, 0) ); 
		vvi prod5( n/2 ,vi (n/2, 0) ); 
		vvi prod6( n/2 ,vi (n/2, 0) );
		vvi prod7( n/2 ,vi (n/2, 0) );
		
		// Initialising the 2d vectors
		vvi added1( n/2 ,vi (n/2, 0) );
		vvi added2( n/2 ,vi (n/2, 0) );
		vvi added3( n/2 ,vi (n/2, 0) ); 
		vvi added4( n/2 ,vi (n/2, 0) ); 
		vvi added5( n/2 ,vi (n/2, 0) );
		vvi added6( n/2 ,vi (n/2, 0) );
		vvi added7( n/2 ,vi (n/2, 0) );
		vvi added8( n/2 ,vi (n/2, 0) );
		vvi added9( n/2 ,vi (n/2, 0) );
		vvi added10( n/2 ,vi (n/2, 0) );
		
		// Initialising the 2d vectors
		vvi negative1( n/2 ,vi (n/2, 0) );
		vvi negative2( n/2 ,vi (n/2, 0) );
		vvi negative3( n/2 ,vi (n/2, 0) );
		vvi negative4( n/2 ,vi (n/2, 0) );

		// P1 =  mat1_part1*(mat2_part2 - mat2_part4)
		negator(n/2, mat2_part4, negative1);
		adder(n/2, mat2_part2, negative1, added1);
		strassen_multiplier(n/2, mat1_part1, added1, prod1);
		
		// P2 =  mat2_part4*(mat1_part1 + mat1_part2)
		adder(n/2,mat1_part1,mat1_part2,added2);
		strassen_multiplier(n/2,added2,mat2_part4,prod2);
		
		// P3 =  mat2_part1*(mat1_part3 + mat1_part4)
		adder(n/2,mat1_part3,mat1_part4,added3);
		strassen_multiplier(n/2,added3,mat2_part1,prod3);
		
		// P4 =  mat1_part4*(mat2_part3 - mat2_part1)
		negator(n/2,mat2_part1,negative2);
		adder(n/2,negative2,mat2_part3,added4);
		strassen_multiplier(n/2,mat1_part4,added4,prod4);
		
		// P5 =  ( mat1_part1 + mat1_part4 )*( mat2_part1 + mat2_part4 )
		adder(n/2,mat1_part1,mat1_part4,added5);
		adder(n/2,mat2_part1,mat2_part4,added6);
		strassen_multiplier(n/2,added5,added6,prod5);
		
		// P6 =  ( mat1_part2 - mat1_part4 )*( mat2_part3 + mat2_part4 )
		negator(n/2,mat1_part4,negative3);
		adder(n/2,mat1_part2,negative3,added7);
		adder(n/2,mat2_part3,mat2_part4,added8);
		strassen_multiplier(n/2,added7,added8,prod6);
		
		// P7 =  ( mat1_part1 - mat1_part3 )*( mat2_part1 + mat2_part2 )
		negator(n/2,mat1_part3,negative4);
		adder(n/2,mat1_part1,negative4,added9);
		adder(n/2,mat2_part1,mat2_part2,added10);
		strassen_multiplier(n/2,added9,added10,prod7);
		
		// Initialising the 2d vectors.
		vvi added11( n/2 ,vi (n/2, 0) );
		vvi added12( n/2 ,vi (n/2, 0) );
		vvi added13( n/2 ,vi (n/2, 0) );
		vvi added14( n/2 ,vi (n/2, 0) );
		vvi added15( n/2 ,vi (n/2, 0) );
		vvi added16( n/2 ,vi (n/2, 0) );
		vvi added17( n/2 ,vi (n/2, 0) );
		vvi added18( n/2 ,vi (n/2, 0) );
		vvi negative5( n/2 ,vi (n/2, 0) );
		vvi negative6( n/2 ,vi (n/2, 0) );
		vvi negative7( n/2 ,vi (n/2, 0) );
			
		// P5 + P4 + P6 - P2
		negator(n/2,prod2,negative5);
		adder(n/2,prod5,prod4,added11);
		adder(n/2,prod6,negative5,added12);
		adder(n/2,added11,added12,added13);

		// P1 + P2
		adder(n/2,prod1,prod2,added14);
		
		// P3 + P4
		adder(n/2,prod3,prod4,added15);
		
		// P1 + P5 - P3 -P7
		negator(n/2,prod3,negative6);
		negator(n/2,prod7,negative7);
		adder(n/2,prod5,prod1,added16);
		adder(n/2,negative6,negative7,added17);
		adder(n/2,added16,added17,added18);
		
		// Assembling the final matrix
		matrix_assembler(n/2, output_matrix,added13,added14,added15,added18);
	}
	
}



int main(){
	
	for (int k = 1; k <= 8; k++){

		int n = pow(2,k);

	    // `time(NULL)` sets the seed based on the current time. So, in each iteration it will give different random number.
        srand(time(NULL));
        
        vvi  input_matrix_1( n ,vi (n, 0) );
		matrix_generator(n, input_matrix_1);
		
		vvi  input_matrix_2( n ,vi (n, 0) );
	    matrix_generator(n, input_matrix_2);
	    
	    vvi  output_matrix( n ,vi (n, 0) );
		
		// Noting the start time of execution.
        auto start_time = high_resolution_clock::now();  
        
		// Calling the function to start multiplication.
	    strassen_multiplier(n, input_matrix_1, input_matrix_2, output_matrix);
		
	    // Noting the end time of execution.
        auto end_time = high_resolution_clock::now();   
		
        // Calculating time taken to process the array and convert it into microseconds.
        auto duration = duration_cast<microseconds>(end_time - start_time);  
        
		double exec_time = duration.count()/1e6;
		
		double nlog7 = pow(n,(log(7)/log(2)));

		printf("n = %d, \t execution time(sec) = %0.6f,\t n^log(7) = %0.6f,\t ratio = %0.8f\n",n,exec_time,nlog7,(exec_time/(nlog7)));
		
	}
}