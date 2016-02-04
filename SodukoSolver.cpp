#include "SodukoSolver.h"
#include <stdlib.h>

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

		//allocate memory and set values for grid points
		for (j = 0; j < GRID_SIZE; j++)
		{
			this->sodukoGrid[i][j].remainingNumbers = (char*)malloc(GRID_SIZE*sizeof(char));
			this->sodukoGrid[i][j].isSet = false;
			this->sodukoGrid[i][j].pointValue = -1;
			
			//set the possible values for each point
			for (k = 0; k < GRID_SIZE; k++)
			{
				this->sodukoGrid[i][j].remainingNumbers[k] = 1;
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
			free(this->sodukoGrid[i][j].remainingNumbers);
		}
	}
}

void SodukoSolver::setSoduko(Soduko* sodukoGrid)
{

}

void SodukoSolver::solveSoduko()
{
	//here is a new comment
}

void SodukoSolver::analyzeRow(int xCoord, int yCoord)
{

}

void SodukoSolver::analyzeColumn(int xCoord, int yCoord)
{

}

void SodukoSolver::analyzeGrid(int xCoord, int yCoord)
{

}

bool SodukoSolver::isLegalMove(int xCoord, int yCoord, int value)
{

}

bool SodukoSolver::setGrid()
{

}