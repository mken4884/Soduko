#include "SodukoSolver.h"
#include <stdlib.h>
#include <iostream>

//heres another line to add

SodukoSolver::SodukoSolver()
{
	int i, j, k;
	for (i = 0; i < GRID_SIZE; i++)
	{
		//allocate memory for the grid struct and set the grid value
		this->sodukoGridArray[i].remainingNumbers = (char*)malloc(GRID_SIZE*sizeof(char));
		this->sodukoGridArray[i].gridNumber = i;

		//set the possible values of each grid
		for (k = 0; k < GRID_SIZE; k++)
		{
			this->sodukoGridArray[i].remainingNumbers[k] = 1;
		}

		//allocate memory and set values for map points
		for (j = 0; j < GRID_SIZE; j++)
		{
			this->sodukoMap[i][j].remainingNumbers = (char*)malloc(GRID_SIZE*sizeof(char));
			this->sodukoMap[i][j].isSet = false;
			this->sodukoMap[i][j].pointValue = -1;

			//Set grid pointer to the corresponding grid the point belongs in
			int xPointCoord = i / 3;
			int yPointCoord = (j / 3)*3;
			this->sodukoMap[i][j].grid = &this->sodukoGridArray[xPointCoord + yPointCoord];

			
			//set the possible values for each point
			for (k = 0; k < GRID_SIZE; k++)
			{
				this->sodukoMap[i][j].remainingNumbers[k] = 1;
			}
		}
	}
}

SodukoSolver::~SodukoSolver()
{

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
					//temp variables to determine if the point can have a value
					int possibleValueSize = 0;
					int possibleValue = -1;
					//iterate through the possible values and see if only 1 value remains
					for (k = 0; k < GRID_SIZE; k++)
					{
						if (this->sodukoMap[i][j].remainingNumbers[k] > -1)
						{
							possibleValueSize++;
							possibleValue = k;
						}
					}

					//if the value is legal, update the point and all other affected points and grids
					if (possibleValueSize == 1 && this->isLegalMove(i,j,possibleValue))
					{
						this->sodukoMap[i][j].isSet = true;
						this->sodukoMap[i][j].pointValue = possibleValue;

						this->analyzeRow(i, j);
						this->analyzeColumn(i, j);
						this->analyzeGrid(i, j);
					}
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
	//holds legal values for this row only
	char possibleValues[9] = { 1,1,1,1,1,1,1,1,1 };
	//coordinates of the current point
	int i = 0;
	int j = yCoord;
	int k = 0;

	for (i = 0; i < GRID_SIZE; i++)
	{
		if (this->sodukoMap[i][j].isSet)
		{
			possibleValues[this->sodukoMap[i][j].pointValue] = -1;
		}
	}
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (k = 0; k < GRID_SIZE; k++)
		{
			if (this->sodukoMap[i][j].remainingNumbers[k] > possibleValues[k])
			{
				this->sodukoMap[i][j].remainingNumbers[k] = possibleValues[k];
			}
		}
	}
}

void SodukoSolver::analyzeColumn(int xCoord, int yCoord)
{
	//holds legal values for this column only
	char possibleValues[9] = { 1,1,1,1,1,1,1,1,1 };
	//coordinates of the current point
	int i = xCoord;
	int j = 0;
	int k = 0;

	for (j = 0; j < GRID_SIZE; j++)
	{
		if (this->sodukoMap[i][j].isSet)
		{
			possibleValues[this->sodukoMap[i][j].pointValue] = -1;
		}
	}
	for (j = 0; j < GRID_SIZE; j++)
	{
		for (k = 0; k < GRID_SIZE; k++)
		{
			if (this->sodukoMap[i][j].remainingNumbers[k] > possibleValues[k])
			{
				this->sodukoMap[i][j].remainingNumbers[k] = possibleValues[k];
			}
		}
	}
}

void SodukoSolver::analyzeGrid(int xCoord, int yCoord)
{
	//the starting indices of the grid where the point lies
	int xGridBaseCoord = xCoord/3;
	int yGridBaseCoord = (yCoord / 3) * 3;

	int gridIndex = xGridBaseCoord + yGridBaseCoord;
	int i, j, k;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (this->sodukoMap[i+xGridBaseCoord][j+yGridBaseCoord].isSet)
			{
				this->sodukoGridArray[gridIndex].remainingNumbers[this->sodukoMap[i+xGridBaseCoord][j+yGridBaseCoord].pointValue] = -1;
			}
		}
	}

	for (j = 0; j < 3; j++)
	{
		for (k = 0; k < 3; k++)
		{
			if (this->sodukoMap[i + xGridBaseCoord][j + yGridBaseCoord].remainingNumbers[k] > this->sodukoGridArray[gridIndex].remainingNumbers[k])
			{
				this->sodukoMap[i + xGridBaseCoord][j + yGridBaseCoord].remainingNumbers[k] = this->sodukoGridArray[gridIndex].remainingNumbers[k];
			}
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
			if (this->sodukoGridArray[i].remainingNumbers[j] != -1)
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
			std::cout << (int) this->sodukoMap[i][j].pointValue;
		}
		std::cout << "\n";
		if ((j+1) % 3 == 0) std::cout << "\n";
	}
}
