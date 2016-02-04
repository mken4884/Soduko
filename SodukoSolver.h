#pragma once
#include "Soduko.h"
#define GRID_SIZE 9

/*
*SudokoPoint
*Holds information about each point in the grid including 
*Possible values, if it has a value, and value
*/
struct SodukoPoint {
	char* remainingNumbers;
	bool  isSet;
	char  pointValue;
};


/*
*SodukoGrid
*Holds the remaining numbers for each grid
*Labeled as such
* 0 1 2
* 3 4 5
* 6 7 8
*/
struct SodukoGrid {
	char* remainingNumbers;
	char  gridNumber;
};

class SodukoSolver {
public:
	SodukoSolver();
	~SodukoSolver();
	void setSoduko(Soduko* sodukoGrid);
	void solveSoduko();
	void analyzeRow(int xCoord, int yCoord);
	void analyzeColumn(int xCoord, int yCoord);
	void analyzeGrid(int xCoord, int yCoord);
	bool isLegalMove(int xCoord, int yCoord, int value);
	bool setGrid();
private:
	SodukoPoint sodukoGrid[GRID_SIZE][GRID_SIZE];
	SodukoGrid  sodukoGridArray[GRID_SIZE];


};