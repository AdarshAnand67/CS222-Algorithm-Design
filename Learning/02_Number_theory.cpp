/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

#define MOD 1000000007

int mod_add(int a, int b, int m)
{
    // Returns the sum of a and b modulo m
    return (a % m + b % m) % m;
}

int mod_sub(int a, int b, int m)
{
    return (a % m - b % m + m) % m;
}

int mod_mul(int a, int b, int m)
{
    return (a % m * b % m) % m;
}

int mod_div(int a, int b, int m)
{
    // Returns the division of a and b modulo m
    return (a % m * mod_inv(b, m) % m) % m;
}

int mod_inv(int a, int m)
{
    // Returns the modular inverse of a modulo m
    return mod_pow(a, m - 2, m);
}

int mod_power(int a, int b, int m)
{
    // Returns the power of a modulo m
    int ans = 1;
    while (b > 0)
    {
        if (b & 1)
            ans = mod_mul(ans, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return ans;
}

bool isPrime(int x)
{
    // Check if x is prime
    if (x == 1)
        return false;
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

int binExp(int x, int y)
{
    // Returns x^y
    int ans = 1;
    while (y > 0)
    {
        if (y & 1)
            ans = mod_mul(ans, x, MOD);
        x = mod_mul(x, x, MOD);
        y >>= 1;
    }
    return ans;
}

bool prime[n + 1];
void sieveOfEratosthenes(int n)
{
    // Sieve of Eratosthenes
    memset(prime, true, sizeof(prime));
    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p])
        {
            for (int i = p * 2; i <= n; i += p)
                prime[i] = false;
        }
    }
    for (int p = 2; p <= n; p++)
    {
        if (prime[p])
            cout << p << " ";
    }
}

int extendedGCD(int a, int b, int &x, int &y)
{
    // Returns the GCD of a and b and their respective multiplicative inverses
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int g = extendedGCD(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - (a / b) * y;
    return g;
}

int gcd(int a, int b)
{
    // Returns the GCD of a and b
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    // Returns the LCM of a and b
    return a / gcd(a, b) * b;
}

int fermat(int a, int b)
{
    // Returns the modular inverse of a modulo b
    int x, y;
    extendedGCD(a, b, x, y);
    return (x % b + b) % b;
}

int chineseRemainder(int a, int b, int c, int d)
{
    // Returns the solution of x = a mod b and y = c mod d
    int x, y;
    extendedGCD(b, d, x, y);
    return mod_mul(a, x, b) % b * mod_mul(c, y, d) % d;
}

signed main()
{
    int
}