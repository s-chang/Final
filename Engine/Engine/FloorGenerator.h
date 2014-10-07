#pragma once

#include <vector>

#define LIMIT 12

enum ROOMS{
	ROOMONEDOWN,
	ROOMONEUP,
	ROOMONELEFT,
	ROOMONERIGHT,
	ROOMTWOH,
	ROOMTWOV,
	ROOMTWODR,
	ROOMTWOUR,
	ROOMTWODL,
	ROOMTWOUL,
	ROOMTHREEDOWN,
	ROOMTHREEUP,
	ROOMTHREELEFT,
	ROOMTHREERIGHT,
	ROOMFOUR
};

enum COR{
	CORONEDOWN,
	CORONEUP,
	CORONELEFT,
	CORONERIGHT,
	CORTWOH,
	CORTWOV,
	CORTWODR,
	CORTWOUR,
	CORTWODL,
	CORTWOUL,
	CORTHREED,
	CORTHREEU,
	CORTHREEL,
	CORTHREER,
	CORFOUR

};

class FloorGenerator
{
private:
	char **map;

	const char onewayD = 'D'; const char onewayU = 'U';	const char onewayL = 'L';const char onewayR = 'R';
	const char twowayH = 'H'; const char twowayV = 'V';
	const char twowayDR = 'Z';const char twowayUR = 'X';const char twowayDL = 'C';const char twowayUL = 'B';
	const char threewayD = '1';const char threewayU = '2';const char threewayL = '3';const char threewayR = '4';
	const char fourway = '5';

	const char roomoneD = 'd';const char roomoneU = 'u';const char roomoneL = 'l';const char roomoneR = 'r';
	const char roomtwoH = 'h';const char roomtwoV = 'v';
	const char roomtwoDR = 'z';const char roomtwoUR = 'x';const char roomtwoDL = 'c';const char roomtwoUL = 'b';
	const char roomthreeD = '!';const char roomthreeU = '@';const char roomthreeL = '#';const char roomthreeR = '$';
	const char roomfour = '%';
	const char blank = ' ';

	FloorGenerator();

	bool checkLeft(int x, int y);
	bool checkLeft2(int x, int y);

	bool checkUp(int x, int y);
	bool checkUp2(int x, int y);

	bool checkRight(int x, int y);
	bool checkRight2(int x, int y);

	bool checkDown(int x, int y);
	bool checkDown2(int x, int y);

	void assignUpR(int x, int y, char currentroom);
	void assignUpC(int x, int y, char currentroom);

	void assignDownR(int x, int y, char currentroom);
	void assignDownC(int x, int y, char currentroom);

	void assignLeftR(int x, int y, char currentroom);
	void assignLeftC(int x, int y, char currentroom);

	void assignRightR(int x, int y, char currentroom);
	void assignRightC(int x, int y, char currentroom);

	void nextRC(char cor_room, int x, int y);

public:
	~FloorGenerator();

	static FloorGenerator *instance();
	void init();

	void generateMap();

	void resetMap();

	char** getMap();
	void shutdown();
};