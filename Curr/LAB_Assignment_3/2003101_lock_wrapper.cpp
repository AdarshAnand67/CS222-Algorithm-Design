/*
    Lab 3

    CS222 - Algorithm Design Course

    This code is written as an assignment under prof Dr. Rahul.

    Author: Adarsh Anand

    Roll No: 2003101
*/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

set<int> s;           // storing all valid locker_ID values (unique)
vector<int> sec_keys; // storing all secondary keys (u1, u2, . . . , uk)

bool is_prime(int x)
{
    /*
        Input : x - an integer
        Output : true if x is prime, false otherwise
    */
    if (x <= 1)
        return false;
    for (int i = 2; i * i <= x; i++)
    { // checking if x is prime
        if (x % i == 0)
            return false;
    }
    return true;
}

void CONFIGURE(int k, int locker_ID, int L)
{
    /*
        The CONFIGURE module should take the number of users k, a locker id, and a key L as
        input and should generate k secondary keys (u1, u2, . . . , uk) and k distinct prime numbers
        p1, p2, . . . , pk. Each secondary key should be a 4 digit number meant for each of those k
        users, and the primary key L is meant for the locker. You may assume L < p1 ×p2 ×. . .×pk
        Further, the configuration module writes an entry to the file conf ig.txt where the entry is
        of the form: locker id − k, p1, p2, . . . , pk
    */

    int p[k]; // array of prime numbers - p1, p2, . . . , pk
    int u[k]; // array of secondary keys - u1, u2, . . . , uk
    int i;
    for (int i = 0; i < k; i++)
    {
        p[i] = rand() % 10000 + 1; // generating primes p1, p2, . . . , pk (4 digit only)
        while (!is_prime(p[i]) || p[i] > 9999 || p[i] < 1000)
        {
            // Making sure all numbers are 4 digit only and prime
            p[i] = rand() % 10000 + 1;
        }
    }

    /*
        Write locker_id to the file if locker_id is not already present in the file.
    */

    if (s.count(locker_ID))
    { // if locker_ID is already present in the file
        cout << "Locker ID already exists so not adding in config.txt" << endl;
        return;
    }
    else
    { // if locker_ID is not already present in the file

        s.insert(locker_ID); // adding locker_ID to the set

        // Append to file if locker_ID is not already present in the file
        ofstream file;
        file.open("config.txt", ios::app);
        s.insert(locker_ID);
        file << 'L' << locker_ID << ' ' << k << " "; // writing the locker id and number of users in the file
        for (i = 0; i < k; i++)
        {
            if (i == k - 1)
            {
                file << p[i] << endl; // remove last comma
            }
            else
            {
                file << p[i] << " "; // writing the prime numbers in the file
            }
        }
        file.close();
    }
    /*
        Display u1 u2 . . . uk to the screen
        u to be of exactly 4 digits
    */
    for (i = 0; i < k; i++)
    {
        u[i] = rand() % 10000 + 1; // generating secondary keys u1, u2, . . . , uk
        while (u[i] < 1000 || u[i] > 9999)
        { // if not 4 digits re-generate
            u[i] = rand() % 10000 + 1;
        }
        cout << "u" << i << " " << u[i] << " ";
        sec_keys.push_back(u[i]);
    }
    cout << endl;
}

int multi_inverse(int a, int b)
{
    /*
        Input : a, b - integers
        Output : x - integer such that a*x = 1 (mod b)

        Calculates the multiplicative inverse of a mod b
    */
    int x, y, d; // x, y, d are temporary variables
    x = 0;
    y = 1;
    d = b;
    while (a > 0)
    {
        int q = b / a; // q is the quotient
        int t = a;     // t is the temporary variable
        a = b % a;     // a is the remainder
        b = t;
        t = x;
        x = y - q * x; // x is the new value of x
        y = t;
    }
    y = y % d; // y is the inverse of a (mod b)
    if (y < 0)
        y += d;
    return y; // return the inverse of a mod b
}

int USE(int locker_ID, int L, vector<int> u)
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
    */

    // Read Locker_ID,k,p1,p2,...,pk from the file config.txt

    ifstream file;           // creating a file
    file.open("config.txt"); // opening the file

    int k;
    string locker_id;

    file >> locker_id >> k;
    int p[k];
    for (int i = 0; i < k; i++)
    {
        file >> p[i];
    }
    file.close(); // closing the file

    /*
        Finding L using Chinese Remainder Theorem
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
        int Mi_inv = multi_inverse(Mi, p[i]); // Mi_inv = (M/p1)^-1 mod p1, (M/p2)^-1 mod p2, ..., (M/pk)^-1 mod pk
        L += (p[i] * Mi * Mi_inv) % M;        // L = L + (p1*M/p1*(M/p1)^-1) + (p2*M/p2*(M/p2)^-1) + ... + (pk*M/pk*(M/pk)^-1)
    }

    L = L % M;     // L = L mod M
    return abs(L); // return L to the main function
}

int main()
{
    /*
        Mention your preference (1/2/3):
            1. CONFIGURE
            2. USE
            3. EXIT
    */

    cout << "-----------------Hello!-------------------" << endl;
    cout << "-----------------Welcome!-----------------" << endl;

    bool flag = true;    // flag to check if the user wants to continue
    int k, locker_ID, L; // k is the number of users, locker_ID is the locker ID, L is the shared locker

    while (flag)
    { // while loop to keep the program running

        cout << "-----------------Enter your choice for n (1/2/3) : -----------------" << endl;

        cout << "1. CONFIGURE" << endl;
        cout << "2. USE" << endl;
        cout << "3. EXIT" << endl;

        int n;
        cin >> n;

        if (n == 1) // CONFIGURE
        {
            int m;
            cout << "-----------------Enter your choice for m (1/2/3) : -----------------" << endl;

            cout << "1. Add New Locker Entry" << endl;
            cout << "2. Delete a locker entry" << endl;
            cout << "3. Exit" << endl;

            cin >> m;

            if (m == 1) // ADD A NEW ENTRY
            {
                // Taking inputs
                cout << "Enter the locker ID (5 chars without L): ";
                cin >> locker_ID;
                cout << "Enter the number of users: ";
                cin >> k;
                cout << "Enter the 10 digit key (L) : ";
                cin >> L;

                CONFIGURE(k, locker_ID, L); // configuring the locker
            }

            else if (m == 2) // DELETE A LOCKER ENTRY
            {
                /*
                    Enter LockerId:
                    (Display) Entry Successfully Deleted/Invalid Entry
                    If lockerID found delete the entry from the file
                */

                cout << "Enter the locker ID to delete (5 chars without L): ";
                cin >> locker_ID;

                string to_remove = "L" + to_string(locker_ID);

                // mark the locker_ID as invalid only those locker_ID are valid which are present in the set s

                if (s.count(locker_ID))
                {
                    // if the locker_ID is present in the set s
                    s.erase(locker_ID);
                    cout << "Entry " << to_remove << " successfully deleted" << endl;
                }
                else
                {
                    // if the locker_ID is not present in the set s
                    cout << "Invalid Entry" << endl;
                }
            }
            else if (m == 3) // GO BACK to main menu
            {
                continue;
            }
            else
            {
                cout << "Invalid choice" << endl;
                continue;
            }
        }

        else if (n == 2) // USE
        {
            // Enter LockerId:
            cout << "Enter the locker ID (5 chars without L): ";
            cin >> locker_ID;

            // If Id present in config.txt

            if (s.count(locker_ID))
            {
                // if the locker_ID is present in the set s

                bool flag = true; // all the secondary keys are valid
                int u[k];         // array of secondary keys - u1, u2, . . . , uk

                for (int i = 0; i < k; i++)
                {
                    cout << "Enter the secondary key for user " << i + 1 << " : ";
                    cin >> u[i]; // reading the secondary keys
                }

                for (int i = 0; i < k; i++)
                {
                    if (u[i] != sec_keys[i])
                    {
                        // if any of the secondary keys is invalid
                        flag = false;
                        break;
                    }
                }

                // If manages to successfully reconstruct the key
                // This should match what you fed in during the configuration phase

                if (flag)
                {
                    int ans = USE(locker_ID, L, sec_keys);
                    cout << "******The Locker Accesscode is : " << ans << "******" << endl;
                }

                else
                {
                    // If any of the secondary keys is invalid
                    cout << "Invalid Accesscode returning to main menu" << endl;
                }
            }

            else
            {
                // If the locker_ID is not present in the set s
                cout << "Invalid Entry" << endl;
            }

            USE(locker_ID, L, sec_keys); // using the locker to get L
        }

        else if (n == 3) // TERMINATE
        {
            cout << "---------------- Thanks! --------------------" << endl;
            flag = false;
        }

        else // INVALID
        {
            cout << "Invalid choice closing the program" << endl;
            flag = false;
        }
    }
    // Clear the set s
    s.clear();

    // Clear the map sec_keys
    sec_keys.clear();

    // Do you want to clear the file config.txt?
    cout << "You append the locker ID to the file config.txt";
    cout << "Do you want to clear the file config.txt? (0/1) : ";
    int x;
    cin >> x;
    if (x == 1)
    {
        // Clear the file config.txt
        ofstream fout;
        fout.open("config.txt"); // open the file
        fout.close();            // close the file
        cout << "File config.txt cleared" << endl;
    }
    else
    {
        // Do nothing
        cout << "Did not clear the file config.txt" << endl;
    }
    return 0;
}
