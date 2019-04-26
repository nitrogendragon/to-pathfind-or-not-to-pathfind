#ifndef PathFinderConsole_H
#define PathFinderConsole_H
using namespace std;
// TODO: add headers that you want to pre-compile here
const int rows = 10;
const int cols = 10;

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
	int counter=0;//counter to be used in move function while loop 
	int movesTaken=0;//a counter for how many actual moves have been taken to reach the end or fail to reach the end
	int prevPos, curPos=0;//the current/previous position of the pathfinder in the map tracked as an integer related to the index of the maparray ary
	int sizeX, sizeY=0;//rows / columns for map
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

bool reRun();//will prompt for user input and restart the main function loop if user enters anything except 'exit';
int genRand(int low, int high); //generates random numbers
void ClearScreen();//clears screen in a sense by going multiple lines down the console
int getNum();////asks user for a number which at least for now will just be used to set up different sizes of maps
#endif //PCH_H#pragma once
