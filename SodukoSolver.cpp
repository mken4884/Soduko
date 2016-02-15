#include "SodukoSolver.h"
#include <stdlib.h>
#include <iostream>

//heres another line to add

SodukoSolver::SodukoSolver()
{
	int i, j, k;
	for (i = 0; i < GRID_SIZE; i++)
	{
		//allocate memory for the row struct and set the row value
		this->sodukoRowArray[i].setNumbers = new std::list<int8_t>(GRID_SIZE);
		this->sodukoRowArray[i].rowNumber = i;

		//allocate memory for the column struct and set the column value
		this->sodukoColumnArray[i].setNumbers = new std::list<int8_t>(GRID_SIZE);
		this->sodukoColumnArray[i].columnNumber = i;

		//allocate memory for the grid struct and set the grid value
		this->sodukoGridArray[i].setNumbers = new std::list<int8_t>(GRID_SIZE);
		this->sodukoGridArray[i].gridNumber = i;

		//allocate memory and set values for map points
		for (j = 0; j < GRID_SIZE; j++)
		{
			this->sodukoMap[i][j].remainingNumbers = new std::list<int8_t>(GRID_SIZE);
			this->sodukoMap[i][j].isSet = false;
			this->sodukoMap[i][j].pointValue = -1;

			//Set grid pointer to the corresponding grid the point belongs in
			int xPointCoord = i / 3;
			int yPointCoord = (j / 3)*3;
			this->sodukoMap[i][j].grid = &this->sodukoGridArray[xPointCoord + yPointCoord];

			
			//set the possible values for each point
			for (k = 0; k < GRID_SIZE; k++)
			{
				this->sodukoMap[i][j].remainingNumbers->push_back(k);
			}
		}
	}

	return;
}

SodukoSolver::~SodukoSolver()
{
	/*
	int i, j;

	//iterate through the grid and deallocate memory for grid and grid points
	for (i = 0; i < GRID_SIZE; i++)
	{
		free(this->sodukoGridArray[i].remainingNumbers);

		for (j = 0; j < GRID_SIZE; j++)
		{
			free(this->sodukoMap[i][j].remainingNumbers);
		}
	}
	*/
}

void SodukoSolver::setSoduko(Soduko* sodukoMap)
{

}

void SodukoSolver::solveSoduko()
{
	int i, j, k;

	//keep going until solved
	while (!this->isSolved())
	{
		for (i = 0; i < GRID_SIZE; i++)
		{
			for (j = 0; j < GRID_SIZE; j++)
			{
				//if the point already has a value ignore it
				if (!this->sodukoMap[i][j].isSet)
				{
					//update the soduko map and this particular point
   					this->analyzeRow(i, j);
					this->analyzeColumn(i, j);
					this->analyzeGrid(i, j);
					this->setValue(i, j);
				}
			}
		}
	}
	this->printSodukoMap();
	return;
}

/*
* SodukoSolver::analyzeRow
* updates the possible values on the desired row
* by looking at the other points on the row and their values
*/
void SodukoSolver::analyzeRow(int xCoord, int yCoord)
{

	//coordinates of the current point
	int i = 0;
	int k = 0;

	/* iterate through the row and see if any points already have a 
	set value. If they do, add that value to the list of set values for this row*/
	for (i = 0; i < GRID_SIZE; i++)
	{
		if (this->sodukoMap[i][yCoord].isSet)
		{
			this->sodukoRowArray[yCoord].setNumbers->push_back(this->sodukoMap[i][yCoord].pointValue);
		}
	}
	/* sort and remove any duplicates from previous analyzeRow calls*/
	this->sodukoRowArray[yCoord].setNumbers->sort();
	this->sodukoRowArray[yCoord].setNumbers->unique();
	std::list<int8_t>::iterator rowIterator = this->sodukoRowArray[yCoord].setNumbers->begin();
	for (i = 0; i < GRID_SIZE; i++)
	{
		//keep checking if the iterator still has numbers left
		while (rowIterator != this->sodukoRowArray[yCoord].setNumbers->end())
		{
			//remove numbers if they are already present in the row
			this->sodukoMap[i][yCoord].remainingNumbers->remove(*rowIterator);
			//move iterator to next number
			rowIterator++;
		}
		//restart iterator at beginning for each point being analyzed
		rowIterator = this->sodukoRowArray[yCoord].setNumbers->begin();
	}
}


void SodukoSolver::analyzeColumn(int xCoord, int yCoord)
{	//coordinates of the current point
	int j = 0;
	int k = 0;

	/* iterate through the column and see if any points already have a 
	set value. If they do, add that value to the list of set values for this row*/
	for (j = 0; j < GRID_SIZE; j++)
	{
		if (this->sodukoMap[xCoord][j].isSet)
		{
			this->sodukoColumnArray[xCoord].setNumbers->push_back(this->sodukoMap[xCoord][j].pointValue);
		}
	}
	/* sort and remove any duplicates from previous analyzeColumn calls*/
	this->sodukoColumnArray[xCoord].setNumbers->sort();
	this->sodukoColumnArray[xCoord].setNumbers->unique();
	std::list<int8_t>::iterator columnIterator = this->sodukoRowArray[xCoord].setNumbers->begin();
	for (j = 0; j < GRID_SIZE; j++)
	{
		//iterate while there are still numbers left
		while (columnIterator != this->sodukoColumnArray[xCoord].setNumbers->end())
		{
			//remove any numbers that are already set in the grid
			this->sodukoMap[xCoord][j].remainingNumbers->remove(*columnIterator);
			columnIterator++;
		}
		//restart the iterator for each point being analyzed
		columnIterator = this->sodukoColumnArray[xCoord].setNumbers->begin();
	}
}


void SodukoSolver::analyzeGrid(int xCoord, int yCoord)
{
	//the starting indices of the grid where the point lies
	int xGridBaseCoord = xCoord/3;
	int yGridBaseCoord = (yCoord / 3) * 3;
	
	//find which grid the point corresponds to
	int gridIndex = xGridBaseCoord + yGridBaseCoord;
	int i, j, k;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (this->sodukoMap[i+xGridBaseCoord][j+yGridBaseCoord].isSet)
			{
				this->sodukoGridArray[gridIndex].setNumbers->push_back(this->sodukoMap[i + xGridBaseCoord][j + yGridBaseCoord].pointValue);
			}
		}
	}
	/* sort and remove any duplicates from previous analyzeGrid calls*/
	this->sodukoGridArray[gridIndex].setNumbers->sort();
	this->sodukoGridArray[gridIndex].setNumbers->unique();
	std::list<int8_t>::iterator gridIterator = this->sodukoGridArray[gridIndex].setNumbers->begin();

	for (j = 0; j < 3; j++)
	{
		for (k = 0; k < 3; k++)
		{
			while (gridIterator != this->sodukoGridArray[gridIndex].setNumbers->end())
			{
				this->sodukoMap[i+xGridBaseCoord][j+yGridBaseCoord].remainingNumbers->remove(*gridIterator);
				gridIterator++;
			}
			gridIterator = this->sodukoGridArray[gridIndex].setNumbers->begin();
		}
	}
}

bool SodukoSolver::isLegalMove(int xCoord, int yCoord, int value)
{
	return true;
}

bool SodukoSolver::setPoint(int xCoord, int yCoord, int value)
{
	this->sodukoMap[xCoord][yCoord].pointValue = value;
	this->sodukoMap[xCoord][yCoord].isSet = true;

	//update the grid and point values so remaining for both is correct
	this->analyzeRow(xCoord, yCoord);
	this->analyzeColumn(xCoord, yCoord);
	this->analyzeGrid(xCoord, yCoord);

	return true;
}

bool SodukoSolver::isSolved()
{
	int i,j;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (this->sodukoGridArray[i].remainingNumbers[j])
			{
				return false;
			}
		}
	}
	return true;
}


void SodukoSolver::printSodukoMap()
{
	int i = 0;
	int j = 0;
	for (j = 0; j < GRID_SIZE; j++)
	{
		for (i = 0; i < GRID_SIZE; i++)
		{
			if (i % 3 == 0) {
				std::cout << "  ";
			}
			if (this->sodukoMap[i][j].pointValue == -1) std::cout << "|";
			else std::cout << (int) (this->sodukoMap[i][j].pointValue+1);
		}
		std::cout << "\n";
		if ((j+1) % 3 == 0) std::cout << "\n";
	}
}


bool SodukoSolver::setValue(int xCoord, int yCoord)
{

	//temp variables to determine if the point can have a value
	int k = 0;
	int possibleValueSize = 0;
	int possibleValue = -1;
	//iterate through the possible values and see if only 1 value remains
	for (k = 0; k < GRID_SIZE; k++)
	{
		if (this->sodukoMap[xCoord][yCoord].remainingNumbers[k] == true)
		{
			possibleValueSize++;
			possibleValue = k;
		}
	}

	//if the value is legal, update the point and all other affected points and grids
	if (possibleValueSize == 1 && this->isLegalMove(xCoord, yCoord, possibleValue))
	{
		this->setPoint(xCoord, yCoord, possibleValue);
		/*DEBUG DELETEME*/
		this->printSodukoMap();
		/*DEBUG DELETEME*/

	}
	return true;
}