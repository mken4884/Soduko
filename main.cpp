#include "Soduko.h"
#include "SodukoSolver.h"
#include <iostream>

void buildSoduko(SodukoSolver ss);

int main()
{
	SodukoSolver ss;
	ss.printSodukoMap();
	buildSoduko(ss);
	ss.solveSoduko();
	ss.isLegalMove(0,0,0);
	return 1;
}

void buildSoduko(SodukoSolver ss)
{
	int i, j;
	int input;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			std::cout << " x coord " << i << " y coord " << j << '\n';
			std::cin >> input;
			if(input > 0)
			{
				ss.setPoint(i, j, input-1);
			}
		}
	}
	ss.printSodukoMap();
}