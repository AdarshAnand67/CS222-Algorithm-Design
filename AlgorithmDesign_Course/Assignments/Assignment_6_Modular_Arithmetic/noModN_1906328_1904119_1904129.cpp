/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment  6 : Modular arithmetic and Extended Euclid's algorithm

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 28rd March 2021

This file contains a C++ program that defines a class nModN using a C++ template with non-type parameter for N and overloads +, * and ++ Operators.
*/

// Including all the required Libraries and Namespaces.
#include <iostream>
#include <utility>
using namespace std;

// Defining a Template for class noModN with default value of non_type parameter as 10.
template<class T, int N = 10>
class noModN{

    private:
        // Data usually an integer & is kept between 0 to N-1.
        T data;    

    public:

        // Constructor.
        noModN(T x);
        noModN(T x , T y);

        // Methods for Overloading the operators.
        noModN operator +(noModN A);
        noModN operator *(noModN A);
        noModN operator ++();
        noModN operator ++(int);

        // Useful Methods in implementing the Overloading of operators.
        void print();
        bool isodd(T x);
        bool isnegative(T x);
        T multiply(T x,T y);
        pair<T,T> divide(T , T y);

        // Note: The `pair` is a simple C++ container defined in <utility> header consisting of two data elements.
};


// Returns 1 (True) if input is negative.
template<class T, int N >
bool noModN<T, N>::isnegative(T x){
    return ( x < 0 );
}


// Returns 1 (True) if the input is odd.
template<class T, int N >
bool noModN<T, N>::isodd(T x){
    return ( x % 2 );
}


// Method that just outputs the data of the Object.
template<class T, int N >
void noModN<T, N>::print(){
    cout << data << "\n";
}


// Defining a divide method that takes two input elements and returns a pair consisting of quotient (q) and reminder(r).
template<class T, int N >
pair<T,T> noModN<T, N>::divide(T a, T b){

        if ( a == 0 ) {
            return make_pair(0,0);
        }

        pair<T,T> result = divide( a/2, b );

        result.first  = 2* result.first;
        result.second = 2* result.second;

        if ( isodd(a) ){
             result.second= result.second+1;
        }
        if ( result.second >= b) {
             result.first++ ;
             result.second -= b;
        }

        return  result;
}


// Defining the Constructor. 
template<class T, int N >
noModN<T, N>::noModN(T x ){

    pair<T,T> result = divide(x, N);
    
    if(isnegative(x)) {
        data = (-1)*result.second ;}

    else {
        data = result.second;}
}


// Method for Overloading the Addition (+) Operator.
template<class T, int N >
noModN<T, N> noModN<T, N>::operator +(noModN A){
    noModN B( A.data + data );
    return B;
}


// Method for Performing Multiplication using Recursive Implementation.
template<class T, int N >
T noModN<T,N>::multiply(T x,T y){

    if ( y == 0 ) return 0;                  
                                                            
    T z = multiply ( x, y/2 );

    pair<T,T> result = divide( z, N );
    
    if(isodd(y)) {
            return x+2*result.second;
    }
    else{
        
        return 2*result.second;
    }

}


// Method for Overloading the Multiplication (*) Operator.
template<class T, int N >
noModN<T, N> noModN<T, N>::operator *(noModN A){
    
    int result  = multiply(abs(data),abs(A.data));
    
    if ( ( A.data < 0 && data >= 0 )  || ( A.data >= 0 && data < 0 ) ){ 
         result = result*(-1); 
    }

    noModN B(result);
    return B;
}


// Method for Overloading the Prefix sum (++) Operator.
template<class T, int N >
noModN<T, N> noModN<T, N>::operator ++(){

    pair<T,T> result = divide(++data,N);

    if(isnegative(data)) {
        data = (-1)*result.second ;}
    
    else {
        data = result.second;}

    noModN temp(data);
    return temp;
}


// Method for Overloading the Postfix sum (++) Operator.
template<class T, int N >
noModN<T, N> noModN<T, N>::operator ++(int){

    pair<T,T> result = divide(++data,N);
    
    if(isnegative(data)) {
        data = (-1)*result.second ;}
    else {
        data = result.second; }

    noModN temp(data-1);
    return temp;
}


int main(){

    // Taking some random input from the user.
    int a,b,c;
    cin >> a >> b >> c;

    class noModN<int, 10> A(a);
    cout << " `A` object of the class nModN with N = 10, with input data value = " << a << " got converted into "; A.print();

    class noModN<int, 10> B(b);
    cout << " `B` object of the class nModN with N = 10, with input data value = " << b << " got converted into "; B.print();

    // Using a Default value for N which is 10. ( Behaves as a default constructor)
    class noModN<int, 10> C(c);
    cout << " `C` object of the class nModN with N = 10, with input data value = " << c << " got converted into "; C.print();

    cout<<  " Performing the given operation on the 3 objects of the class nModN, i.e. (A+B)*C yields = ";
    ((A+B)*C).print();

    cout <<  " Performing Post fix operation on the object `A` of the class nModN, i.e. A++ yields ";   
    (A++).print(); 

    cout <<  " Performing Pre  fix operation on the object `A` of the class nModN, i.e. ++A yields ";
    (++A).print(); 

    return 0;
}
