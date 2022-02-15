/*

This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment 2 : Fibonacci numbers using recursion

Authors :   Prakhar Mathur   1906328
			Sanjay Marreddi  1904119
			Rishabh Tripathi 1904129


Date: 9th February 2021

This file contains program of a recursive function that computes the nth Fibonacci number F(n), Time taken to compute it - T(n)
and saves n, logarithm of Fn and logarithm of T(n) into a csv file.

*/

// Including all the required Libraries and Namespaces.
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

// Defining a short name for the below data type.
typedef long long int ll_int;

// Function for calculating the nth Fibonacci number.
ll_int fibonacci(ll_int n)
{

	// 	Base Step using Initial conditions.
	if (n == 0)
		return 0;

	if (n == 1)
		return 1;

	// Recursive step
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{

	// Creating a new file to output the computed values.
	FILE *fp = fopen("fibonacci_output_1906328_1904119_1904129.csv", "w");

	if (fp == NULL)
		printf("Sorry! Unable to create/open the file");

	fprintf(fp, "n,log(nth_fibonacci_number),log(time_taken)\n");

	int N = 40;

	// Looping for first N Numbers of the fibonacci series.
	for (int n = 1; n <= N; n++)
	{

		// Noting the start time of execution.
		clock_t start_time = clock();

		// Calling the Fibonacci Function.
		ll_int nth_fibonacci = fibonacci(n);

		// Noting the End time of execution.
		clock_t end_time = clock();

		// Converting system clock(time taken in the process) into `seconds.`
		double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;

		// Writing the computed values into the csv file.
		fprintf(fp, "%d,%f,%f\n", n, log(nth_fibonacci), log(time_taken));

		// Note that since `time taken` is very less, we get negative values for `log(time_taken)`.
	}

	fclose(fp);
	return (0);
}
