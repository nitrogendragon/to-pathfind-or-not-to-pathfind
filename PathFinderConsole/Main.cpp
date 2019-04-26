#include "pch.h"
#include "PathFinderConsole.h"
#include <iostream>


int main()
{
	ClearScreen();//clears the screen for us maybe...
	bool proceederval = true;
	while ( proceederval == true)//checks to make sure we still want to continue which on the first run we will ofc and thusly runs it and then depending on rerun function will decide whether to do so again
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
		cout << "this is the dimension of map1 " << map1.pubdim << endl;
		pathfinder pf1(dim);//sets up the pathfinder map using map1's data
		cout << "for some reason putting this here let's startendpoint work and without it doesn't" << endl;
		pf1.startEndPoint(dim);//sets up the start and endpoints for the pfs map
		pf1.setbounds(dim);//sets up the left and right boundaries to stop illegal moves through the single dimension array map ary
		pf1.move(dim);//will tell the pathfinder to move through the map until it reaches the endpoint... if it ever does which i doubt it will at the moment
		proceederval = reRun();//asks whether the user wants to run the program again or close it
		cout << proceederval << endl;
		//cout << "help" << endl;
	}
}