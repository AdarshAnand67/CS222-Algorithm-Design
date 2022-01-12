/*
This code is written as a part of Ctemp22-Algorithm Design Course under Dr. Aripta Korwar.

Assignment  7 : Extended Euclid's algorithm

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 11th April 2021

This file contains a recursive program in C++ that takes a and b as input from the user and
outputs gcd(a, b) and the integers x, y such that gcd(a, b) = ay + bx
*/


// Including all the required Libraries and Namespaces.
#include <iostream>
#include <utility>
using namespace std;


// Defining a Structure that stores the values of x,y,gcd in the equation gcd(a,b) = a*y + b*x.
struct coefficients{  
	int x = 0;  
	int y = 0;
	int gcd_value = 0;
};


/*
Defining a divide function that takes two input integers and returns a pair consisting of quotient (q) and reminder(r).
Note: The `pair` is a simple C++ container defined in <utility> header consisting of two data elements.
*/
pair<int,int> divide(int a, int b){

        if ( a == 0 ) {
            return make_pair(0,0);
        }

        pair<int,int> result = divide( a/2, b );

        result.first  = 2* result.first;
        result.second = 2* result.second;

        if ( a%2 == 1 ){
             result.second= result.second+1;
        }
        if ( result.second >= b) {
             result.first++ ;
             result.second -= b;
        }

        return  result;
}


/*
Defining a `gcd` function that takes two input integers and returns a struct consisting of coefficients 
of input integers in Euclids Extended Algo, i.e. It returns x,y,gcd in the equation gcd(a,b) = a*y + b*x
*/
struct coefficients gcd(int a,int b){

	// Swapping numbers.
	if ( b>a ){
		coefficients ans, temp;
		temp = gcd(b,a);
		ans.x = temp.y;
		ans.y = temp.x;
		ans.gcd_value = temp.gcd_value;
		return ans;
	}

	// If the Input numbers are negative.
	if ( ( a <= 0) || (b < 0) ){
		printf("ERROR! Wrong Input, Please enter positive integers");
		struct coefficients empty;
		return empty;
	}

	// Base Case
	if (b == 0 ){
		struct coefficients ans;
		ans.y = 1;
		ans.x = 0;
		ans.gcd_value = a;
		return ans;
	}

	struct coefficients temp, ans;

	// Using the theorem `gcd(a,b) = gcd(b,r)` where a = bq + r.
	auto div_result = divide(a,b); 

	// div_result has first element as quotient & second element as reminder.
	temp = gcd(b, div_result.second);

	// Updating the values of coefficients.
	ans.y = temp.x;
	ans.x = temp.y + (-div_result.first)*(temp.x);
	ans.gcd_value = temp.gcd_value;

	return ans;
}

int main(){
	
	int a, b;
	printf("Input the two numbers: ");
	scanf("%d %d",&a,&b); 

	struct coefficients result = gcd(a, b);
	printf("\nThe gcd of %d and %d is %d.\n", a, b, result.gcd_value);
	printf("\n");

	printf("Using extended Euclids algorithm to represent as gcd(a, b) = ay + bx\n");
	printf("\n");

	printf("%d = (%d)*%d + (%d)*%d\n", result.gcd_value, result.y, a, result.x, b);
}
