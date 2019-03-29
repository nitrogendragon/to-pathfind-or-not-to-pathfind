// PathFinderConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <random>
#include <string>
#include <stdlib.h>

using namespace std;
const int rows = 10;
const int cols = 10;
bool proceederval = true;//used for rerun function to determine whether to continue executing the program
void reRun();//will prompt for user input and continue executing if user enters anything except 'exit;
void ClearScreen()//clears the screen sord've
{
	cout << string(100, '\n');
}
class map {
	public:
		bool grid[rows][cols];
		
		
		void assignWalls(bool grid[rows][cols]);//will use random numbers to create the map via bools i.e. true is wall false is roamable land
	
};

//Function used for creating the grid. takes in a 2D array of size rows * cols
void map::assignWalls(bool grid[rows][cols]) {
	
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(0, 99); // define the range
	for (int i =0;i < 10;i++) {
		for (int y = 0;y < 10;y++) {
			cout<<distr(eng)<<endl;//generate a number inclusive in the range
			grid[i][y] = (distr(eng) > 80) ? true : false;//determines whether the location will be a wall(true) or free roamable land(false)
		}

	}
	return;
}

//Function asking for user input to determine whether to rerun the program
void reRun() {

	string choice;//holds the users value entered
	string quit = "exit";
	cout << "please enter 'exit' to stop the program or hit enter to continue ";
	getline(cin,choice);
	if (choice == "") {
		choice = "x";//sets choice to something so question mark statement works without entering a character
	}
	cout << choice << endl;
	proceederval= ((choice == "exit") ? false : true);//if choice is exit the program will quit otherwise it will run again upon hitting enter
	
}

int main()
{
	ClearScreen();
	while (proceederval==true)
	{
		map map1;
		map1.assignWalls(map1.grid);
		for (int i = 0;i < rows;i++) 
		{
			for (int y = 0;y < cols;y++) 
			{
				cout << map1.grid[i][y] << " ";
			}
			cout << endl;
		}
		reRun();
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
