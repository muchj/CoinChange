#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <deque>
//#include <Windows.h>

#define MAX_ARRAY_SIZE 40

using namespace std;

struct results {
    int numCoins;
    deque<int> coins;
};

void changedp(int v[], int size, int a);

///////////////////////////////////////////
// MAIN
////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int Values[] = {1, 3, 7, 12};
	int amount = 31;

	changedp(Values, 4, amount);

	return 0;
}

void changedp(int v[], int size, int a)
{
	int T[a + 1][size]; // Number of each coin for a given amount, a.
	int m[a + 1]; // Minimum number of total coins for a given amount, a.

	// Initialize all T[n][p] to zeroes, and m[n] to n.	
	for (int n = 0; n < a + 1; n++)
	{
		for (int p = 0; p < size; p++)
		{
			T[n][p] = 0;
		}
		m[n] = n;
	}
	
	int sum, coin, remainder;
	// Outer loop will calculate m for each value of a.
	for (int i = 1; i < a + 1; i++)	
	{		
		// Inner loop will calculate the number of each coin.
		for (int j = 0; j < size; j++)
		{			
			if (i >= v[j]) // Don't even bother if the coin is too large.
			{
				coin = 1; // Try one coin first.
				remainder = i;
				while (remainder >= v[j]) // Go until too many coins.
				{
					// Whatever is left over will have a value in T[][] and an m[].
					remainder = i - coin * v[j];

					// This many coins plus the remainder might be optimum.
					sum = coin + m[remainder];

					// If that's the case, fill in m[] and T[][].
					if (sum <= m[i])
					{
						m[i] = sum;	

						// Copy the remainder's array first.
						for (int k = 0; k < size; k++)
						{
							T[i][k] = T[remainder][k];
						}
						// Then, add coin in the appropriate spot.
						T[i][j] = T[i][j] + coin;
					}
					coin++;
				}								
			}			
		}		
	}

	// Print the table for testing.
	for (int n = 0; n < a + 1; n++)
	{
		cout << n << "\t";
		for (int p = 0; p < size; p++)
		{
			cout << T[n][p] << "\t";
		}
		cout << m[n] << endl;
	}
}
