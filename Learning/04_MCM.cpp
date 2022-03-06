/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int MCM(vector<int> v, int i, int j)
{
    // Recursive function to find the MCM of array[i..j]
    if (i >= j)
        return 0;
    int ans = INT_MAX;
    for (int k = i; k < j; k++)
    {
        int curr_ans = MCM(v, i, k) + MCM(v, k + 1, j) + v[i - 1] * v[k] * v[j];
        ans = min(ans, curr_ans);
    }
    return ans;
}

int dp[1001][1001];
int MCM_DP(vector<int> v, int i, int j)
{
    // Recursive function to find the MCM of array[i..j]
    if (i >= j)
        return 0;
    int ans = INT_MAX;
    if (dp[i][j] != -1)
        return dp[i][j];

    for (int k = i; k < j; k++)
    {
        int curr_ans = MCM(v, i, k) + MCM(v, k + 1, j) + v[i - 1] * v[k] * v[j];
        ans = min(ans, curr_ans);
    }
    return dp[i][j] = ans;
}

signed main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    int n = v.size();
    cout << "MCM of given array is " << MCM(v, 1, n - 1) << endl;
    ;

    memset(dp, -1, sizeof(dp));
    cout << "MCM_DP of given array is " << MCM_DP(v, 1, n - 1);
}