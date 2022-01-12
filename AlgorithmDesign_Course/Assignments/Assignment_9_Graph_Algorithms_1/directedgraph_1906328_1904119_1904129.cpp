/*
This code is written as a part of CS222-Algorithm Design Course under Dr. Aripta Korwar.

Assignment  9 : Graph algorithms Part 1

Authors :   Prakhar Mathur   1906328
            Sanjay Marreddi  1904119
            Rishabh Tripathi 1904129

Date: 25th April 2021

This file contains code that has a class representing DIRECTED Graph & methods to perform BFS, DFS & Linearization.
*/


// Including all the required Libraries and Namespaces.
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
using namespace std;


class DirectedGraph{

    private:
        int no_of_vertices;
        vector< list <int > > adj_list;

    public:
        DirectedGraph();

        void add_edge(int source, int destination);
        void displayAdjList();

        void DFS(int n);
        void DFS(int vertex, vector<bool> &visited);

        void BFS(int n);
        void BFS( queue<int> my_queue, vector<bool>&visited, vector <int> &distances, int &curr_distance );

        void linearization();
        bool check_cycle(int vertex, vector<bool> &visited, vector<bool> &recursion_stack);
};


// Method that takes source & destination vertices & adds an edge to the Directed Graph.
void DirectedGraph ::add_edge(int source, int destination){

    adj_list[source].push_back(destination);

    cout << "Edge ("<< source << ',' << destination << ") added.\n";
}


// Constructor that takes input from the user & builds the Directed Graph.
DirectedGraph :: DirectedGraph(){

    int source,destination;
    char enter_more ;

    cout << "Enter the number of vertices in your graph: ";
    cin >> no_of_vertices;
    cout << "Note that the vertices should have their values from 1 - " <<  no_of_vertices << endl;

    // Initializing an adjacency list as Vector of Linked Lists where all the vertices in vector has it adjacent 
    // vertices shown in corresponding Linked List. Note that we are using Doubly Linked List from STL.
    vector< list <int > > adj_list_temp( no_of_vertices + 1);
    adj_list = adj_list_temp;

    cout << "Do you want to enter more edges? (y/n): ";
    cin >> enter_more ;

    while( enter_more =='y' ){

        cout << "Enter the edge: ";
        cin >> source >> destination;

        add_edge(source,destination);
        cout << "Do you want to enter more edges? (y/n): ";
        cin >> enter_more ;


        if ( (enter_more !='y') && (enter_more !='n') ){
            cout << "Invalid Input! Please type y/n \n";
        }

    }
}


// Method that prints the Graph in Adjancency List representation.
void DirectedGraph :: displayAdjList() {

   cout << "The Input Graph in Adjancency List representation:\n";
   for(int i = 1; i <= no_of_vertices; i++) {
      cout << i << " -> ";

      for(auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
         cout << *it << " ";
      }
      cout << endl;
   }
}


// Recursive Implementation of DFS that prints the vertices in the sequence they are visited.
void DirectedGraph :: DFS( int vertex, vector<bool> &visited ){

    cout << vertex << " ";
    visited[vertex] = true;
    for (auto i : adj_list[vertex])
    {
        if (!visited[i])
        {
            DFS(i, visited);
        }
    }
}


// Method that takes start vertex n & prints the vertices reachable from it using DFS.
void DirectedGraph :: DFS(int n){

    // Vector to keep track of the visited vertices. 
    vector <bool> visited(no_of_vertices+1,false);

    cout << "Set of reachable vertices from vertex " << n << " are : ";
    
    DFS(n, visited);

    cout << endl;
}


// Recursive Implementation of BFS using queue.
void DirectedGraph :: BFS( queue<int> my_queue, vector<bool>&visited, vector <int> &distances, int &curr_distance){

    if ( my_queue.empty() )
        return;

    int vertex = my_queue.front();
    distances[vertex] = curr_distance;
    curr_distance++;
    my_queue.pop();

    for(auto i:adj_list[vertex]){

        if(!visited[i]){
            visited[i]=true ;
            my_queue.push(i);
        }
    }

    BFS(my_queue, visited, distances, curr_distance);

}

// Method that takes start vertex n & Outputs the distance of each vertex from vertex n using BFS.
// If vertex is not reachable, it outputs -1.
void DirectedGraph :: BFS(int n){

        vector <int> distances(no_of_vertices+1, -1);
        int curr_distance = 0;
                                                                        
        vector <bool> visited(no_of_vertices+1,false);
        queue <int> my_queue;
        
        visited[n] = true;
        my_queue.push(n);

        BFS(my_queue, visited, distances, curr_distance);

        for (int i = 1; i <= no_of_vertices;  i++ ){
            if (distances[i] != -1){
                 cout << "The vertex "<< i << " is reachable from the given vertex " << n << " with distance between them = " << distances[i] << "\n";
            }
            else{
                cout << "The vertex "<< i << " is not reachable from the given vertex " << n << ". So distance is defined as -1 \n";
            }
        }

}


// Method that checks for the presence of Cycle in the graph.
bool DirectedGraph ::check_cycle(int vertex, vector<bool> &visited, vector<bool> &recursion_stack){

    visited[vertex] = true;
    recursion_stack[vertex] = true;

    for (auto i : adj_list[vertex]){

        // If the vertex is not visited, We make a recursive call & insert it to stack .
        if ( !visited[i] && check_cycle(i, visited, recursion_stack) ){
            return true;
        }

        // If the vertex is visited, We will check if it is on recursion stack.
        else if (recursion_stack[i])
            return true;
    }

    // vertex is removed from stack as in usual DFS.
    recursion_stack[vertex] = false;

    // If no such cycle is found, return false.
    return false;
}


// Outputs a linearization of Graph if it is a DAG. Else prints that it is not a DAG. 
void DirectedGraph :: linearization(){

    vector<bool> visited(no_of_vertices+1, false);

    // Helps in keeping track of back edges.
    vector<bool> recursion_stack(no_of_vertices+1, false);

    for (int i = 1; i <= no_of_vertices; i++){

        // Checking if the graph contains a cycle.
        if (check_cycle(i, visited, recursion_stack))
        {
            cout <<"\nThe graph G is not a DAG.\n";
            return;
        }
    }

    cout << "\nThe graph G is a DAG.\n";
    return;

}


int main(){

    int n;
    DirectedGraph G ;
    G.displayAdjList();
    cout << endl;

    cout << "Enter the start vertex for DFS : ";
    cin >> n;
    G.DFS(n);
    cout << endl;

    cout << "Enter the start vertex for BFS : ";
    cin >> n;
    G.BFS(n);

    G.linearization();
    return 0;
}
