/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment  9 : Graph algorithms Part 1

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 25th April 2021

This file contains code that has a class representing UNDIRECTED Graph & methods to perform BFS, DFS.
*/
    

// Including all the required Libraries and Namespaces.
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
using namespace std;


class UndirectedGraph{

    private:
        int no_of_vertices;
        vector< vector<int> > adj_matrix;

    public:
        UndirectedGraph();
        void displayAdjMatrix();

        void DFS(int n);
        void DFS(vector<bool>visited, stack<int>my_stack);

        void BFS(int n);
        void BFS(queue<int> my_queue,vector<bool>visited,int destination_vertex,int &distance,bool &checking_vertex);

};

// Constructor that takes input from the user & builds the Directed Graph.
UndirectedGraph :: UndirectedGraph(){
 
    int source,destination;
    char enter_more ;

    cout << "Enter the number of vertices in your graph: ";
    cin >> no_of_vertices;
    cout << "Note that the vertices should have their values from 1 - " <<  no_of_vertices << endl;

    // Initializing an adjacency Matrix as Vector of Vectors.
    vector< vector <int > > adj_matrix_temp( no_of_vertices + 1, vector<int> (no_of_vertices + 1, 0));
    adj_matrix = adj_matrix_temp;

    cout << "Do you want to enter more edges? (y/n): ";
    cin >> enter_more ;

    while( enter_more =='y' ){

        cout << "Enter the edge: ";
        cin >> source >> destination;

        adj_matrix[source][destination] = 1;
        adj_matrix[destination][source] = 1;
        cout << "Edge ("<< source << ',' << destination << ") added.\n";

        cout << "Do you want to enter more edges? (y/n): ";
        cin >> enter_more ;

        if ( (enter_more !='y') && (enter_more !='n') ){
            cout << "Invalid Input! Please type y/n \n";
        }

    }
}



// Method that prints the Graph in Adjancency Matrix representation.
void UndirectedGraph :: displayAdjMatrix() {

   cout << "The Input Graph in Adjancency Matrix representation:\n";
   for(int i = 1; i <= no_of_vertices; i++) {

        for(int j = 1; j <= no_of_vertices; j++) {

            cout << adj_matrix[i][j] << " ";
        }

        cout << endl;
   }
}


// Non Recursive Implementation of DFS that prints the vertices in the sequence they are visited.
void UndirectedGraph :: DFS( vector<bool> visited, stack<int> my_stack){

    while( !my_stack.empty() ){

        int vertex = my_stack.top();
        my_stack.pop();

        if (!visited[vertex])
        {
        visited[vertex] = true; 
        cout << vertex << " "; 
        }

        for(int i = 1; i <= no_of_vertices; i++ ){

            if ( ( adj_matrix[vertex][i]  == 1) && (!visited[i]) ){
                    my_stack.push(i);
            }
        }
    }
}


// Method that takes start vertex n & prints the vertices reachable from it using DFS.
void UndirectedGraph :: DFS(int n){
    
    // Vector to keep track of the visited vertices. 
    vector<bool>visited(no_of_vertices+1,false);

    stack<int>my_stack;
    my_stack.push(n);

    cout << "Set of reachable vertices from vertex " << n << " are : ";

    DFS(visited, my_stack);
    
    cout << endl;
}


// Non Recursive Implementation of BFS using queue.
void UndirectedGraph :: BFS(queue<int> my_queue,vector<bool>visited,int destination_vertex,int &distance,bool &checking_vertex){

    while(! my_queue.empty()){

        int vertex= my_queue.front();
        distance++;

        if(checking_vertex)
            return;

         my_queue.pop();
        
        for(int i = 1; i <= no_of_vertices; i++ ){

            if ( ( adj_matrix[vertex][i]  == 1) && (!visited[i]) ){
                
                visited[i] = true ;

                if ( i == destination_vertex){
                    checking_vertex = true;
                    return;
                }
                 
                my_queue.push(i);
            }
        }
    }
}


// Method that takes start vertex n & Outputs the distance of each vertex from vertex n using BFS.
// If vertex is not reachable, it outputs -1.
void UndirectedGraph :: BFS(int n){

    int distance;
    bool checking_vertex;

    for( int j = 1; j <= no_of_vertices; ++j){

        distance = 0;
        checking_vertex = false;

        if ( j == n ) {
            cout << "The vertex "<< j << " is reachable from the given vertex " << n << " with distance between them = " << distance << "\n";
            continue;
        }
            

        vector<bool>visited(no_of_vertices+1,false);
        queue<int> my_queue;
        visited[j] = true;
        my_queue.push(j);
        
        BFS( my_queue, visited, n, distance, checking_vertex);

        if(checking_vertex){
                 cout << "The vertex "<< j << " is reachable from the given vertex " << n << " with distance between them = " << distance << "\n";
        }
        else{
                cout << "The vertex "<< j << " is not reachable from the given vertex " << n << ". So distance is defined as -1 \n";
        }
    }
}


int main(){

    int n;
    UndirectedGraph G ;
    G.displayAdjMatrix();
    cout << endl;

    cout << "Enter the start vertex for DFS : ";
    cin >> n;
    G.DFS(n);
    cout << endl;

    cout << "Enter the start vertex for BFS : ";
    cin >> n;
    G.BFS(n);

    return 0;
}