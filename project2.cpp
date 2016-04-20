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
//#include <Windows.h>

#define MAX_ARRAY_SIZE 40
#define INPUT_FILE "Coin1.txt"
//#define MIN_ELEMENT -5
//#define MAX_ELEMENT 15

using namespace std;

struct results{
    int sum;
    int startIdx;
    int endIdx;
};

////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////
void output(int* array, int arrSize, int sum, int startIdx, int endIdx, int algNo);
int inputFileLineCount();
void parseInputFile(int lineCount);

void testRunTime();

////////////////////////////////////////////
// Algorithm Prototypes
////////////////////////////////////////////


////////////////////////////////////////////
// MAIN
////////////////////////////////////////////
int main(int argc, char *argv[]){
	
	parseInputFile(inputFileLineCount());
	return 0;
}

////////////////////////////////////////////
//START - Programs
////////////////////////////////////////////

////////////////////////////////////////////
//	inputFileLineCount
//	- Gets line count of INPUT_FILE.
////////////////////////////////////////////
int inputFileLineCount()
{
	int lineCount = 0;
	string line;
	ifstream inputFile(INPUT_FILE);
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
//	- It reads in INPUT_FILE.
//	- Crunches the sum for all  algorithms
//	- Outputs the result onto the screen AND  
////////////////////////////////////////////
void parseInputFile(int lineCount)
{
	// Array on every other line.
	int arrayCount = lineCount / 2;

	// Delimiters
	char comma = ',';
	char leftBracket = '[';
	char rightBracket = ']';
	
	ifstream inputFile(INPUT_FILE);
	
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
			for (int l = 0; l < arraySize[k]; l++)
			{
				cout << V[k][l] << "\t";
			}
			cout << "\tSize: " << arraySize[k];
			cout << "\n" << A[k] << endl;
		}
		/*results resOut;
		for (int k = 0; k < lineCount; k++)
		{
			resOut = mssAlgorithm1(A[k], arraySize[k]);
			output(A[k], arraySize[k], resOut.sum, resOut.startIdx, resOut.endIdx, 1);

			resOut = mssAlgorithm2(A[k], arraySize[k]);
			output(A[k], arraySize[k], resOut.sum, resOut.startIdx, resOut.endIdx, 2);

			// Alg 3 should always start at index 0, right?
			resOut = mssAlgorithm3(A[k], 0, arraySize[k] - 1);		
			output(A[k], arraySize[k], resOut.sum, resOut.startIdx, resOut.endIdx, 3);

			resOut = mssAlgorithm4(A[k], arraySize[k]);
			output(A[k], arraySize[k], resOut.sum, resOut.startIdx, resOut.endIdx, 4);
		}*/
	}

	else
		cout << "\nUnable to open \"Coins1.txt\"." << endl;
	
}
