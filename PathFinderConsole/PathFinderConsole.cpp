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
		bool *mapArray;
		void Print();//function used to print dynamically sized map
		int pubdim = C;//value to be used to access C value from pathfinder class startendpoint function
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
		int counter;//counter to be used in move function while loop
		int movesTaken;//a counter for how many actual moves have been taken to reach the end or fail to reach the end
		int prevPos, curPos;//the current/previous position of the pathfinder in the map tracked as an integer related to the index of the maparray ary
		int sizeX, sizeY;//rows / columns for map
		int totSize = sizeX * sizeY;//may use for shortcutting to get total size
		bool *ary;//our dynamically allocatable array which will be a lightweight solution for representing the map as opposed to 2D attempts
		int *checkpoints;//this will hold all the points that we need to return to in the case that we reach a deadend while still having other paths we could have taken from these points
		int *decisionArray;//this array will hold integers that will correspond to whether a location has been visited and what action to take based on previous actions corresponding to the current int
		int *leftBounds;//this array will hold the left boundaries for ensuring that when trying to move particularly left we dont just jump to a row down on the other side of the map
		int *rightBounds;//this pointer to an int array will hold the left boundaries for ensuring that when trying to move right we dont just jum to a row up on the other side of the map
		int startpoint;//the value associated to the startpoint
		int endpoint;//the value associated to the endpoint
												  
		/* ary[i][j] is then rewritten as
		 * ary[i*sizeX + j]//reference in case I ever forget
		 */
	public:
		int setPosToCheckpoint(int mapsize);
		void setbounds(int dim);
		void move(int dim);  //handles decision making and execution of movement through map
		void startEndPoint(int dim); // sets up the starting point and ending point of the map exploration
		bool addwalls();//adds walls to the array being passed as a function argument
		pathfinder(int dim); //constructor
		~pathfinder(); //destructor
};


/*https://www.geeksforgeeks.org/create-dynamic-2d-array-inside-class-c/ link to where I got help for setting up a non-const initialzed '2D' array*/
map::map(int C)
{
	this->C = C;
	pubdim = this->C;//value to be used to access C value from pathfinder class startendpoint function
	// Create a dynamic array of pointers 
	gPtr = new bool*[C];
	mapArray = new bool[C*C];
	// Create a row for every pointer 
	for (int i = 0; i < C; i++)
	{
		// Note : Rows may not be contiguous 
		gPtr[i] = new bool[C];
		

		// Initialize all entries as false to indicate 
		// that there are no walls initially 
		memset(gPtr[i], false, C * sizeof(bool));
	}
	for (int y = 0;y < C*C;y++) {
		mapArray[y] = false;
	}
}

map::~map() {
	//gPtr = NULL;
	//mapArray = NULL;
	
	for (int i = 0; i < this->C;i++) {
		
			delete[]gPtr[i];
		
	}
	
	cout << "deleting gptr" << endl;
	delete [] gPtr;
	gPtr = NULL;
	cout << "gPtr is NULL" << endl;
	cout << "deleting map array" << endl;
	delete[]mapArray;
	mapArray = NULL;
	cout << "mapArray is NULL" << endl;
}


int genRand(int low =0, int high = 99) 
{
	int l = low;
	int h = high;
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(l, h); // define the range
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
			mapArray[i*C + y] = gPtr[i][y];
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
int getNum() 
{
	bool cont=true;
	int size=0;
	string ui;//user input
	std::cout << "we are starting/restarting and ui is " << ui << endl;
	while (cont==true) 
	{
		int size = 0;
		cout << size << endl;
		cout << "please enter a positive integer greater than 1 to use as for the square map dimensions" << endl;
		getline(cin, ui);
		bool has_only_digits = (ui.find_first_not_of("0123456789") == string::npos);//checks to see if we have a number
		if (has_only_digits == true) //if we do..
		{
			size = atoi(ui.c_str());//convert to integer
			if (size> 1) {
				cout << "the value of size is " << size << endl;//print it out
				cin.clear(); // clear the failed state
				cin.ignore(1000, '\n'); // throw away the non-numeric input
				cont = false;
				return size;//return our size for the 'box' map dimensions
				cout << "please press enter to confirm your value" << size << " " << endl;
			}
		}
	}
	
	
}

bool pathfinder::addwalls() {
		int rand=0;
		bool tf=true;
		
		rand = genRand();//grabs a random number in the predefined range
		cout << rand << endl;
		tf = (rand > 80) ? true : false;//determines whether the location will be a wall(true) or free roamable land(false)
				
			

		

		return tf;
}
int pathfinder::setPosToCheckpoint(int mapsize) 
{
	
	int length = mapsize;//the length of the checkpoints array
	for (int i = 0;i < length;i++) 
	{
		if (this->checkpoints[i] == 1) 
		{
			return i;//returns the point to set our curPos to
		}
	}
	return length;//if we dont have a checkpoint we will return a value that is one outside of the possible indexes which will lead us to determine we are trapped/the map is impossible to clear
	
}
void pathfinder::move(int dim)
{

	bool cantMove = false;//tells us whether we managed to find a spot with no further possible moves
	bool hitRight = false;
	bool hitLeft = false;
	int newPos=0;//the index we will move to if the current position is exhausted of options
	int mapsize = dim * dim;//used to make sure vertially we are still in the map if we move forward or back
	int forwardVal = dim;//number of indices we will add from current index position in array when going forward
	int backVal = -dim;//number of indices we will reduce from current index position in array when going back
	int leftVal = -1;//number of indices we will reduce from current index position in array when going left
	int rightVal = 1;//number of indices we will add from current index position in array when going right
	cout << "the startpoint is" << startpoint << endl;
	cout << "the endpoint is " << endpoint << endl;
	curPos = startpoint;
	//cout << "the ary vals are " << ary[forwardVal - 1] << endl;

	while (curPos != endpoint && counter < mapsize * 4)
	{
		++counter;
		cout << counter << endl;

		if (decisionArray[curPos] == 0)
		{
			decisionArray[curPos] += 1;
			checkpoints[curPos] = 1;//tells us that this is a point to return to
			if (curPos + forwardVal < mapsize && ary[curPos + forwardVal] == false)
			{
				
				cout << "we can and will go forward" << endl;
				curPos += forwardVal;
			}
		}
		else if (decisionArray[curPos] == 1)
		{
			decisionArray[curPos] += 1;
			
			if (curPos + leftVal >= 0 && ary[curPos + leftVal] == false &&(curPos+leftVal) )
			{
				
				for (int i = 0;i < forwardVal;i++) {//go through all the values in leftBounds to see if we will hit a left wall with the move
					if (leftBounds[i] == curPos + leftVal) {
						hitLeft = true;
						cout << "leftB is: " << leftBounds[i] << endl;
						cout << "curPos+leftVal is: " << curPos + leftVal << endl;
					}
				}
				if (hitLeft==false) {//if we didn't hit a wall we will proceed with the move
					prevPos = curPos;
					cout << "we can and will go left" << endl;
					curPos += leftVal;
				}
				else { cout << "we hit a left wall" << endl; hitLeft = false; }//reset for next move
			}

		}
		else if (decisionArray[curPos] == 2)
		{
			decisionArray[curPos] += 1;
			
			if (curPos + rightVal < mapsize && ary[curPos + rightVal] == false)
			{
				for (int i = 0;i < forwardVal;i++) {//go through all the values in rightBounds to see if we will hit a right wall with the move
					if (rightBounds[i] == (curPos + rightVal)) {
						hitRight = true;
						cout << "leftB is: " << rightBounds[i] << endl;
						cout << "curPos+leftVal is: " << curPos + rightVal << endl;
					}
				}
				if (hitRight==false) {//if we didn't hit a wall we will proceed with the move
					prevPos = curPos;
					cout << "we can and will go right" << endl;
					curPos += rightVal;
				}
				else { cout << "we hit a right wall" << endl; hitRight = false; }//reset for next move
			}

		}
		else if (decisionArray[curPos] == 3)
		{
			decisionArray[curPos] += 1;
			checkpoints[curPos] = 0;//tells us that this is no longer a point to return to
			if (curPos + backVal >= 0 && ary[curPos + backVal] == false)
			{
				
				cout << "we can and will go back/down" << endl;
				curPos += backVal;
			}
			
		}

		else if(decisionArray[curPos] == 4 && newPos!=mapsize)
		{	
			checkpoints[curPos] = 0;
			newPos = setPosToCheckpoint(mapsize);
			cout << "newPos is : " << newPos << endl;
		
			
			curPos = newPos;
			cout << "we have moved to a checkpoint: checkpoint position: "<< newPos << endl;
		}
		else
		{
			cantMove = true;
		}

		if (cantMove == false)
		{
			cout << "the current position is: " << curPos << endl;
			cout << "the decisionArray value is now: " << decisionArray[curPos] << endl;
		}
		else
		{
			cout << "you are trapped it seems" << endl;
			break;
		}


	}
	if (cantMove == false) {
		cout << "congratulations pathfinder! You made it to the endpoint!" << endl;
		cout << "you arrived at position: " << curPos << " and the endpoint is " << endpoint << endl;
	}
}


void pathfinder::setbounds(int dim) //sets the boundaries for the map in regards to where we cannot go left or right as in move one unit at a time through the single dimension array 
{
	int distToNextBounds = dim;//set distance for reaching next left or right boundary
	for (int i = 0;i < distToNextBounds;i++) 
	{
		leftBounds[i] = i * distToNextBounds;//set array values to integer correlating to left edge of map/map array ary
		rightBounds[i] = i * distToNextBounds + distToNextBounds - 1;
		cout << "left boundary #" << i << "is: " << leftBounds[i] << endl;
		cout << "right boundary #" << i << "is: " << rightBounds[i] << endl;
	}
}


void pathfinder::startEndPoint(int dim) 
{
	int count = 0;
	cout << "we made it to the start" << endl;
	int si = dim * dim;
	bool endpointset = false;//will be used to make sure we have a valid endpoint
	bool startpointset = false;//will be used to make sure we have a valid startpoint
	while (!endpointset ) //while we haven't found a valid endpoint..
	{
		count++;
		endpoint = genRand(0, si-1);//generate a random value within the range of the map
		if (ary[endpoint] == false)//check to see if there is a wall there
		{
			endpointset = true;//stop checking if there wasn't a wall and we have our endpoint
		}
		else 
		{
			cout << "still looking for endpoint" << endl;
		}
	}
	count = 0;
	while (!startpointset )//while we haven't found a valid startpoint...
	{
		count++;
		startpoint = genRand(0, si - 1);//generate a random value within the range of the map
		if (ary[startpoint] == false && startpoint != endpoint)// check to see if there is a wall there and if this is the endpoint
		{
			startpointset = true;//stop checking for walls and overlap and we have our starting point
		}
		else
		{
			cout << "still looking for starting point" << endl;
		}
	}
	cout << "this is the starting point " << startpoint <<endl;
	cout << "this is the endpoint " << endpoint << endl;
}


pathfinder::pathfinder(int dim):map(C)
{
	int bsize = dim;//sets size to dim dimensions for boundary arrays
	int size = dim*dim;//sets size to dim *dim dimensions
	cout << "size is " << size << endl;
	
	ary = new bool[size];
	
	for (int i = 0;i < size;i++) {
		if (&ary[i]){
			ary[i] = false;//setting initial values
			cout << "ary[" << i << "] is " << ary[i] << endl;
		}
	}
	checkpoints = new int[size];
	for (int i = 0;i < size;i++) {
		if (&checkpoints[i]) {
			checkpoints[i] = 0;//setting initial values
			cout << "checkpoints[" << i << "] is " << checkpoints[i] << endl;
		}
	}
	decisionArray = new int[size];
	for (int i = 0;i < size;i++) {
		if (&decisionArray[i]) {
			decisionArray[i] = 0;//setting initial values
			cout << "decisionArray[" << i << "] is " << decisionArray[i] << endl;
		}
	}

	leftBounds = new int[bsize];
	for (int i = 0;i < bsize;i++) {
		if (&leftBounds[i]) {
			leftBounds[i] = 0;//setting initial values
			cout << "leftBounds[" << i << "] is " << leftBounds[i] << endl;
		}
	}

	rightBounds = new int[bsize];
	for (int i = 0;i < bsize;i++) {
		if (&rightBounds[i]) {
			rightBounds[i] = 0;//setting initial values
			cout << "leftBounds[" << i << "] is " << rightBounds[i] << endl;
		}
	}
	
	for (int i = 0;i < (size);i++) {
		if (&ary[i]) {
			ary[i] = addwalls();
			cout << "ary[" << i << "] is " << ary[i] << endl;
		}
	}
	//sizeX = dim;//sets sizeX to value of whatever maps we want to use pubdim value which is just the C-value of the map. not certain if this was a good idea or not but it was a worthwhile experiment
	//sizeY = dim;//sets sizeY to value of whatever maps we want to use pubdim value which is just the C-value of the map. not certain if this was a good idea or not but it was a worthwhile experiment
	for (int i = 0; i < (size); i++) 
	{
			
			checkpoints[i] = 0;//sets all values to NULL since we dont have any place to return to at the start
			decisionArray[i] = 0;//this will set all values to zero which will correspond to not having visited or more accurately made a decision at the lcoation yet	
	}
	for (int i = 0; i < bsize;i++) 
	{
		leftBounds[i] = 0;//sets all values to zero since we dont want garbage
		rightBounds[i] = 0; //sets all values to zero since we dont want garbage
	}
	
	cout << "this is the size of ary" << sizeof(ary) << endl;
	cout << "this is the size of checkpoints" <<sizeof(checkpoints) << endl;
	cout << "this is the size of decisionArray" <<sizeof(decisionArray) << endl;
	cout << "pathfinder created" << endl;

}

pathfinder::~pathfinder()
{
	
	
	//cout << "we have begun destroying pathfinder" << endl;
	delete[] ary;
	cout << "ary is gone" << endl;
	ary = NULL;//get rid of dangly things
	cout << "ary is Null" << endl;
	delete[] checkpoints;
	cout << "checkpoints is gone" << endl;
	checkpoints = NULL;//get rid of dangly things
	cout << "checkpoints is null" << endl;
	delete[] decisionArray;//get rid of unncessary stuff here for now until we determine we want to use it longer
	cout << "decisionArray is gone" << endl;
	delete[] leftBounds;//get rid of unncessary stuff here for now until we determine we want to use it longer
	cout << "leftBounds array is gone" << endl;
	delete[] rightBounds;//get rid of unncessary stuff here for now until we determine we want to use it longer
	cout << "rightBounds array is gone" << endl;
	
	decisionArray = NULL;//get rid of dangly things
	cout << "decisionArray is null" << endl;
	cout << "pathfinder destroyed" << endl;
	
}



int main()
{
	ClearScreen();//clears the screen for us maybe...
	while (proceederval==true)//checks to make sure we still want to continue which on the first run we will ofc and thusly runs it and then depending on rerun function will decide whether to do so again
	{
		int dim = 0;//initializes the dimension int to 0
		dim = getNum();//asks the user for a number to set dim to
		cout << "the value of dim is " << dim << endl;//prints dim
		map map1(dim);//initializes map1 with a user defined size of dim
		map1.assignWalls(map1.grid);//randomly sets walls to the grid for map1 noting that this is the const based map which isn't using the user input dim dimensions
		
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
		cout <<"this is the dimension of map1 "<<map1.pubdim << endl;
		pathfinder pf1(dim);//sets up the pathfinder map using map1's data
		cout << "for some reason putting this here let's startendpoint work and without it doesn't" << endl;
		pf1.startEndPoint(dim);//sets up the start and endpoints for the pfs map
		pf1.setbounds(dim);//sets up the left and right boundaries to stop illegal moves through the single dimension array map ary
		pf1.move(dim);//will tell the pathfinder to move through the map until it reaches the endpoint... if it ever does which i doubt it will at the moment
		reRun();//asks whether the user wants to run the program again or close it
		//cout << "help" << endl;
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
