#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int array[m][n];

    // memset(sumarray,(int)0,sizeof(sumarray));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> array[i][j];
        }
    }

    int sumarray[m][n];

    for (int i = 0; i < m; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (j == n - 1)
                sumarray[i][j] = array[i][j];
            else
                sumarray[i][j] = sumarray[i][j + 1] + array[i][j];
        }
    }

    int s_end[m][n];
    int t_end[m][n];
    int tsum[m][n];
    int tid[m][n];

    memset(tid, (int)0, sizeof(tid));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0)
            {
                tsum[i][j] = sumarray[i][j];
            }
            else
            {
                if (sumarray[i][j] + tsum[i - 1][j] < sumarray[i][j])
                {
                    tid[i][j] = tid[i - 1][j];
                    tsum[i][j] = sumarray[i][j] + tsum[i - 1][j];
                }
                else
                {
                    tid[i][j] = i;
                    tsum[i][j] = sumarray[i][j];
                }
            }
            s_end[i][j] = n - 1;
            t_end[i][j] = n - 1;
        }
    }
    cout << '\n';
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << tsum[i][j] << " ";
        }
        cout << '\n';
    }
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << tid[i][j] << " ";
        }
        cout << '\n';
    }

    cout << endl;

    int ssum[m][n];
    memcpy(ssum, tsum, sizeof(ssum));
    int sbegin[m][n];
    memcpy(sbegin, tid, sizeof(sbegin));

    int bestsumstorer[n][n], bestid[n][n];
    memset(bestsumstorer, (int)0, sizeof(bestsumstorer));
    memset(bestid, (int)0, sizeof(bestid));
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            bestsumstorer[i][j] = sumarray[0][i] - sumarray[0][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << bestsumstorer[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << '(' << sbegin[i][j] << ',' << s_end[i][j] << ')' << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ssum[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (i == 0)
                {
                    // cout<<i<<" "<<j<<" "<<ssum[i][j]<<endl;
                    if (bestsumstorer[j][k] < ssum[i][j])
                    {
                        s_end[i][j] = k - 1;
                        ssum[i][j] = bestsumstorer[j][k];
                    }
                }
                else
                {
                    if (bestsumstorer[j][k] + sumarray[i][j] - sumarray[i][k] > sumarray[i][j] - sumarray[i][k])
                    {
                        bestsumstorer[j][k] = sumarray[i][j] - sumarray[i][k];
                        bestid[j][k] = i;
                    }
                    else
                    {
                        bestsumstorer[j][k] += (sumarray[i][j] - sumarray[i][k]);
                    }
                    if (ssum[i][j] >= bestsumstorer[j][k])
                    {
                        ssum[i][j] = bestsumstorer[j][k];
                        s_end[i][j] = k - 1;
                        sbegin[i][j] = bestid[j][k];
                    }
                }
            }
        }
    }
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << '(' << sbegin[i][j] << ',' << s_end[i][j] << ')' << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ssum[i][j] << " ";
        }
        cout << endl;
    }
}
/*
4 5
6 -5 9 -3 -2
-3 2 -7 -3 -1
-2 7 2 5 4
-1 -9 1 7 -2
*/