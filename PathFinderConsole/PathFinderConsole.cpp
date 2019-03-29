// PathFinderConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <random>
using namespace std;
const int rows = 10;
const int cols = 10;
void reRun();//will prompt for user input and continue executing if user enters anything except 'exit;
class map {
	public:
		bool grid[rows][cols];
		
		
		void assignWalls(bool grid[rows][cols]);//will use random numbers to create the map via bools i.e. true is wall false is roamable land
	
};
void map::assignWalls(bool grid[rows][cols]) {
	
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(0, 99); // define the range
	for (int i =0;i < 10;i++) {
		for (int y = 0;y < 10;y++) {
			cout<<distr(eng)<<endl;//generate a number inclusive in the range
			grid[i][y] = (distr(eng) > 80) ? true : false;
		}

	}
	return;
}
int main()
{
	
	map map1;
	map1.assignwalls(map1.grid);
	for (int i = 0;i < rows;i++) {
		for (int y = 0;y < cols;y++) {
			cout << map1.grid[i][y] << " ";
		}
		cout << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
