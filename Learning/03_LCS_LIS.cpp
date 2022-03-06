/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int LCS(string x, string y, int n, int m)
{
    if (n == 0 || m == 0)
        return 0;
    if (x[n - 1] == y[m - 1])
        return 1 + LCS(x, y, n - 1, m - 1);
    else
        return max(LCS(x, y, n - 1, m), LCS(x, y, n, m - 1));
} // Time Complexity: O(2^nm)

int dp[1001][1001];
int LCS_DP(string x, string y, int n, int m)
{
    if (n == 0 || m == 0)
        return 0;
    if (dp[n][m] != -1)
        return dp[n][m]; // if already calculated
    if (x[n - 1] == y[m - 1])
        return dp[m][n] = 1 + LCS(x, y, n - 1, m - 1); // store in dp and return
    else
        return dp[m][n] = max(LCS(x, y, n - 1, m), LCS(x, y, n, m - 1));
} // Time Complexity: O(mn)

int LIS(vector<int> v, int n)
{
    // Recursive function to find the LIS of array[0..n-1]
    if (n == 0)
        return 0;
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int curr_ans = 1 + LIS(v, i);
        ans = max(ans, curr_ans);
    }
    return ans;
} // Time Complexity: O(n^2)

signed main()
{
    string x = "Adarsh";
    string y = "Anand";
    int n = x.length();
    int m = y.length();
    memset(dp, -1, sizeof(dp));
    cout << "LCS of " << x << " and " << y << " is " << LCS(x, y, n, m) << endl;
    cout << "LCS of " << x << " and " << y << " is " << LCS_DP(x, y, n, m) << endl;

    vector<int> v = {1, 2, 3, 0, 5};
    int nm = v.size();
    cout << "LIS of given array is " << LIS(v, nm) << endl;
}