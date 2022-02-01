/*

This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment 1 : Sorting (Quick Sort)

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 3rd February 2021             

This file contains a C++ program that for every i ∈ {1, 2, 3, . . . , k}, takes a random integer array of n n = 2^i, 
and  computes the time T(n) taken by our quicksort function to process it and saves (i, 2^i, T(2^i), i*2^i, c_i)
for each `i` on a new row into a csv file.

*/

// Including all the required Libraries and Namespaces.
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <map>
using namespace std;
using namespace std::chrono;


// Defining a short name for the below data type.
typedef long long int ll;

// Function that swaps two integers.
void swap( int *x, int * y){
    int * temp = y;
    *y = *x;
    *x = *temp;
}


// Partitioning using Lomuto Partition Scheme Algorithm
int Partition(int a[],int low, int high){
    
    // Choosing the last element as Pivot
    int piv = a[high];
    int i = low -1 ;

    for (int j = low ; j < high; j++){
        if (a[j] <= piv){
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i+1], a[high]);

    // Returning the pivot position after partitioning the array accordingly.
    return i+1;

}


/*
Simple_QuickSort : It takes the array & performs sorting into ascending order using Simple Quick Sort, i.e. 
it always takes Last element as Pivot. So the Worst case time complexity is O(n^2) 
*/
void Simple_QuickSort(int a[], int low, int high){

    if ( low < high){
        int pivot = Partition(a, low, high);
        Simple_QuickSort(a, low, pivot-1);
        Simple_QuickSort(a,pivot+1,high);
    }

}


// Partitioning using Median-of-3 method i.e. we choose 3 random integers from the array and then
// compute the median of them and use it as pivot. 
int Randomized_Partition(int a[],int low, int high){

    srand(time(NULL));  

    map<int, int> m;
    
    for (int i = 0;  i <3 ; i++ ){

        // Choosing index randomly.   
        int temp = rand()%(high-low)+low;

        m.insert(make_pair(a[temp],temp));
    }

    // Finding the Median of the elements present at the above 3 indices 
    int pivot_index = next(m.begin())->second;
    
    swap(a[low],a[pivot_index]);

    return Partition(a,low, high);
}


/*
quicksort : It takes the array & performs sorting into ascending order using Quick Sort. 
It is an improved variant of Quicksort that chooses the Pivot using  Median-of-3 Method. 
It almost avoids the worst cases which occur in normal Quick Sort and thus has time Complexity of O(nlogn).  
*/
void quicksort(int a[], int low, int high){

    if ( low < high){
        int pivot = Randomized_Partition(a, low, high);
        Simple_QuickSort(a, low, pivot-1);
        Simple_QuickSort(a,pivot+1,high);
    }

}

int main(){

    // Creating a new file to output the computed values.
    FILE *fp = fopen("quicksort_output_1906328_1904119_1904129.csv","w");

    fprintf(fp," i, 2^i, T(2^i), i*2^i, c_i \n");
    
    if(fp==NULL) printf("Sorry! Unable to create/open the file");
    
    int k = 17;
    long double constant_c_i_List[k];
 

    for( int i=1; i<=k; ++i ){

        // `time(NULL)` sets the seed based on the current time. So, in each iteration it will give different random number.
        srand(time(NULL));

        ll n = pow(2,i);

        int a[n];
        
        for(int j = 0; j<n;++j){ 
            
            // Random numbers are choosen between -1000 to 1000.
            a[j] = ( (-1000) + rand() % (1000 - (-1000) + 1 )) ;

        }

        // Noting the start time of execution.
        auto start_time = high_resolution_clock::now();  

     
        // Calling the Quick Sort Function on this random integer Array.
        quicksort(a, 0, n-1);
        
    
        // Noting the End time of execution.
        auto end_time = high_resolution_clock::now();   
        

        // Calculating time taken to process the array and convert it into microseconds.
        auto duration = duration_cast<microseconds>(end_time - start_time);  
        
        ll nlogn_value = i*n;
        
        ll duration_micro_sec = (duration.count());

        long double constant_c_i = ( (long double)duration_micro_sec/nlogn_value );
        
        constant_c_i_List[i] = constant_c_i;

        // Writing the computed values into the csv file.
        fprintf(fp, " %d, %lld, %lld, %lld, %Lf \n", i, n, duration_micro_sec, nlogn_value, constant_c_i);
    }

    long double Expectation = 0;
    long double Variance = 0;

    // Calculating the Expectation and Variance of c_i's and writing into the csv file.
    for(int j = 5; j < k; ++j){
        Expectation = Expectation + (constant_c_i_List[j]/(k-4)); 
    }

    for (int j = 5; j < k; ++j){
		Variance = Variance + (pow((constant_c_i_List[j]-Expectation),2)/(k-4));
	}
	
	fprintf(fp,"\nThe Expected Value of c_i's is %Lf ms\n",Expectation);
	fprintf(fp,"The Variance of c_i's is %Lf ms^2\n",Variance);

    fclose(fp);
    return 0;
}
