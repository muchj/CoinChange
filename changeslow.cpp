// Example program
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <climits>
#include <vector>
#include <cstring>
#include <sstream>
#include <limits>
#define MAXSIZE 20
using namespace std;

struct results {
    int numCoins;
    deque<int> coins;
};

int changeSlow(int v[], int cca[], int amount, int length);
void initArray(int arr[], int length);
void outputCoinArray(int cca[], int length, int count);

int main()
{
    int coinCountArray2[MAXSIZE];
    initArray(coinCountArray2, MAXSIZE);
    int coinCount;
  int v[3] = {1,2,5};
  int size = 3;
  int a = 10;
  
 coinCount = changeSlow(v, coinCountArray2, a, size);
  outputCoinArray(coinCountArray2, size, coinCount);
  
  return 0;
}
void outputCoinArray(int cca[], int length, int count)
{

    std::cout << "[";

	for (int i = 0; i < length; i++)
	{
		std::cout << cca[i];

		if (i < length - 1) { 
			std::cout << ", ";

		}
	}
	std::cout << "]\n" << count << "\n\n";
}
void initArray(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = 0;
	}
}
int changeSlow(int v[], int cca[], int amount, int length)
{
	// Assign default value to total coin count
	int aggregateCount = numeric_limits<int>::max();
	
	// Base case
	for (int i = 0; i < length; i++)
	{
		if (amount == v[i])
		{
			cca[i] += 1;
			return 1;
		}
	}
	
	// Recursive case
	for (int i = 1; i < amount; i++)
	{
		int ccaI[length];
		int ccaKI[length];
		initArray(ccaI, length);
		initArray(ccaKI, length);
		int icent = changeSlow(v, ccaI, i, length);
		int k_icent = changeSlow(v, ccaKI, amount - i, length);
		if(icent + k_icent < aggregateCount) 
		{
			aggregateCount =  icent + k_icent;
			for(int j = 0; j < length; j++)
			{
				ccaI[j] += ccaKI[j];
			}
			for(int k = 0; k < length; k++)
			{
				cca[k] = ccaI[k];
			}
		}
	}
	
	return aggregateCount;
}
