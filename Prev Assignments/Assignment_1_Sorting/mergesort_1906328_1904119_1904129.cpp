/*

This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment 1 : Sorting (Merge Sort)

Authors :   Prakhar Mathur   1906328
			Sanjay Marreddi  1904119
			Rishabh Tripathi 1904129

Date: 3rd February 2021

This file contains a C++ program that for every i ∈ {1, 2, 3, . . . , k}, takes a random integer array of n n = 2^i,
and  computes the time T(n) taken by our mergesort function to process it and saves (i, 2^i, T(2^i), i*2^i, c_i)
for each `i` on a new row into a csv file.

*/

// Including all the required Libraries and Namespaces.
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <map>
#include <cstring>
using namespace std;
using namespace std::chrono;

// Defining a short name for the below data type.
typedef long long int ll;

// Function for merging 2 sorted arrays.
void merge(int *array1, int *array2, int n, int m, int *array_merged)
{

	// Variable Initialisation
	int i = 0, j = 0, k = 0;

	// Loop to go through the arrays and comparing its elements.
	while (i < n and j < m)
	{

		if (array1[i] <= array2[j])
		{
			array_merged[k] = array1[i];
			i++;
		}

		else
		{
			array_merged[k] = array2[j];
			j++;
		}

		k++;
	}

	// Adding the remaining elements into the output merged array.
	for (; i < n; i++)
	{
		array_merged[k] = array1[i];
		k++;
	}

	for (; j < m; j++)
	{
		array_merged[k] = array2[j];
		k++;
	}
}

// Function for mergesort.
int *mergesort(int *arr, int n)
{

	// Base case
	if (n == 1)
	{
		return arr;
	}

	else
	{

		int array[n];
		int mid = n / 2;

		for (int v = 0; v < n; v++)
		{
			array[v] = arr[v];
		}

		// If size of given array is even.
		if (n % 2 == 0)
		{

			// Dynamically allocate memory for two halves of the array.
			int *firstHalf = (int *)malloc(mid * sizeof(int));
			int *secondHalf = (int *)malloc(mid * sizeof(int));

			// Copy the contents.
			memcpy(firstHalf, array, mid * sizeof(int));
			memcpy(secondHalf, array + mid, mid * sizeof(int));

			// Recursively, sort both the half arrays.
			int *Sorted_firstHalf = mergesort(firstHalf, mid);
			int *Sorted_secondHalf = mergesort(secondHalf, mid);

			// Merging the two sorted half arrays.
			merge(Sorted_firstHalf, Sorted_secondHalf, mid, mid, arr);

			// Free up the allocated memory.
			free(firstHalf);
			free(secondHalf);
		}

		else
		{

			// Dynamically allocate memory for two halves of the array.
			int *firstHalf = (int *)malloc(mid * sizeof(int));
			int *secondHalf = (int *)malloc((mid + 1) * sizeof(int));

			// Copy the contents.
			memcpy(firstHalf, array, mid * sizeof(int));
			memcpy(secondHalf, array + mid, (mid + 1) * sizeof(int));

			// Recursively, sort both the half arrays.
			int *Sorted_firstHalf = mergesort(firstHalf, mid);
			int *Sorted_secondHalf = mergesort(secondHalf, mid + 1);

			// Merging the two sorted half arrays.
			merge(Sorted_firstHalf, Sorted_secondHalf, mid, mid + 1, arr);

			// Free up the allocated memory.
			free(firstHalf);
			free(secondHalf);
		}
		return arr;
	}
}

int main()
{

	// Creating a new file to output the computed values.
	FILE *fp = fopen("mergesort_output_1906328_1904119_1904129.csv", "w");

	fprintf(fp, " i, 2^i, T(2^i), i*2^i, c_i \n");

	if (fp == NULL)
		printf("Sorry! Unable to create/open the file");

	int k = 17;
	long double constant_c_i_List[k];

	for (int i = 1; i <= k; ++i)
	{

		// `time(NULL)` sets the seed based on the current time. So, in each iteration it will give different random number.
		srand(time(NULL));

		ll n = pow(2, i);

		int *a = (int *)malloc(n * sizeof(int));

		for (int j = 0; j < n; ++j)
		{

			// Random numbers are choosen between -1000 to 1000.
			a[j] = ((-1000) + rand() % (1000 - (-1000) + 1));
		}

		// Noting the start time of execution.
		auto start_time = high_resolution_clock::now();

		// Calling the Quick Sort Function on this random integer Array.
		a = mergesort(a, n);

		// Noting the End time of execution.
		auto end_time = high_resolution_clock::now();

		// Calculating time taken to process the array and convert it into microseconds.
		auto duration = duration_cast<microseconds>(end_time - start_time);

		ll nlogn_value = i * n;

		ll duration_micro_sec = (duration.count());

		long double constant_c_i = ((long double)duration_micro_sec / nlogn_value);

		constant_c_i_List[i] = constant_c_i;

		// Writing the computed values into the csv file.
		fprintf(fp, " %d, %lld, %lld, %lld, %Lf \n", i, n, duration_micro_sec, nlogn_value, constant_c_i);

		free(a);
	}

	long double Expectation = 0;
	long double Variance = 0;

	// Calculating the Expectation and Variance of c_i's and writing into the csv file.
	for (int j = 5; j < k; ++j)
	{
		Expectation = Expectation + (constant_c_i_List[j] / (k - 4));
	}

	for (int j = 5; j < k; ++j)
	{
		Variance = Variance + (pow((constant_c_i_List[j] - Expectation), 2) / (k - 4));
	}

	fprintf(fp, "\nThe Expected Value of c_i's is %Lf ms\n", Expectation);
	fprintf(fp, "The Variance of c_i's is %Lf ms^2\n", Variance);

	fclose(fp);
	return 0;
}
