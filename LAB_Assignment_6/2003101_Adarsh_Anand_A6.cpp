/*
    Lab 6

    CS222 - Algorithm Design Course

    This code is written as an assignment under prof Dr. Rahul.

    Author: Adarsh Anand

    Roll No: 2003101
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 99999

vector<int> getPath(vector<vector<int>> parent, int i, int j)
{
    // Function to get the path from the parent matrix
    vector<int> path; 
    for (int v = j; v != i; v = parent[i][v])
    {
        if (v == -1)
        {
            path.push_back(i); // if the path is not found, then push the source node
            break;
        }

        path.push_back(v); // push the path
    }

    reverse(path.begin(), path.end()); // reverse the path
    return path;                       // return the path
}

void floydWarshall(vector<vector<int>> &matrix, vector<vector<int>> &p, int n)
{

    for (int k = 0; k < n; k++) //checking all intermediate paths
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (matrix[i][k] + matrix[k][j] < matrix[i][j] && matrix[i][k] != INF && matrix[k][j] != INF)
                {
                    // Between vertex i and j, the shortest path is through vertex k
                    matrix[i][j] = matrix[i][k] + matrix[k][j]; 

                    p[i][j] = k; // update the parent 
                }
            }
        }
    }
}

int main()
{
    // main function
    freopen("graph.txt", "r", stdin); // open the file
    int n;                            // number of nodes
    cin >> n;                         // input the number of nodes
    vector<string> v(n);              // vector to store the edges
    for (int i = 0; i < n; i++)       // input the edges
        cin >> v[i];

    vector<vector<int>> graph(n, vector<int>(n, 0)); // create a graph
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string st;
            cin >> st;
            int num;
            if (st == "INF")
                num = INF;
            else
                num = stoi(st);

            graph[i][j] = num;
        }
    }
    freopen("CON", "r", stdin); // redirect stdin to console

    vector<vector<int>> p(n, vector<int>(n, -1)); // create a parent matrix
    floydWarshall(graph, p, n);                   // call the floydWarshall function

    while (true)
    {
        cout << "------------------------------------------------------" << endl;
        cout << "Welcome to Adarsh Anand's Floyd-Warshall algorithm" << endl;
        cout << "Follow the instructions below to find the shortest path between any two cities" << endl;
        cout << "------------------------------------------------------" << endl;

        // Cout cities

        cout << "The Cities are: ";
        for (int i = 0; i < n; i++)
        {
            cout << v[i] << " ";
        }
        cout << endl;

        int s, d;            // source and destination
        string city1, city2; // source and destination cities

        cout << "\nEnter Source City: ";
        cin >> city1;

        auto it1 = find(v.begin(), v.end(), city1); // find the source city
        if (it1 == v.end())
        {
            cout << "Invalid Source City\n";
            continue;
        }
        s = it1 - v.begin();

        cout << "Enter destination City: ";
        cin >> city2;

        auto it2 = find(v.begin(), v.end(), city2); // find the destination city
        if (it2 == v.end())
        {
            cout << "Invalid Destination City\n";
            continue;
        }

        d = it2 - v.begin();
        if (graph[s][d] == INF)
        {
            cout << "No path exists between these cities\n";
            continue;
        }

        vector<int> res = getPath(p, s, d); // get path from parent matrix

        cout << "\nThe shortest path is: ";
        for (int i = 0; i < res.size(); i++)
        {
            if (i != res.size() - 1)
                cout << v[res[i]] << " -> ";
            else
                cout << v[res[i]];
        }
        cout << " of total cost " << graph[s][d] << '\n';

        // Ask for another path
        char ch;
        cout << "Do you want to find another path? (y/n): ";
        cin >> ch;
        if (ch == 'n')
        {
            cout << "------------------------------------------------------" << endl;
            cout << "\nThank you for using my program!\n    Have a nice day!\n";
            cout << "------------------------------------------------------" << endl;
            break;
        }
        else if (ch == 'y')
        {
            continue;
        }
        else
        {
            cout << "Invalid Input, going back to main menu\n";
            continue;
        }
    }
}