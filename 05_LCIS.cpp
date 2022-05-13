
#include <bits/stdc++.h>
using namespace std;

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
                if (curr + 1 > dp[j])
                    dp[j] = curr + 1;
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

int main()
{
    // Take input of size of arrays
    int n, m;
    cin >> n >> m;
    // Take input of arrays
    vector<int> a1(n), a2(m);
    for (int &x : a1)
        cin >> x;
    for (int &x : a2)
        cin >> x;

    // calculate LCIS
    cout << LCIS(a1, n, a2, m) << '\n';
    return 0;
}