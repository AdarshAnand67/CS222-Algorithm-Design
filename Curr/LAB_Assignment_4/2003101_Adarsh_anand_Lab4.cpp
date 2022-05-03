/*
    Lab 4

    CS222 - Algorithm Design Course

    This code is written as an assignment under prof Dr. Rahul.

    Author: Adarsh Anand

    Roll No: 2003101
*/

// ! TASK -
// In this assignment, you have to write a program that reads two array of integers as input and
// computes the Longest Increasing Sequence that is present in both the arrays in O(n2log n) time
// (you may assume n to be the length of the longest array). You may assume elements in an array
// to be distinct. You program can read the size of both the arrays as input, further, read both
// the arrays and just print the output.

#include <bits/stdc++.h> // Include all the necessary libraries
using namespace std;     // Use the standard namespace

// ---------------------------------------------------------------------------------------------------------------------

int LCIS(vector<int> &a1, int n, vector<int> &a2, int m)
{
    // dp[j] stores length of LCIS
    int dp[m] = {0};
    // Iterate over every element of first array
    for (int i = 0; i < n; i++)
    {
        // Initiase length of current LCIS
        int curr = 0;
        // Iterate over every element of second array
        for (int j = 0; j < m; j++)
        {
            // If same, update dp[j]
            if (a1[i] == a2[j])
            {
                dp[j] = max(dp[j], curr + 1);
            }
            // else if greater, update current
            if (a1[i] > a2[j])
            {
                curr = max(curr, dp[j]);
            }
        }
    }
    // return max element of dp[j] i.e. length of LCIS
    return *max_element(dp, dp + m);
}

// ---------------------------------------------------------------------------------------------------------------------

int main()
{
    int n, m; // n = size of array a, m = size of array b

    cout << "Enter size of array a: ";
    cin >> n;

    cout << "Enter size of array b: ";
    cin >> m;

    vector<int> a(n), b(m); // create vectors a and b

    cout << "Enter elements of array a: ";
    for (int i = 0; i < n; i++)
        cin >> a[i]; // read elements of array a

    cout << "Enter elements of array b: ";
    for (int i = 0; i < m; i++)
        cin >> b[i]; // read elements of array b

    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Longest Increasing Sequence in both the arrays: ";

    int lcis = LCIS(a, n, b, m);
    cout << lcis << endl;

    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;

    return 0;
}
