/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * 
 *
 * Created on April 22, 2016, 3:35 PM
 */

#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <fstream>

using namespace std; 

struct results {
    int numCoins;
    deque<int> coins;
};

results changegreedy(int v[], int size, int a);
results changedp(int v[], int size, int a);
results changeslow(int v[], int size, int a);

results changeslow(int v[], int size, int a)
{  
    
        results m;
	results r;
	r.numCoins = 0;
        
        for(int i = 0; i < size; i++)
        {
            r.coins.push_back(0);
        }
	
        if(a == 0)
        {
            return r;
        }
        
	for(int j = 0; j < size; j++)
	{
            if(v[j] <= a)
            {
                m = changeslow(v, size, a - v[j]);
                r.coins[j] = m.coins[j] + 1;
                r.numCoins = m.numCoins + 1;
            }
	}
          
        return r;
}

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

void output(int* array, int arrSize, int totalCoins, deque<int> coins, string algNo)
{
    ofstream out;
    string filename; //need to change
    
    //need to change file name;
    out.open("change.txt", ofstream::out | ofstream::app);	
    
	// Print the algorithm number.
	out << "Algorithm " << algNo << ":\n";
	cout << "Algorithm " << algNo << ":\n";

	// Print the maximum subsequence.
	out << "\n\nNumber of coins:\n";
	cout << "\n\nNumber of coins:\n";	
	
	for(int i = 0; i < coins.size(); i++)
        {
            out << coins[i] << ' ';
            cout << coins[i] << ' ';
        }
	
	// Print the sum.
	out <<"\n\nTotal Number of coins:\n" << totalCoins << endl << endl;
	cout <<"\n\nTotal number of coins:\n" << totalCoins << endl << endl;	
	
	out.close(); 	
}
/*
 * 
 */
int main(int argc, char** argv) {
    
    int v[] = {1, 3, 7, 12};
    int a = 29;
    results r;
    
    r = changeslow(v, 4, a);
    
    for(int i = 0; i < r.coins.size(); i++)
    {
        cout << r.coins[i] << endl;
    }
    cout << r.numCoins << endl;
    
    //output(v, 4, r.numCoins, r.coins, "changegreedy");

    return 0;
}