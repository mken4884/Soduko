#include "Soduko.h"
#include "SodukoSolver.h"
#include <iostream>

void buildSodukoAUTO(SodukoSolver &ss);
void buildSodukoAUTO1(SodukoSolver &ss);
void buildSodukoCMD(SodukoSolver &ss);

int main()
{
	SodukoSolver ss;
	buildSodukoAUTO1(ss);
	ss.solveSoduko();
	ss.isLegalMove(0,0,0);
	return 1;
}

void buildSodukoCMD(SodukoSolver &ss)
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

void buildSodukoAUTO(SodukoSolver &ss)
{
	ss.setPoint(0,0,0);
	ss.setPoint(3,0,5);
	ss.setPoint(4,0,6);
	ss.setPoint(5,0,8);
	ss.setPoint(6,0,1);
	ss.setPoint(7,0,7);
	ss.setPoint(8,0,3);
	ss.setPoint(1,1,5);
	ss.setPoint(3,1,0);
	ss.setPoint(8,1,8);
	ss.setPoint(1,2,6);
	ss.setPoint(3,2,3);
	ss.setPoint(0,3,2);
	ss.setPoint(1,3,1);
	ss.setPoint(2,3,3);
	ss.setPoint(8,3,6);
	ss.setPoint(2,4,4);
	ss.setPoint(4,4,2);
	ss.setPoint(6,4,3);
	ss.setPoint(0,5,6);
	ss.setPoint(6,5,7);
	ss.setPoint(7,5,4);
	ss.setPoint(8,5,2);
	ss.setPoint(5,6,3);
	ss.setPoint(7,6,6);
	ss.setPoint(0,7,8);
	ss.setPoint(5,7,0);
	ss.setPoint(7,7,3);
	ss.setPoint(0,8,7);
	ss.setPoint(1,8,3);
	ss.setPoint(2,8,1);
	ss.setPoint(3,8,6);
	ss.setPoint(4,8,8);
	ss.setPoint(5,8,4);
	ss.setPoint(8,8,5);
	ss.printSodukoMap();
	return;
}

void buildSodukoAUTO1(SodukoSolver &ss)
{
	ss.setPoint(2,0,1);
	ss.setPoint(3,0 ,4 );
	ss.setPoint(8,0 ,3);
	ss.setPoint(1,1 ,3 );
	ss.setPoint(4,1 ,1 );
	ss.setPoint(7,1 ,4 );
	ss.setPoint(0,2 ,7 );
	ss.setPoint(5,2 ,5 );
	ss.setPoint(6,2 ,6 );
	ss.setPoint(0,3 ,5 );
	ss.setPoint(5,3 ,0 );
	ss.setPoint(6,3 ,7 );
	ss.setPoint(1,4 ,0 );
	ss.setPoint(4, 4, 6);
	ss.setPoint(7,4 ,5);
	ss.setPoint(2,5 ,3 );
	ss.setPoint(3,5 ,1 );
	ss.setPoint(8,5 ,2 );
	ss.setPoint(2,6 ,7 );
	ss.setPoint(3,6 ,8 );
	ss.setPoint(8,6 ,6 );
	ss.setPoint(1,7 ,2 );
	ss.setPoint(4,7 ,0 );
	ss.setPoint(7, 7, 8);
	ss.setPoint(0,8 ,8);
	ss.setPoint(5, 8,4 );
	ss.setPoint(6,8,2);
	ss.printSodukoMap();
	return;
}