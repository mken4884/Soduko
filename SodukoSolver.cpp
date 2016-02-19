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
		this->sodukoGridArray[i].possiblePointValuesSize = GRID_SIZE*GRID_SIZE;

		//list autofills with zeroes so remove them here
		this->sodukoRowArray[i].setNumbers->unique();
		this->sodukoRowArray[i].setNumbers->remove(0);

		this->sodukoColumnArray[i].setNumbers->unique();
		this->sodukoColumnArray[i].setNumbers->remove(0);

		this->sodukoGridArray[i].setNumbers->unique();
		this->sodukoGridArray[i].setNumbers->remove(0);

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
	int i, j, pointValue,loopCount =0;

	//keep going until solved
	while (true)//!this->isSolved())
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
				/*	if ((pointValue = this->analyzeRemainingNumbers(i, j)) >= 0)
					{
						this->setPoint(i, j, pointValue);
					}
					else
					{*/
					if (loopCount > 0)
					{
						if (i == 4 && j == 5)
						{
							this->setValue(i, j);
						}
						else
						{
							this->setValue(i, j);
						}
					}
					
				//	}
					
				}
			}
		}
		loopCount++;
	}
	this->printSodukoMap();
	return;
}

/*
* SodukoSolver::analyzeRow
* updates the possible values on the desired point relative to its row
* by looking at the other points on the row and their values
*/
void SodukoSolver::analyzeRow(int xCoord, int yCoord)
{

	//coordinates of the current point
	int i = 0;

	//index for the point's remaining numbers
	int remainingNumbersIndex = 0;
	//index for the row's points' remaining numbers
	int rowRemainingNumbersIndex = 0;

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

	//remove an duplicates within every point
	this->sodukoMap[xCoord][yCoord].remainingNumbers->sort();
	this->sodukoMap[xCoord][yCoord].remainingNumbers->unique();

	//keep checking if the iterator still has numbers left
	while (rowIterator != this->sodukoRowArray[yCoord].setNumbers->end())
	{
		//remove numbers if they are already present in the row
		this->sodukoMap[xCoord][yCoord].remainingNumbers->remove(*rowIterator);
		//move iterator to next number
		rowIterator++;
	}
	
}


void SodukoSolver::analyzeColumn(int xCoord, int yCoord)
{	//coordinates of the current point
	int j = 0;


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
	std::list<int8_t>::iterator columnIterator = this->sodukoColumnArray[xCoord].setNumbers->begin();
	
	//remove an duplicates within every point
	this->sodukoMap[xCoord][yCoord].remainingNumbers->sort();
	this->sodukoMap[xCoord][yCoord].remainingNumbers->unique();


	//iterate while there are still numbers left
	while (columnIterator != this->sodukoColumnArray[xCoord].setNumbers->end())
	{
		//remove any numbers that are already set in the grid
		this->sodukoMap[xCoord][yCoord].remainingNumbers->remove(*columnIterator);
		columnIterator++;
	}
	//restart the iterator for each point being analyzed
	columnIterator = this->sodukoColumnArray[xCoord].setNumbers->begin();
	
}


void SodukoSolver::analyzeGrid(int xCoord, int yCoord)
{
	//the starting indices of the grid where the point lies
	int xGridBase = xCoord / 3;
	int yGridBase = (yCoord / 3) * 3;

	//the offset of x and y points for grid iteration
	int xGridOffset = xGridBase * 3;
	int yGridOffset = yGridBase;

	//find which grid the point corresponds to
	int gridIndex = xGridBase + yGridBase;
	int i, j;

	if (this->sodukoMap[xCoord][yCoord].grid->gridNumber != gridIndex)
	{
		while (1);
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (this->sodukoMap[i + xGridOffset][j + yGridOffset].isSet)
			{
				this->sodukoGridArray[gridIndex].setNumbers->push_back(this->sodukoMap[i + xGridOffset][j + yGridOffset].pointValue);
			}
		}
	}
	/* sort and remove any duplicates from previous analyzeGrid calls*/
	this->sodukoGridArray[gridIndex].setNumbers->sort();
	this->sodukoGridArray[gridIndex].setNumbers->unique();
	std::list<int8_t>::iterator gridIterator = this->sodukoGridArray[gridIndex].setNumbers->begin();


	//remove any duplicates within the point
	this->sodukoMap[xCoord][yCoord].remainingNumbers->sort();
	this->sodukoMap[xCoord][yCoord].remainingNumbers->unique();

	while (gridIterator != this->sodukoGridArray[gridIndex].setNumbers->end())
	{
		this->sodukoMap[xCoord][yCoord].remainingNumbers->remove(*gridIterator);
		gridIterator++;
	}

	//update the count of the number of possibles values for each point in the grid,
	//this will be used in another function call to try and resolve hard puzzles
	this->sodukoGridArray[gridIndex].possiblePointValuesSize = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (!this->sodukoMap[i + xGridOffset][j + yGridOffset].isSet)
			{
				this->sodukoGridArray[gridIndex].possiblePointValuesSize += this->sodukoMap[i + xGridOffset][j + yGridOffset].remainingNumbers->size();

			}
		}
	}
	
}

/*
Analyze the remaining numbers of all adjacent points to see if the given point contains
a remaining number that isn't present in any adjacent points
*/
int8_t SodukoSolver::analyzeRemainingNumbers(int xCoord, int yCoord)
{
	int i = 0;
	int j = 0;
	int possValueCount = 0;

	//the starting indices of the grid where the point lies
	int xGridBase = xCoord / 3;
	int yGridBase = (yCoord / 3) * 3;

	//the offset of x and y points for grid iteration
	int xGridOffset = xGridBase * 3;
	int yGridOffset = yGridBase;

	//find which grid the point corresponds to
	int gridIndex = xGridBase + yGridBase;
	

	//declare and define iterators to go through remaining numbers of both adjacent points and
	//the given point
	std::list<int8_t>::iterator pointRemNumItr = this->sodukoMap[xCoord][yCoord].remainingNumbers->begin();
	std::list<int8_t>::iterator adjPointRemNumItr;

	//analyze adjacent points from the row first

	//loop while there are remaining elements in the point
	while (pointRemNumItr != this->sodukoMap[xCoord][yCoord].remainingNumbers->end())
	{
		possValueCount = 0;

		//check each adjacent point as long as it's not set
		for (i = 0; i < GRID_SIZE; i++)
		{
			//set iterator to next point
			adjPointRemNumItr = this->sodukoMap[i][yCoord].remainingNumbers->begin();

			/*check adjacent remaining numbers with one of point's remaining numbers if
			the adjacent point isnt set, the adjacent point isnt the given point, and the adjacent iterator
			still has remaining numbers
			*/
			while (this->sodukoMap[i][yCoord].isSet == false && i != xCoord 
				&& adjPointRemNumItr != this->sodukoMap[i][yCoord].remainingNumbers->end())
			{
				//if the remaining number is present elsewhere break and go to next remaining point from the given point
				if (*pointRemNumItr == *adjPointRemNumItr)
				{
					possValueCount++;
					break;
				}
				adjPointRemNumItr++;
			}

			//if possValueCount>0, the remaining value isn't the sole one so break and move to the next remaining number for the given
			// point
			if (possValueCount > 0)
			{
				break;
			}
		}

		//if possValueCount ==0, the remaining number is the only one present in the grid so it must be the correct value
		if (possValueCount == 0)
		{
			return *pointRemNumItr;
		}
		//move to the next remaining value
		pointRemNumItr++;
	}
	
	//analyze adjacent points from the column
	pointRemNumItr = this->sodukoMap[xCoord][yCoord].remainingNumbers->begin();

	//if there are more remaining points, keep going
	while (pointRemNumItr != this->sodukoMap[xCoord][yCoord].remainingNumbers->end())
	{
		possValueCount = 0;
		//iterate through all points on the column
		for (j = 0; j < GRID_SIZE; j++)
		{
			//set the iterator to the next point
			adjPointRemNumItr = this->sodukoMap[xCoord][j].remainingNumbers->begin();
			/*check if any of the given point's remaining numbers are present in adjacent points only if
			the adjacent point isnt set, the adjacent point isnt set to the given point, and there are still
			remaining numbers in the adjacent iterator*/
			while (this->sodukoMap[xCoord][j].isSet == false && j != yCoord 
				&& adjPointRemNumItr != this->sodukoMap[xCoord][j].remainingNumbers->end())
			{
				//if the values equal each other, this remaining value isn't unique, move to the next one
				if (*pointRemNumItr == *adjPointRemNumItr)
				{
					possValueCount++;
					break;
				}
				adjPointRemNumItr++;
			}
			
			//if possValueCount > 0, this remaining value isnt unique so move to the next
			if (possValueCount > 0)
			{
				break;
			}
		}

		//if possValueCount == 0, this remaining value is unique so it must be the point's value
		if (possValueCount == 0)
		{
			return *pointRemNumItr;
		}

		pointRemNumItr++;

	}

	//analyze adjacent points from the grid
	pointRemNumItr = this->sodukoMap[xCoord][yCoord].remainingNumbers->begin();
	//if the point still has remaining values, keep going
	while (pointRemNumItr != this->sodukoMap[xCoord][yCoord].remainingNumbers->end())
	{
		possValueCount = 0;
		//iterate in the x direction
		for (i = 0; i < 3; i++)
		{
			//iterate in the y direction
			for (j = 0; j < 3; j++)
			{
				//get the next adjacent point's iterator
				adjPointRemNumItr = this->sodukoMap[i + xGridOffset][j + yGridOffset].remainingNumbers->begin();

				/*check this adjacent point if it isnt set, the adjacent point isnt the given point, the iterator still 
				has remaining values left*/
				while (this->sodukoMap[i + xGridOffset][j + yGridOffset].isSet == false && ((i != xCoord) && (j != yCoord))
					&& adjPointRemNumItr != this->sodukoMap[i + xGridOffset][j + yGridOffset].remainingNumbers->end())
				{
					if (*pointRemNumItr == *adjPointRemNumItr)
					{
						possValueCount++;
						break;
					}
					adjPointRemNumItr++;
				}

				//if possValueCount>0 the remaining number isn't unique so break
				if (possValueCount > 0)
				{
					break;
				}
			}
			//same as above, if possValueCount>0 the remaining number isn't unique so break
			if (possValueCount > 0)
			{
				break;
			}
		}

		//if possValueCount == 0, it is the only instance of the remaining number so it is the point's value
		if (possValueCount == 0)
		{
			return *pointRemNumItr;
		}

		pointRemNumItr++;
		
	}
	return -1;
}

bool SodukoSolver::isLegalMove(int xCoord, int yCoord, int value)
{
	return true;
}

bool SodukoSolver::setPoint(int xCoord, int yCoord, int value)
{
	this->sodukoMap[xCoord][yCoord].pointValue = (int8_t)value;
	this->sodukoMap[xCoord][yCoord].isSet = true;

	//update the grid and point values so remaining for both is correct
	this->analyzeRow(xCoord, yCoord);
	this->analyzeColumn(xCoord, yCoord);
	this->analyzeGrid(xCoord, yCoord);

	return true;
}

bool SodukoSolver::isSolved()
{
	int i;
	for (i = 0; i < GRID_SIZE; i++)
	{
		//do this combo to remove any duplicates
		this->sodukoGridArray[i].setNumbers->sort();
		this->sodukoGridArray[i].setNumbers->unique();

		if (this->sodukoGridArray[i].setNumbers->size() < (int8_t)GRID_SIZE)
		{
			return false;
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
	std::cout << "\n";
	std::cout << "\n";
}


bool SodukoSolver::setValue(int xCoord, int yCoord)
{
	//remove any duplicates
	this->sodukoMap[xCoord][yCoord].remainingNumbers->sort();
	this->sodukoMap[xCoord][yCoord].remainingNumbers->unique();
	
	//if there are two or three remaining numbers, it is possible that
	//the point contains a remaining number that isn't present in any of the points
	//or set in the grid, check and see and set if legal
	if ((this->sodukoMap[xCoord][yCoord].remainingNumbers->size() > 1 && this->sodukoMap[xCoord][yCoord].remainingNumbers->size() < 4)|| (xCoord == 4 && yCoord == 5))
	{
		int pointValue = this->analyzeRemainingNumbers(xCoord, yCoord);
		if (pointValue >= 0)
		{
			this->sodukoMap[xCoord][yCoord].pointValue = pointValue;
			this->sodukoMap[xCoord][yCoord].isSet = true;
			std::cout << xCoord << "  " << yCoord << '\n';
			this->printSodukoMap();
			return true;
		}
	}

	//if there is only one remaining number, that is the point's new value
	if (this->sodukoMap[xCoord][yCoord].remainingNumbers->size() == 1)
	{
		this->sodukoMap[xCoord][yCoord].pointValue = this->sodukoMap[xCoord][yCoord].remainingNumbers->front();
		this->sodukoMap[xCoord][yCoord].isSet = true; 
		std::cout << xCoord << "  " << yCoord << '\n';
		this->printSodukoMap();

	}
	return true;
}