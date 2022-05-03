/*
    Author: Adarsh Anand
    Roll No: 2003101
    B.Tech, CSE 2020

    Date: 10 April 2022

    Dijkstra's algorithm

    Time Complexity: O(m*logk)

    Space Complexity: O(k + m)
*/

/*----------------------------------*/

#include <bits/stdc++.h>
using namespace std;

#define inf (int)1e7
void swap(pair<int, int> *x, pair<int, int> *y);

class MinHeap
{
    pair<int, int> *harr; // {vertex, distance} pair
    int capacity;         // maximum size of heap
    int heap_size;        // current size of heap

public:
    MinHeap(int capacity); // constructor

    void MinHeapify(int); // function to heapify the subtree rooted with index i

    int parent(int i) { return (i - 1) / 2; } // returns the index of the parent of the vertex at index i

    int left(int i) { return (2 * i + 1); } // returns the index of the left child of the vertex at index i

    int right(int i) { return (2 * i + 2); } // returns the index of the right child of the vertex at index i

    pair<int, int> extractingMin(); // function to extract the minimum element from the heap

    pair<int, int> gettingMin() { return harr[0]; } // function to return the minimum element from the heap

    void insertKey(pair<int, int> k); // function to insert a key into the heap

    bool empty() { return heap_size == 0; } // function to check if the heap is empty
};

MinHeap::MinHeap(int cap)
{
    // initialize the capacity and heap size
    heap_size = 0;
    capacity = cap;
    harr = new pair<int, int>[cap];
}

void MinHeap::insertKey(pair<int, int> k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    heap_size++;           // increment the heap size
    int i = heap_size - 1; // set the index of the new vertex
    harr[i] = k;           // insert the new vertex

    while (i != 0 && harr[parent(i)].first > harr[i].first)
    {
        swap(&harr[i], &harr[parent(i)]); // swap the new vertex with its parent
        i = parent(i);                    // move to the parent
    }
}

pair<int, int> MinHeap::extractingMin()
{
    if (heap_size <= 0)
        return {INT_MAX, INT_MAX};
    if (heap_size == 1)
    {
        heap_size--; // decrement the heap size
        return harr[0];
    }

    pair<int, int> root = harr[0]; // store the root
    harr[0] = harr[heap_size - 1];
    heap_size--;
    MinHeapify(0); // heapify the root

    return root;
}

void MinHeap::MinHeapify(int i)
{
    int l = left(i);  // set the index of the left child
    int r = right(i); // set the index of the right child
    int smallest = i;
    if (l < heap_size && harr[l].first < harr[i].first)
        smallest = l; // set the index of the smallest child
    if (r < heap_size && harr[r].first < harr[smallest].first)
        smallest = r; // set the index of the smallest child
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest); // recursively heapify the subtree rooted with the smallest child
    }
}

void swap(pair<int, int> *x, pair<int, int> *y)
{ // function to swap two vertices
    pair<int, int> temp = *x;
    *x = *y;
    *y = temp;
}

/*----------------------------------*/

vector<int> restorePaths(int s, int t, vector<int> const &p)
{ // function to restore the path from the parent vector
    vector<int> path;

    for (int v = t; v != s; v = p[v]) // traverse the parent vector from the destination to the source
        path.push_back(v);
    path.push_back(s); // push the source into the path

    reverse(path.begin(), path.end()); // reverse the path
    return path;
}

void dijkstra(int src, vector<vector<pair<int, int>>> &adj, vector<int> &dis, vector<int> &vis, MinHeap &pq, vector<int> &p)
{
    dis[src] = 0; // set the distance of the source from itself to 0
    vis[src] = 1; // set the visited status of the source to 1
    while (!pq.empty())
    {
        int node = pq.extractingMin().second; // extract the minimum distance vertex from the heap

        for (auto x : adj[node])
        {
            int v = x.first;     // set the vertex
            int cost = x.second; // set the cost of the edge

            if (dis[v] > dis[node] + cost)
            {
                dis[v] = dis[node] + cost;
                pq.insertKey({dis[v], v});
                p[v] = node; // set the parent of the vertex
            }
        }
    }
}

int main()
{
    freopen("graph.txt", "r", stdin); // open the file  to read the input
    int n, m;                         // set the number of vertices and edges
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1); // set the adjacency list
    for (int i = 0; i < m; i++)
    {
        int s, d, c;        // set the source, destination and cost of the edge
        cin >> s >> d >> c; // read the input
        adj[s].push_back({d, c});
        adj[d].push_back({s, c});
    }

    vector<int> dis(n + 1, inf), vis(n + 1, 0), p(n + 1, -1); // set the distance vector and visited vector
    MinHeap pq(1000);

    pq.insertKey({0, 1}); // insert the source into the heap

    dijkstra(1, adj, dis, vis, pq, p); // run the dijkstra algorithm

    freopen("CON", "r", stdin); // open the file to read the input
    cout << "*-----------------------------------------------------*\n";
    cout << "Welcome to the Lab Assignment 5\n";
    cout << "Follow the instructions in the terminal to get the output!\n";
    while (true)
    {
        cout << "\nEnter destination Vertex: "; // ask the user to enter the destination vertex
        int d;
        cin >> d;
        // if input is not a valid vertex
        if (d < 1 || d > n)
        {
            cout << "\nInvalid Vertex\n";
            continue;
        }
        vector<int> res = restorePaths(1, d, p); // restore the path
        cout << "The shortest path is: ";
        for (int i = 0; i < res.size(); i++) // print the path
        {
            if (i != res.size() - 1) // if the vertex is not the destination
                cout << res[i] << " -> ";
            else
                cout << res[i];
        }
        cout << " of total cost " << dis[d] << '\n';
        // press q to quit or any other key to continue
        cout << "Press q to quit or any other character to continue: \n";
        char c;
        cin >> c;
        if (c == 'q')
            break;
    }
    cout << "*-----------------------------------------------------*\n";
    return 0;
}