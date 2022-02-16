
/*
    Lab 3

    CS222 - Algorithm Design Course

    This code is written as an assignment under prof Dr. Rahul.

    Author: Adarsh Anand

    Roll No: 2003101
*/

/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

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

int Get_L(int locker_ID, int L, vector<int> u)
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
    */

    // Read Locker_ID,k,p1,p2,...,pk from the file config.txt
    ifstream file;
    file.open("config.txt");
    int k;
    string locker_id;
    file >> locker_id >> k;
    int p[k];
    for (int i = 0; i < k; i++)
    {
        file >> p[i];
    }
    file.close();

    // Finding L using Chinese Remainder Theorem
    /*
        Solving the equation
        L = p1 mod(u1) , u1<p1
        L = p2 mod(u2) , u2<p2
        ...
        L = pk mod(uk) , uk<pk
    */
    int M = 1; // M is the product of all the prime numbers
    for (int i = 0; i < k; i++)
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
}
// int main()
// {
//     /*
//         Mention your preference (1/2/3):
//             1. CONFIGURE
//             2. USE
//             3. EXIT
//     */

//     cout << "-----------------Hello!-------------------" << endl;
//     cout << "-----------------Welcome!-----------------" << endl;
//     int n;
//     cout << "Enter your choice (1/2/3) : ";
//     cin >> n;

//     int k, locker_ID, L;
//     while (1)
//     {

//         if (n == 1) // CONFIGURE
//         {
//             int m;
//             cout << "Enter your choice (1/2/3) : ";
//             cin >> m;
//             if (m == 1) // ADD A NEW ENTRY
//             {
//                 // Taking inputs
//                 cout << "Enter the locker ID (5 chars): ";
//                 cin >> locker_ID;
//                 cout << "Enter the number of users: ";
//                 cin >> k;
//                 cout << "Enter the 10 digit key (L) : ";
//                 cin >> L;

//                 // CONFIGURE(k, locker_ID, L); // configuring the locker
//             }

//             // k=3,locker_ID=11,L=12;
//             else if (m == 2) // DELETE A LOCKER ENTRY
//             {
//                 /*
//                     Enter LockerId:
//                     (Display) Entry Successfully Deleted/Invalid Entry
//                     If lovkerId found delete the entry from the file
//                 */
//                 cout << "Enter the locker ID (5 chars): ";
//                 cin >> locker_ID;
//                 // removing the entry from the file
//                 ofstream file;
//                 file.open("config.txt", ios::out | ios::trunc);
//                 file.close();
//             }
//             else if (m == 3) // GO BACK
//             {
//                 continue;
//             }
//         }
//         // int u[k] = {7,29,31};
//         else if (n == 2)
//         {
//             int u[k]; // array of secondary keys - u1, u2, . . . , uk
//             for (int i = 0; i < k; i++)
//             {
//                 cout << "Enter the secondary key for user " << i + 1 << " : ";
//                 cin >> u[i]; // reading the secondary keys
//             }

//             USE(locker_ID, L, u); // using the locker to get L
//         }
//         else
//         {
//             cout << "---------------- Thanks! --------------------" << endl;
//             return 0;
//         }
//     }
// }

int main(){
    int L = Get_L(11,12,{7,29,31});
}
