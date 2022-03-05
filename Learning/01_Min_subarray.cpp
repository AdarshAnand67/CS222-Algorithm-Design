/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int minSubArrayLen(int target, vector<int> &nums)
{
    int n = nums.size();
    int ans = INT_MAX;
    int sum = 0;
    int start = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        while (sum >= target)
        {
            ans = min(ans, i - start + 1);
            sum -= nums[start++];
        }
    }
    return ans == INT_MAX ? 0 : ans;
}


// Maximum subarray problem
// Given an array of integers, find the contiguous subarray with maximum sum.

int kadane(vector<int> &nums)
{
    // Kadane's algorithm for maximum subarray problem - O(n) time complexity
    int n = nums.size();
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    for (int i = 0; i < n; i++)
    {
        max_ending_here = max(nums[i], max_ending_here + nums[i]);
        max_so_far = max(max_so_far, max_ending_here);
        if(max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

signed main()
{
    cout << "Enter the number of elements in the array: ";
    int n;
    cin >> n;
    vector<int> v(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    // cout << "Enter the target sum: ";
    // int k;
    // cin >> k;
    // cout << "The minimum length of the subarray is: " << minSubArrayLen(k, v);
    cout << "The maximum sum of the subarray is: " << kadane(v);
}

// ------------------------------------------------------------------------------------------------


