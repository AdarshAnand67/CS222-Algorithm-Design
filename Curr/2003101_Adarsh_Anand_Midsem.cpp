/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// Given a non-Charmichael number, design an algorithm that checks whether a given
// number is prime or not, with success probability at least 0.125. Justify your answer. You may assume Fermat’s Primality test as a black box. Analyze your algorithm.

bool isPrime(int n)
{
    if (n == 1)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
}