/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment 3 : Heap sort using max heap

Authors :-   
Prakhar Mathur   1906328
Sanjay Marreddi  1904119
Rishabh Tripathi 1904129

Date: 19th February 2021             

This file contains implementation of Heap Data Structure as a C++ Class & also a function to do Heap Sort. 
*/

// Including all the required Libraries and Namespaces.
#include <iostream>
#include <algorithm>
#include <climits>
#include <ctime>
#include <cmath>
using namespace std;


class maxHeap{

private:

        int* items; 
        int size;
       
       // Takes an index. Assume all the other items in the sub-tree rooted at the index satisfy the max-heap property. 
       // Swap items in the sub-tree rooted at the index, so that the sub-tree rooted at the index is a max-heap.
        void sift_down(int index,int n);

        // Takes an index. Assume all the other items in the heap satisfy the max-heap property.  
        // Swap items from the root to the index so that the tree satisfies the max-heap property.
        void sift_up(int index);

        // Returns the index of the parent
        int find_parent(int child_index){
            return (child_index-1)/2;   
        }

        // Returns the index of the left child
        int find_lchild(int parent_index){ 
            return 2*parent_index+1;    
        }
        
        // Returns the index of the right child
        int find_rchild(int parent_index){
             return 2*parent_index+2;} 
        
        // Verifys the validity of given index 
        bool is_valid_index(int index){   
            return ((index < size) && (index >=0));
        }
    
 
public:
        // Called by the constructor below to convert the arbitrary array items into a max-heap.
        void heapify(int m,int n);
        
        // peeks into the max-heap and returns the maximum value
        int get_max (); 

        // inserts an element into the max heap
        void insert(int x);	
        
        // returns the maximum value and deletes the item.
        int delete_max();	
        
        // Constructor that takes an arbitrary array of size sz and creates a max-heap.
        maxHeap(int sz, int arr[]); 
	
};



/* 
Takes an index. Assume all the other items in the sub-tree rooted at the index satisfy the max-heap property. 
Swap items in the sub-tree rooted at the index, so that the sub-tree rooted at the index is a max-heap.
*/
void maxHeap::sift_down(int index, int n){

            int largest = index;
            int left  = find_lchild(index);
            int right = find_rchild(index);

            if (left < n && items[left] > items[largest])
                largest = left;
            if (right < n && items[right] >items[largest])
                largest = right;

            if (largest != index){
                swap(items[index], items[largest]);
                sift_down(largest,n);
            }
}



/* 
Takes an index. Assume all the other items in the heap satisfy the max-heap property.  
Swap items from the root to the index so that the tree satisfies the max-heap property.
*/
void maxHeap::sift_up(int index){

    while( is_valid_index (index) && (items[find_parent(index)]<items[index])){
   
        // Swapping parent and child values
        swap( items[find_parent(index)], items[index] );
      
        index = find_parent(index);
    }
}

// Maintains the Max Heap Properties
void maxHeap::heapify( int m, int n){
        sift_down(m,n);    
};


// peeks into the max-heap and returns the maximum value
int maxHeap::get_max(){
    return items[0];
};


// insert element in max_heap
void maxHeap::insert(int x){
    items[size] = x;
    size = size+1;
    sift_up(size-1);
};


// Delete the max, heapify again and return it.
int maxHeap::delete_max(){
    
    // Base Case
    if(!is_valid_index(size-1))
     return INT_MIN;      
    
    int max = items[0];     
    items[0] = items[size-1];
    size = size-1;
    
    heapify(0,size);
    return max;
};

// Constructor that takes an arbitrary array of size sz and creates a max-heap.
maxHeap::maxHeap(int sz, int arr[]){
    items = arr;
    size = sz;
    for (int k = (sz / 2) - 1; k >= 0; k--)
        heapify(k,sz);
};

// Sorts the given Random Array using an object of maxHeap Class.
void heapsort(int a[], int N){

    class maxHeap my_heap(N, a);
    for (int i = N-1 ; i > 0 ; i--){
        swap(a[0], a[i]);
        my_heap.heapify(0,i);
    }
}

int main(){   

    int N = 20 ;
    int A[N];

    srand(time(NULL));
    
    for(int j = 0; j<N;++j){ 

        // Random numbers are choosen between -1000 to 1000.
        A[j] = ( (-1000) + rand() % (1000 - (-1000) + 1 )) ;
    }
    
    cout << "The Input random array is:\t";
    for (int i = 0; i < N; i++){
        cout << A[i] << " ";
    }
    cout <<  endl;

    heapsort(A, N);
    
    cout << "The Output sorted array is:\t";
    for (int i = 0; i < N; i++){
        cout << A[i] << " ";
    }
    
    return 0;
}