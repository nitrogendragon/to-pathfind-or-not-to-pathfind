// PathFinderConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <random>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
using namespace std;
const int rows = 10;
const int cols = 10;
bool proceederval = true;//used for rerun function to determine whether to continue executing the program
void reRun();//will prompt for user input and continue executing if user enters anything except 'exit;
int genRand(int low, int high); //generates random numbers
void ClearScreen()//clears the screen sord've
{
	cout << string(100, '\n');
}
//the map to be navigated 
class map {
	protected:
		int C; // No. of cols
		bool** gPtr; //pointer to pointer of bools to be used for creating impromptu 2D array dynamically
	public:
		void Print();//function used to print dynamically sized map
		
		map(int C);   // Constructor 
		~map(); //destructor
	// function to add a wall to the map 
		void addWall();
		
		bool grid[rows][cols];//2D array using constants as size parameters 
		
		void assignWalls(bool grid[rows][cols]);//will use random numbers to create the map via bools i.e. true is wall false is roamable land
	
};
//our impromptu navigator who will treak through the perilous depths of the dungeon
class pathfinder : public map {
	protected:
		int sizeX, sizeY;//rows and columns for map
		bool *ary = new bool[sizeX*sizeY];//our dynamically allocatable array which will be a lightweight solution for representing the map as opposed to 2D attempts

		/* ary[i][j] is then rewritten as
		*ary[i*sizeX + j]//reference in case I ever forget
		*/
	public:
		void move();  //handles decision making and execution of movement through map
		pathfinder(); //constructor
		~pathfinder(); //destructor
};

/*https://www.geeksforgeeks.org/create-dynamic-2d-array-inside-class-c/ link to where I got help for setting up a non-const initialzed '2D' array*/
map::map(int C)
{
	this->C = C;

	// Create a dynamic array of pointers 
	gPtr = new bool*[C];

	// Create a row for every pointer 
	for (int i = 0; i < C; i++)
	{
		// Note : Rows may not be contiguous 
		gPtr[i] = new bool[C];

		// Initialize all entries as false to indicate 
		// that there are no walls initially 
		memset(gPtr[i], false, C * sizeof(bool));
	}
}

map::~map() {
	for (int i = 0; i < this->C;i++) {

		delete[]gPtr[i];
	}
	delete [] gPtr;
	gPtr = NULL;
}


int genRand(int low =0, int high = 99) 
{
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(0, 99); // define the range
	return distr(eng);
}


//Function used for creating the grid. takes in a 2D array of size rows * cols
void map::assignWalls(bool grid[rows][cols]) {
	
	int rand; 
	for (int i =0;i < 10;i++) {
		for (int y = 0;y < 10;y++) {
			rand = genRand();//grabs a random number in the predefined range
			cout<<rand<<endl;//generate a number inclusive in the range
			grid[i][y] = (rand > 80) ? true : false;//determines whether the location will be a wall(true) or free roamable land(false)
		}

	}
	return;
}


void map::addWall() {
	int rand;
	int size = this->C;//sets to the objects C value which is determined upon creation via contstructor value
	
	for (int i = 0;i < C;i++) {
		for (int y = 0;y < C;y++) {
			rand = genRand();//grabs a random number in the predefined range
			cout << rand << endl;//generate a number inclusive in the range
			gPtr[i][y] = (rand > 80) ? true : false;//determines whether the location will be a wall(true) or free roamable land(false)
		}

	}
	return;
	
}


void map::Print() {
	for (int i = 0;i < this->C;i++)
	{
		for (int y = 0;y < this->C;y++)
		{
			cout << gPtr[i][y] << " ";//prints dynamic grid layout
		}
		cout << endl;
	}
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


//asks user for a number which at least for now will just be used to set up different sizes of maps
int getNum() {
	int size=0;
	string ui;//user input
	
	while (size==0) 
	{
		cout << "please enter an integer to use as for the square map dimensions" << endl;
		getline(cin, ui);
		bool has_only_digits = (ui.find_first_not_of("0123456789") == string::npos);//checks to see if we have a number
		if (has_only_digits == true) //if we do..
		{
			int size = atoi(ui.c_str());//convert to integer
			cout << "the value of size is " << size << endl;
			return size;
		}
		
		
		
	}
	

	

	
}


void pathfinder::move()
{

}

pathfinder::pathfinder(): map(C)
{
	for (int i = 0; i < C; i++) 
	{
		for (int y = 0; y < C;y++) 
		{
			ary[i*C + y] = gPtr[i][y];//sets the values for pathfinders single dimension array to be those of the maps array of pointers to arrays map. this unnecesarry code may be changed later but its for practice right now
		}
	}

}

pathfinder::~pathfinder()
{

}


int main()
{
	ClearScreen();
	while (proceederval==true)
	{
		int dim = 0;
		dim = getNum();
		cout << "the value of dim is " << dim << endl;
		map map1(dim);//initializes map1 with a user defined size
		map1.assignWalls(map1.grid);//randomly sets walls to the grid for map1
		for (int i = 0;i < rows;i++) 
		{
			for (int y = 0;y < cols;y++) 
			{
				cout << map1.grid[i][y] << " ";//prints const based grid layout
			}
			cout << endl;
		}
		map1.addWall();//adds walls to dynamic '2D' array aka pointers to 1D arrays
		map1.Print();//prints out the values for the dynamic maps map/grid(gPtr) for map1
		
		reRun();//asks whether the user wants to run the program again or close it
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
