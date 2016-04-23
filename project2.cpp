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
void output(int* array, int arraySize, int toChange, string out, string algName);
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
//	- 
////////////////////////////////////////////
void output(int* array, int arraySize, int toChange, string fileOut, string algName)
{
	ofstream out;

	results resOut;
	resOut = changegreedy(array, arraySize, toChange);
    
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

		
		// DELETE THIS BLOCK LATER used for testing.
		for (int k = 0; k < arrayCount; k++)
		{
			for (int l = 0; l < arraySize[k]; l++)
			{
				cout << V[k][l] << "\t";
			}
			cout << "\tSize: " << arraySize[k];
			cout << "\n" << A[k] << endl;
		}
		// END DELETE BLOCK
		

		// Run algorithms on V[i][] and arraySize[i], for amounts A[i] here.
		results resOut; // delete later. Output is now calling the algorithms.
		int m; // delete later.
		for (int k = 0; k < arrayCount; k++)
		{
		// Run output on each algorithm here.
		output(V[k], arraySize[k], A[k], outputFileName, "greedy");


        // DELETE THIS BLOCK LATER used for testing
			// Run the algorithm.
			resOut = changegreedy(V[k], arraySize[k], A[k]);
			
			// This will produce the desired format for the output.
			cout << "\nAlgorithm changegreedy:\n["; 
			for (m = 0; m < resOut.coins.size() - 1; m++)
			{
				cout << resOut.coins[m] << ", ";
			}
			cout << resOut.coins[m];
			cout << "]\n" << resOut.numCoins << endl;

		// END DELETE BLOCK

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
    results r;
    int table[a + 1][size];
    
    for(int i = 0; i < size; i++)
    {
        r.coins.push_back(0);
    }
    
    for(int i = 0; i <= size; i++)
    {
        table[0][i] = 1;
    }    
}
