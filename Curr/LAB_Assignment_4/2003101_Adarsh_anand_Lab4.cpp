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

vector<int> construct_vector(vector<int> array, vector<int> previous_LIS, int current_end_index)
{
    /*
    This function takes a vector, a vector of previous longest increasing sequence and the current end index of the array as input and returns the longest increasing sequence as a vector.
    */
    if (previous_LIS[current_end_index] == -1)
    {                       // If the current end index is not in the previous longest increasing sequence, then the current end index is the longest increasing sequence.
        vector<int> result; // Create a vector to store the longest increasing sequence
        result.push_back(array[current_end_index]);
        return result;
    }
    vector<int> result = construct_vector(array, previous_LIS, previous_LIS[current_end_index]); // Recursively call the function to construct the longest increasing sequence
    result.push_back(array[current_end_index]);
    return result; // Return the longest increasing sequence
}

// ---------------------------------------------------------------------------------------------------------------------d

vector<int> LIS(vector<int> array)
{
    /*
    This function takes a vector as input and returns the longest increasing sequence present in the vector as a vector.
    */
    int length = array.size();                             // Get the length of the array
    vector<int> previous_LIS(length), LIS_lengths(length); // Create a vector to store the previous longest increasing sequence and a vector to store the lengths of the longest increasing sequences
    LIS_lengths[0] = 1;                                    // The length of the longest increasing sequence for the first element is 1
    previous_LIS[0] = -1;                                  // The previous longest increasing sequence for the first element is -1
    for (int i = 1; i < length; i++)
    { // Iterate over the array
        LIS_lengths[i] = 1;
        previous_LIS[i] = -1; // Initialize the lengths and previous longest increasing sequences
        for (int j = 0; j < i; j++)
        {
            if (array[j] < array[i] && LIS_lengths[i] < LIS_lengths[j] + 1)
            {                                        // If the current element is smaller than the current element and the length of the longest increasing sequence is less than the length of the longest increasing sequence of the previous element plus 1
                LIS_lengths[i] = LIS_lengths[j] + 1; // Update the length of the longest increasing sequence
                previous_LIS[i] = j;                 // Update the previous longest increasing sequence
            }
        }
    }

    int max_index = 0; // Create a variable to store the index of the longest increasing sequence
    for (int i = 0; i < length; i++)
    {
        if (LIS_lengths[i] > LIS_lengths[max_index])
        {                  // Find the index of the longest increasing sequence
            max_index = i; // Update the index of the longest increasing sequence
        }
    }
    return construct_vector(array, previous_LIS, max_index); // Return the longest increasing sequence
    // Time complexity: O(n2log n)
}

// ---------------------------------------------------------------------------------------------------------------------

vector<int> common_LIS(vector<int> a, vector<int> b)
{
    /*
    This function takes two vectors as input and returns the longest increasing sequence present in both the vectors as a vector.
    */
    vector<int> a_LIS = LIS(a);   // Get the longest increasing sequence of the first array
    vector<int> b_LIS = LIS(b);   // Get the longest increasing sequence of the second array
    vector<int> common_LIS;       // Create a vector to store the longest increasing sequence
    int a_index = 0, b_index = 0; // Create two variables to store the index of the longest increasing sequence of the first array and the second array
    while (a_index < a_LIS.size() && b_index < b_LIS.size())
    { // Iterate over the longest increasing sequences of the first and second array
        if (a_LIS[a_index] == b_LIS[b_index])
        {                                         // If the current element of the longest increasing sequence of the first array is equal to the current element of the longest increasing sequence of the second array
            common_LIS.push_back(a_LIS[a_index]); // Add the current element of the longest increasing sequence of the first array to the longest increasing sequence of the second array
            a_index++;                            // Increment the index of the longest increasing sequence of the first array
            b_index++;                            // Increment the index of the longest increasing sequence of the second array
        }
        else if (a_LIS[a_index] < b_LIS[b_index])
        {              // If the current element of the longest increasing sequence of the first array is smaller than the current element of the longest increasing sequence of the second array
            a_index++; // Increment the index of the longest increasing sequence of the first array
        }
        else
        {              // If the current element of the longest increasing sequence of the first array is greater than the current element of the longest increasing sequence of the second array
            b_index++; // Increment the index of the longest increasing sequence of the second array
        }
    }
    return common_LIS; // Return the longest increasing sequence
    // Time complexity: O(n2log n)
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
    vector<int> ans = common_LIS(a, b); // get the longest increasing sequence present in both the arrays
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " "; // print the longest increasing sequence
    }
    cout << endl;

    cout << "------------------------------------------------------" << endl;
    cout << "------------------------------------------------------" << endl;

    return 0;
}
