#pragma once
class Soduko
{
public:
	Soduko();
	~Soduko();
	int  getSize();
	bool isSolved();
	void generateSoduko();
	void createSoduko();
	void sodukoAdd(Soduko* newGrid);
	void sodukoCreate();
	bool sodukoClean();
private:
	void isSolvable();
	char sodukoGrid[9][9];
	int size;
};

