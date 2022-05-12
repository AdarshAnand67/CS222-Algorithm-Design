/* Dynamic Programming C++ implementation of LIS problem */
#include <bits/stdc++.h>
using namespace std;

int lis(int arr[], int n)
{
    int lis[n];
    lis[0] = 1;
    /* Compute optimized LIS values in bottom up manner */
    for (int i = 1; i < n; i++)
    {
        lis[i] = 1;
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;
    }
    // Return maximum value in lis[]
    return *max_element(lis, lis + n);
}

int main()
{
    // int arr[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Length of LIS is " << lis(arr, n);
    return 0;
}