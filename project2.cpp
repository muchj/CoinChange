/*
CS325 - Project 2 
Contributors - Joseph Cuellar, Adam Much, Ryan Peters
Instructions: 
*/

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
//#include <Windows.h>

#define MAX_ARRAY_SIZE 40

using namespace std;

struct results {
    int numCoins;
    deque<int> coins;
};

////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////
void output(int* array, int arraySize, int toChange, string out, int algNo);
int inputFileLineCount(string inputFile);
void parseInputFile(int lineCount, string inputFileName, string outputFileName);
string createOutputFile(string inputFile);

void testRunTime(); // Not yet implemented.

////////////////////////////////////////////
// Algorithm Prototypes
////////////////////////////////////////////
results changeslow(int v[], int size, int a); // Not yet implemented.
results changegreedy(int v[], int size, int a);
results changedp(int v[], int size, int a);

///////////////////////////////////////////
// MAIN
////////////////////////////////////////////
int main(int argc, char *argv[])
{
	string inputFileName;
	string outputFileName;

	// If a file name is not given, prompt for it.
	if (argc < 2)
	{
		cout << "Which file do you wish to test? ";		
		cin >> inputFileName;		
	}
	
	// Otherwise use the given name at argv[1];
	else	
		inputFileName = string(argv[1]);	
	
	// Create the output file by inserting "change" into the input file name. 	
	outputFileName = createOutputFile(inputFileName);	
		
	parseInputFile(inputFileLineCount(inputFileName), inputFileName, outputFileName);

	return 0;
}

////////////////////////////////////////////
//START - Programs
////////////////////////////////////////////

////////////////////////////////////////////
//	output
//	- Prints the results of the selected algorithm to a file.
////////////////////////////////////////////
void output(int* array, int arraySize, int toChange, string fileOut, int algNo)
{
	ofstream out;

	results resOut;
	string algName;
	
	// Select which algorithm to run base on algNo.
	switch (algNo)
	{
		case 1:		resOut = changeslow(array, arraySize, toChange);
					algName = "changeslow";
					break;

		case 3:		resOut = changedp(array, arraySize, toChange);
					algName = "changedp";
					break;

		default:	resOut = changegreedy(array, arraySize, toChange);
					algName = "changegreedy";				
		
    }
    out.open(fileOut.c_str(), ofstream::out | ofstream::app);

	// This will produce the desired format for the output.
	int i;
	out << "\nAlgorithm " << algName << ":\n[";
	for (i = 0; i < resOut.coins.size() - 1; i++)
	{
		out << resOut.coins[i] << ", ";
	}
	out << resOut.coins[i];
	out << "]\n" << resOut.numCoins << endl;			

	out.close();
}

////////////////////////////////////////////
//	inputFileLineCount
//	- Gets line count of the input file.
////////////////////////////////////////////
int inputFileLineCount(string inputFileName)
{
	int lineCount = 0;
	string line;
	ifstream inputFile(inputFileName.c_str());
	while (inputFile.good())
	{
		getline(inputFile, line);		
		if(line == "")
		{
			break;
		}
		else
		{
			lineCount++;
		}
	}	
	inputFile.close();

	return lineCount;
}

////////////////////////////////////////////
// 	parseInputFile
//	- Is THE function called that is used for grading
//	- It reads in the input file.
//	- Crunches the sum for all  algorithms
//	- Outputs the result onto the screen AND  
////////////////////////////////////////////
void parseInputFile(int lineCount, string inputFileName, string outputFileName)
{
	// Array on every other line.
	int arrayCount = lineCount / 2;

	// Delimiters
	char comma = ',';
	char leftBracket = '[';
	char rightBracket = ']';
	
	ifstream inputFile(inputFileName.c_str());
	
	// Get characters until an int is next.
	char c; 
	int nextInt;
	
	// Make lineCount / 2 number of arrays for coin values.
	int V[arrayCount][MAX_ARRAY_SIZE]; 

	int arraySize[arrayCount]; // Corresponding array sizes.

	int A[arrayCount]; // Amount to change.

	int size = 0; // current size of one of the arrays.
	int i = 0; // Incremental number for line (array) from input lineCount.
	int j = 0; // V[i][j]
	
	if (inputFile)
	{
		while(!inputFile.eof())
		{
			inputFile >> c;
			if (c == comma || c == leftBracket)// We know an int is next.
			{					
				inputFile >> nextInt;				
				
				// Plug the int into its spot, and increment the spot and size.
				V[i][j] = nextInt;				
				j++;
				size++;
			}

			if (c == rightBracket) // End of an array.
			{	
				// Get the amount to change after the array of values.
				inputFile >> nextInt;
				A[i] = nextInt;

				// Plug in the array size, reset size to 0, and move to next array.
				arraySize[i] = size;
				size = 0;
				i++;
				j = 0;				
			}			
		}
		inputFile.close();		

		// Run algorithms on V[i][] and arraySize[i], for amounts A[i] here.		
		for (int k = 0; k < arrayCount; k++)
		{
			// Run output on each algorithm here.
			//output(V[k], arraySize[k], A[k], outputFileName, 1); // 1 for slow.
			output(V[k], arraySize[k], A[k], outputFileName, 2); // 2 for greedy.
			output(V[k], arraySize[k], A[k], outputFileName, 3); // 3 for dp.
		}
	}

	else
		cout << "\nUnable to open " << inputFileName << "." << endl;
	
}

////////////////////////////////////////////
// 	createOutputFile
//	- Accepts a string that corresponds to the input file name.
//  - Returns an appropriately named string to be used as the output file name.
////////////////////////////////////////////
string createOutputFile(string inputFile)
{
	string opFile = inputFile;
	int dotPosition = 0;	
	
	// Find the last dot in the string.
	for (int i = 0; i < opFile.length(); i++)
	{		
		if (opFile[i] == '.')
			dotPosition = i;		
	}	

	// No file extensions. Or at least no '.' in string.
	if (dotPosition == 0)
		opFile.insert(opFile.length(), "change.txt");
	
	// Some file extension, insert "change" at the dot's position.
	else
		opFile.insert(dotPosition, "change");		

	return opFile;
}

////////////////////////////////////////////
//END - Programs
////////////////////////////////////////////

////////////////////////////////////////////
// START - Algorithms
////////////////////////////////////////////

////////////////////////////////////////////
// Algorithm 1 - changeslow
////////////////////////////////////////////
results changeslow(int v[], int size, int a)
{
	int min_sum = INT_MAX;
	results r;
	r.numCoins = 0;
	
	if(a == 0)//Never going to happen, but just in case
	{
		r.coins.push_back(0);
		return r;
	}
	else
	{	//Base Case
		for(int i = 0; i < size; i++)
		{
			if(v[i] == a)
			{
				r.numCoins = 1;
				r.coins.push_back(a);
				return r;
			}
		}
	}
	
	//Recursive Case
	for(int j = a-1; j >= a / 2; j--)
	{
		results rLow;
		results rHigh;
		//minimum number of coins to make a-j cents
		rLow = changeslow(v, size, (a-j) );
		//minimum number coins to make j cents
		rHigh = changeslow(v, size, j);
		
		int sum = rLow.coins.size() + rHigh.coins.size();
		
		if(min_sum > sum)
		{
			r.numCoins = sum;
			deque<int>::iterator it = rLow.coins.begin();
			++it;
			rLow.coins.insert(it,rHigh.coins.begin(), rHigh.coins.end());
			r.coins = rLow.coins;
		}
	}
	return r;
}

////////////////////////////////////////////
// Algorithm 2 - changegreedy
////////////////////////////////////////////
results changegreedy(int v[], int size, int a)
{
    results r;
    r.numCoins = 0;
    int coin;    
    
    for(int i = size - 1; i >= 0; i--)
    {
        coin = a / v[i];
        r.coins.push_front(coin);
        r.numCoins += a / v[i];
        a %= v[i];
    }
    
    return r;    
}

////////////////////////////////////////////
// Algorithm 3 - changedp
////////////////////////////////////////////
results changedp(int v[], int size, int a)
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

	results r;
	r.numCoins = m[a];

	for (int i = 0; i < size; i++)
	{
		r.coins.push_back(T[a][i]);
	}
	
	return r;
}
