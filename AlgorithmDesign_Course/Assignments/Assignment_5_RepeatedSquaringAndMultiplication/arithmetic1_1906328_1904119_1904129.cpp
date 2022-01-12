/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment 5 : Multiplication and Repeated Squaring

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 3rd March 2021             

This file contains a C++ program that defines multiply and exponential functions and computes the value of given expression.
*/

// Including all the required Libraries and Namespaces.
#include <iostream>
using namespace std;

// Defining a short name for the below data type.
typedef long long int ll;

// A Recursive function that computes product of two non negative integers.
ll multiply( ll x, ll y){

	// Base Case
	if ( y == 1 ) return x;

	// If y is odd
	if ( y%2 == 1 ) return ( x + 2*multiply(x,y/2) );

	// If y is even
	if ( y%2 == 0 ) return ( 2*multiply(x,y/2) );
	
	return 0;
}


// A Recursive function that calculates the power given two positive integers using repeated squaring method.
ll exponential(ll a,ll b){
	
	// Base Case
	if ( b==0 ) return 1;
	
	// If b is odd
	if ( b%2 == 1 ) return (a*exponential(a,b/2)*exponential(a,b/2));
	
	// If b is even
	if ( b%2 == 0 ) return (exponential(a,b/2)*exponential(a,b/2));
	
	return 0;
}


int main(){

	// Variable declaration
	ll a,b,c,d,result;

	// Taking Input from the user.
	printf("Enter value for a: ");
	scanf("%lld",&a);
	printf("Enter value for b: ");
	scanf("%lld",&b);
	printf("Enter value for c: ");
	scanf("%lld",&c);
	printf("Enter value for d: ");
	scanf("%lld",&d);

	// Calculating the required quantity by calling corrsponding defined functions. 
	result = multiply(exponential(a,b),exponential(c,d));

	printf("The required quantity : (a^b)*(c^d) = %lld\n",result);

}
