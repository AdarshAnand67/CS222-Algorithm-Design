/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

bool is_prime(int x)
{
    // Return true if x is prime, false otherwise
    if (x <= 1)
        return false;
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

void configure(int k, int locker_ID, int L)
{
    /*
The CONFIGURE module should take the number of users k, a locker id, and a key L as
input and should generate k secondary keys (u1, u2, . . . , uk) and k distinct prime numbers
p1, p2, . . . , pk. Each secondary key should be a 4 digit number meant for each of those k
users, and the primary key L is meant for the locker. You may assume L < p1 ×p2 ×. . .×pk
Further, the configuration module writes an entry to the file conf ig.txt where the entry is
of the form:

locker id − k, p1, p2, . . . , pk
Further, given the sequence p1, p2, . . . , pk, one can construct

a unique L (0 ≤ L < Y
k
i=1
pi) from the sequence (u1, u2, . . . , uk) provided ui < pi for 1 ≤ i ≤ k.
*/
    int p[k]; // array of prime numbers - p1, p2, . . . , pk
    int u[k]; // array of secondary keys - u1, u2, . . . , uk
    int i;
    for (i = 0; i < k; i++)
    {
        p[i] = rand() % 10000 + 1; // generating primes p1, p2, . . . , pk
        while (!is_prime(p[i]))
        { // if not prime re-generate
            p[i] = rand() % 10000 + 1;
        }
    }

    ofstream file;                          // creating a file
    file.open("config.txt");                // opening the file
    file << locker_ID << " - " << k << ","; // writing the locker id and number of users in the file
    for (i = 0; i < k; i++)
    {
        if (i == k - 1)
        {
            file << p[i] << endl; // remove last comma
        }
        else
        {
            file << p[i] << ","; // writing the prime numbers in the file
        }
    }
    file.close();
}

int multi_inverse(int a, int b)
{
    // Return the inverse of a mod b
    int x, y, d;
    x = 0;
    y = 1;
    d = b;
    while (a > 0)
    {
        int q = b / a;
        int t = a;
        a = b % a;
        b = t;
        t = x;
        x = y - q * x;
        y = t;
    }
    y = y % d;
    if (y < 0)
        y += d;
    return y;
}

void use(int locker_ID, int L, int u[])
{
    /*
The USE module is supposed to read the locker id and fetch the value of k and the pis
from the configuration file conf ig.txt to begin with. Further, it queries the user(s) to feed in
u1, u2, . . . , uk (order matters) as input. The task in hand is to generate L using p1, p2, . . . , pk
so as to let the users access the shared locker.
Your implementation should be based on Chinese Remainder Theorem. You may assume the
number of users to be 2 to begin with and pick a pair of sufficiently large prime numbers such
that the product of these two prime numbers is at least 1000. Then you may try to increase it
to 3, and then 4.
If your code works for at most 5 users, that’s fine.
**Bonus credit for code that works for arbitrary k.
*/
    ifstream file;           // reading the file
    file.open("config.txt"); // opening the file
    int locker_id, k;
    string line;
    getline(file, line);
    // extracting the locker id and number of users
    // split on -
    stringstream ss(line);
    string token;
    // cout<<line<<endl;
    int i = 0;
    while (getline(ss, token, '-'))
    {
        if (i == 0)
        {
            locker_id = stoi(token);
        }
        else if (i == 1)
        {
            k = stoi(token);
        }
        i++;
    }
    cout << "------------------------------------" << endl;
    cout << "Locker ID: " << locker_id << endl;
    cout << "Number of users: " << k << endl;
    file.close();

    int p[k];                 // array of prime numbers - p1, p2, . . . , pk
    ifstream file2;           // reading the file
    file2.open("config.txt"); // opening the file
    getline(file2, line);     // extracting the prime numbers
    stringstream ss2(line);   // splitting on ,
    i = 0;
    while (getline(ss2, token, ','))
    {
        if (i == 0)
        {
            // skip the locker id
        }
        else
        {
            p[i - 1] = stoi(token); // storing the prime numbers in the array
        }
        i++;
    }
    cout << "Prime numbers [pi]: ";
    for (i = 0; i < k; i++)
    {
        cout << p[i] << " ";
    }
    cout << endl;
    cout << "Secondary keys [ui]: ";
    for (int i = 0; i < k; i++)
    {
        cout << u[i] << " ";
    }
    cout << endl;

    file2.close();

    // Finding L using Chinese Remainder Theorem
    /*
        Solving the equation
        L = p1 mod(u1) , u1<p1
        L = p2 mod(u2) , u2<p2
        ...
        L = pk mod(uk) , uk<pk
    */
    int M = 1; // M is the product of all the prime numbers
    for (i = 0; i < k; i++)
    {
        M *= u[i]; // M = u1*u2*...*uk
    }
    for (int i = 0; i < k; i++)
    {
        int Mi = M / p[i];                    // Mi = M/p1, M/p2, ..., M/pk
        int Mi_inv = multi_inverse(Mi, p[i]); // Mi_inv = M/p1, M/p2, ..., M/pk
        L += (p[i] * Mi * Mi_inv) % M;        // L = L + (p1*M/p1*(M/p1)^-1) + (p2*M/p2*(M/p2)^-1) + ... + (pk*M/pk*(M/pk)^-1)
    }
    L = L % M; // L = L mod M
    cout << "L : " << L << endl;
    cout << "---------------- Thanks! --------------------" << endl;
}

int main()
{
    cout << "-----------------Hello!-------------------" << endl;
    int k, locker_ID, L;
    cout << "Enter the number of users: ";
    cin >> k;
    cout << "Enter the locker ID: ";
    cin >> locker_ID;
    cout << "Enter the key: ";
    cin >> L;

    // k=3,locker_ID=11,L=12;

    configure(k, locker_ID, L); // configuring the locker

    // int u[k] = {7,29,31};

    int u[k]; // array of secondary keys - u1, u2, . . . , uk
    for (int i = 0; i < k; i++)
    {
        cout << "Enter the secondary key for user " << i + 1 << " : ";
        cin >> u[i]; // reading the secondary keys
    }

    use(locker_ID, L, u); // using the locker to get L
    return 0;
}