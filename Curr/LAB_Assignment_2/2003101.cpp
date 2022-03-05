/*
    Lab 2

    CS222 - Algorithm Design Course

    This code is written as an assignment under prof Dr. Rahul.

    Author: Adarsh Anand

    Roll No: 2003101
*/

// Including all the required Libraries and Namespaces.

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int main() // Main Function
{
    freopen("input.txt", "r", stdin);   // redirects standard input to input.txt
    freopen("output.txt", "w", stdout); // redirects standard output to output.txt

    int m, n;         // m is the number of rows and n is the number of columns
    cin >> m >> n;    // reads the number of rows and columns of the matrix
    int matrix[m][n]; // declares an array of size m × n

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j]; // reads the elements of the matrix
        }
    }
    /*
        1
        For the first part we create a suffix_sum_matrix[m][n] which is suffix sum of the 2d array.
        This is done by adding the elements of the matrix from right to left and from bottom to top.
        For example, if the matrix is:
        1 2 3
        4 5 6
        7 8 9
        then the suffix_sum_matrix is:
        6 5 3
        15 11 6
        24 17 9
    */
    int suffix_sum_matrix[m][n]; // suffix sum matrix
    for (int i = 0; i < m; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (j == n - 1) // if the element is in the last column
                suffix_sum_matrix[i][j] = matrix[i][j];
            else // if the element is not in the last column
                suffix_sum_matrix[i][j] = suffix_sum_matrix[i][j + 1] + matrix[i][j];
        }
    }

    int S_end[m][n];
    int T_end[m][n]; // stores the column

    int T_sum[m][n]; // stores the sum of the elements in the column
    int T_ID[m][n]; // stores the ID of the column

    memset(T_ID, (int)0, sizeof(T_ID)); // initializing the matrix to 0

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0)
            {
                T_sum[i][j] = suffix_sum_matrix[i][j]; // if the element is in the first row
            }
            else
            {
                if (suffix_sum_matrix[i][j] + T_sum[i - 1][j] < suffix_sum_matrix[i][j])
                {
                    // if the sum of the elements in the row is less than the sum of the elements in the row
                    T_ID[i][j] = T_ID[i - 1][j];                             // assign the ID of the row above
                    T_sum[i][j] = suffix_sum_matrix[i][j] + T_sum[i - 1][j]; // assign the sum of the elements in the row
                }
                else
                {
                    // if the sum of the elements in the row is greater than the sum of the elements in the row
                    T_ID[i][j] = i;                        // assign the row number to the element
                    T_sum[i][j] = suffix_sum_matrix[i][j]; // assign the sum of the elements in the row
                }
            }
            S_end[i][j] = n - 1; // S_end[i][j] stores the index of the last element in the row
            T_end[i][j] = n - 1; // T_end[i][j] stores the index of the last element in the row
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << T_sum[i][j] << " "; // prints the sum of elements in a matrix X with the term weight of X
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << T_ID[i][j] << " "; // prints the index of the last element in the row
        }
        cout << endl;
    }
    cout << endl;
    /*
        2
    */
    int S_sum[m][n];
    memcpy(S_sum, T_sum, sizeof(S_sum)); // copying the matrix T_sum to S_sum

    int S_begin[m][n];
    memcpy(S_begin, T_ID, sizeof(S_begin)); // copy the matrix T_ID to S_begin

    int Best_sum_storer[n][n], Best_ID[n][n];
    memset(Best_sum_storer, (int)0, sizeof(Best_sum_storer)); // initializes the Best_sum_storer to 0

    memset(Best_ID, (int)0, sizeof(Best_ID)); // initializes the Best_ID to 0

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            Best_sum_storer[i][j] = suffix_sum_matrix[0][i] - suffix_sum_matrix[0][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << Best_sum_storer[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << '(' << S_begin[i][j] << ',' << S_end[i][j] << ')' << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << S_sum[i][j] << " ";
        }
        cout << endl;
    }

    /*
        3
    */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (i == 0)
                {
                    if (Best_sum_storer[j][k] < S_sum[i][j])
                    {
                        S_end[i][j] = k - 1;
                        S_sum[i][j] = Best_sum_storer[j][k];
                    }
                }
                else
                {
                    if (Best_sum_storer[j][k] + suffix_sum_matrix[i][j] - suffix_sum_matrix[i][k] > suffix_sum_matrix[i][j] - suffix_sum_matrix[i][k])
                    {
                        Best_sum_storer[j][k] = suffix_sum_matrix[i][j] - suffix_sum_matrix[i][k];
                        Best_ID[j][k] = i;
                    }
                    else
                    {
                        Best_sum_storer[j][k] += (suffix_sum_matrix[i][j] - suffix_sum_matrix[i][k]);
                    }
                    if (S_sum[i][j] >= Best_sum_storer[j][k])
                    {
                        S_sum[i][j] = Best_sum_storer[j][k];
                        S_end[i][j] = k - 1;
                        S_begin[i][j] = Best_ID[j][k];
                    }
                }
            }
        }
    }
    cout << endl;
    /*
        4
    */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << '(' << S_begin[i][j] << ',' << S_end[i][j] << ')' << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << S_sum[i][j] << " ";
        }
        cout << endl;
    }
}
