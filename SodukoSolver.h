#pragma once
#include "Soduko.h"
#include <cstdint>
#include <list>
#define GRID_SIZE 9
/*
*SodukoRow
*Holds the remaining numbers for each row
*
*/
struct SodukoRow {
	std::list<int8_t>* setNumbers;
	int8_t             rowNumber;
};

/*
*SodukoRow
*Holds the remaining numbers for each row
*
*/
struct SodukoColumn {
	std::list<int8_t>* setNumbers;
	int8_t             columnNumber;
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
	std::list<int8_t>* setNumbers;
	int8_t             gridNumber;
	int8_t			   possiblePointValuesSize;
};

/*
*SudokoPoint
*Holds information about each point in the grid including
*Possible values, if it has a value, and value
*/
struct SodukoPoint {
	std::list<int8_t>* remainingNumbers;
	bool               isSet;
	int8_t             pointValue;
	SodukoGrid*        grid;

};

class SodukoSolver {
public:
	SodukoSolver();
	~SodukoSolver();
	void setSoduko(Soduko* sodukoGrid);
	void solveSoduko();

//private:
	void analyzeRow(int xCoord, int yCoord);
	void analyzeColumn(int xCoord, int yCoord);
	void analyzeGrid(int xCoord, int yCoord);
	int8_t analyzeRemainingNumbers(int xCoord, int yCoord);
	bool isLegalMove(int xCoord, int yCoord, int value);
	bool setPoint(int xCoord, int yCoord, int value);
	bool isSolved();
	void printSodukoMap();
	bool setValue(int xCoord, int yCoord);
	SodukoPoint  sodukoMap[GRID_SIZE][GRID_SIZE];
	SodukoGrid   sodukoGridArray[GRID_SIZE];
	SodukoRow    sodukoRowArray[GRID_SIZE];
	SodukoColumn sodukoColumnArray[GRID_SIZE];

};