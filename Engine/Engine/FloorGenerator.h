//#pragma once
//
//#include <vector>
//
//#define LIMIT 12
//
//enum ROOMS{
//	ROOMONEDOWN,
//	ROOMONEUP,
//	ROOMONELEFT,
//	ROOMONERIGHT,
//	ROOMTWOH,
//	ROOMTWOV,
//	ROOMTWODR,
//	ROOMTWOUR,
//	ROOMTWODL,
//	ROOMTWOUL,
//	ROOMTHREEDOWN,
//	ROOMTHREEUP,
//	ROOMTHREELEFT,
//	ROOMTHREERIGHT,
//	ROOMFOUR
//};
//
//enum COR{
//	CORONEDOWN,
//	CORONEUP,
//	CORONELEFT,
//	CORONERIGHT,
//	CORTWOH,
//	CORTWOV,
//	CORTWODR,
//	CORTWOUR,
//	CORTWODL,
//	CORTWOUL,
//	CORTHREED,
//	CORTHREEU,
//	CORTHREEL,
//	CORTHREER,
//	CORFOUR
//
//};
//
//class FloorGenerator
//{
//private:
//	char **map;
//
//	
//
//	char onewayD ; char onewayU ;	char onewayL ;char onewayR ;
//	char twowayH ; char twowayV ;
//	char twowayDR ;char twowayUR ;char twowayDL ;char twowayUL ;
//	char threewayD ;char threewayU ;char threewayL;char threewayR ;
//	char fourway ;
//
//	char roomoneD ;char roomoneU ;char roomoneL ;char roomoneR ;
//	char roomtwoH ;char roomtwoV ;
//	char roomtwoDR ;char roomtwoUR ;char roomtwoDL ;char roomtwoUL ;
//	char roomthreeD ;char roomthreeU ;char roomthreeL ;char roomthreeR ;
//	char roomfour ;
//	char blank ;
//
//	FloorGenerator();
//
//	bool checkLeft(int x, int y);
//	bool checkLeft2(int x, int y);
//
//	bool checkUp(int x, int y);
//	bool checkUp2(int x, int y);
//
//	bool checkRight(int x, int y);
//	bool checkRight2(int x, int y);
//
//	bool checkDown(int x, int y);
//	bool checkDown2(int x, int y);
//
//	void assignUpR(int x, int y, char currentroom);
//	void assignUpC(int x, int y, char currentroom);
//
//	void assignDownR(int x, int y, char currentroom);
//	void assignDownC(int x, int y, char currentroom);
//
//	void assignLeftR(int x, int y, char currentroom);
//	void assignLeftC(int x, int y, char currentroom);
//
//	void assignRightR(int x, int y, char currentroom);
//	void assignRightC(int x, int y, char currentroom);
//
//	void nextRC(char cor_room, int x, int y);
//
//public:
//	~FloorGenerator();
//
//	static FloorGenerator *instance();
//	void init();
//
//	void generateMap();
//
//	void resetMap();
//
//	char** getMap();
//	void shutdown();
//};