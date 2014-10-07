//#include "FloorGenerator.h"
//
//FloorGenerator::FloorGenerator()
//{
//
//}
//
//FloorGenerator::~FloorGenerator()
//{}
//
//FloorGenerator *FloorGenerator::instance()
//{
//	FloorGenerator map;
//	return &map;
//}
//
//void FloorGenerator::init()
//{
//	map = new char*[LIMIT];
//	for(int i = 0; i < LIMIT; i++)
//		map[i] = new char[LIMIT];
//
//	onewayD = 'D'; onewayU = 'U';	 onewayL = 'L'; onewayR = 'R';
//	twowayH = 'H'; twowayV = 'V';
//	twowayDR = 'Z';twowayUR = 'X'; twowayDL = 'C';twowayUL = 'B';
//	threewayD = '1'; threewayU = '2';threewayL = '3';threewayR = '4';
//	fourway = '5';
//	
//	roomoneD = 'd';roomoneU = 'u';roomoneL = 'l';roomoneR = 'r';
//	roomtwoH = 'h';roomtwoV = 'v';
//	roomtwoDR = 'z';roomtwoUR = 'x';roomtwoDL = 'c';roomtwoUL = 'b';
//	roomthreeD = '!';roomthreeU = '@';roomthreeL = '#';roomthreeR = '$';
//	roomfour = '%';
//	blank = ' ';
//}
//
//bool FloorGenerator::checkLeft(int posX, int posY)
//{
//	if(map[posX][posY] == onewayR ||
//		map[posX ][posY] == twowayH ||
//		map[posX ][posY] == twowayDR ||
//		map[posX ][posY] == twowayUR ||
//		map[posX ][posY ] == threewayD ||
//		map[posX ][posY] == threewayU ||
//		map[posX ][posY] == threewayR ||
//		map[posX ][posY ] == fourway ||
//		map[posX ][posY ] == roomoneR ||
//		map[posX ][posY ] == roomtwoH ||
//		map[posX ][posY ] == roomtwoUR ||
//		map[posX ][posY ] == roomtwoDR ||
//		map[posX ][posY] == roomthreeD ||
//		map[posX ][posY ] == roomthreeU ||
//		map[posX ][posY ] == roomthreeR ||
//		map[posX ][posY ] == roomfour ||
//		map[posX ][posY ] == ' '
//		)
//	{
//		return true;
//	}else
//		return false;
//}
//
//bool FloorGenerator::checkLeft2(int posX, int posY)
//{
//	if(map[posX][posY] == onewayR ||
//		map[posX ][posY] == twowayH ||
//		map[posX ][posY] == twowayDR ||
//		map[posX ][posY] == twowayUR ||
//		map[posX ][posY ] == threewayD ||
//		map[posX ][posY] == threewayU ||
//		map[posX ][posY] == threewayR ||
//		map[posX ][posY ] == fourway ||
//		map[posX ][posY ] == roomoneR ||
//		map[posX ][posY ] == roomtwoH ||
//		map[posX ][posY ] == roomtwoUR ||
//		map[posX ][posY ] == roomtwoDR ||
//		map[posX ][posY] == roomthreeD ||
//		map[posX ][posY ] == roomthreeU ||
//		map[posX ][posY ] == roomthreeR ||
//		map[posX ][posY ] == roomfour
//		)
//	{
//		return true;
//	}else
//		return false;
//
//}
//
//bool FloorGenerator::checkUp(int posX, int posY)
//{
//	
//	if(
//		map[posX ][posY] == onewayD ||
//		map[posX ][posY] == twowayV ||
//		map[posX ][posY ] == twowayDR ||
//		map[posX ][posY ] == twowayDL ||
//		map[posX ][posY ] == threewayD ||
//		map[posX ][posY ] == threewayL ||
//		map[posX ][posY ] == threewayR ||
//		map[posX ][posY ] == fourway ||
//		map[posX ][posY ] == roomoneD ||
//		map[posX ][posY ] == roomtwoV ||
//		map[posX ][posY ] == roomtwoDL ||
//		map[posX ][posY ] == roomtwoDR ||
//		map[posX ][posY ] == roomthreeD ||
//		map[posX ][posY ] == roomthreeL ||
//		map[posX ][posY ] == roomthreeR ||
//		map[posX ][posY ] == roomfour ||
//		map[posX ][posY ] == blank
//		)
//	{
//		return true;
//	}else
//		return false;
//
//
//
//}
//bool FloorGenerator::checkUp2(int posX, int posY)
//{
//	if(
//		map[posX ][posY] == onewayD ||
//		map[posX ][posY] == twowayV ||
//		map[posX ][posY ] == twowayDR ||
//		map[posX ][posY ] == twowayDL ||
//		map[posX ][posY ] == threewayD ||
//		map[posX ][posY ] == threewayL ||
//		map[posX ][posY ] == threewayR ||
//		map[posX ][posY ] == fourway ||
//		map[posX ][posY ] == roomoneD ||
//		map[posX ][posY ] == roomtwoV ||
//		map[posX ][posY ] == roomtwoDL ||
//		map[posX ][posY ] == roomtwoDR ||
//		map[posX ][posY ] == roomthreeD ||
//		map[posX ][posY ] == roomthreeL ||
//		map[posX ][posY ] == roomthreeR ||
//		map[posX ][posY ] == roomfour 
//		)
//	{
//		return true;
//	}else
//		return false;
//
//
//}
//
//bool FloorGenerator::checkRight(int posX, int posY)
//{
//	if(map[posX ][posY ] == onewayL ||
//		map[posX ][posY] == twowayH ||
//		map[posX ][posY] == twowayDL ||
//		map[posX ][posY ] == twowayUL ||
//		map[posX ][posY ] == threewayD ||
//		map[posX ][posY ] == threewayU ||
//		map[posX ][posY ] == threewayL ||
//		map[posX ][posY ] == fourway ||
//		map[posX ][posY ] == roomoneL ||
//		map[posX ][posY ] == roomtwoH ||
//		map[posX ][posY ] == roomtwoUL ||
//		map[posX ][posY ] == roomtwoDL ||
//		map[posX ][posY ] == roomthreeD ||
//		map[posX ][posY ] == roomthreeU ||
//		map[posX ][posY ] == roomthreeL ||
//		map[posX ][posY ] == roomfour ||
//		map[posX ][posY ] == blank
//		)
//	{
//		return true;
//	}else
//		return false;
//}
//bool FloorGenerator::checkRight2(int posX, int posY)
//{
//	if(map[posX ][posY ] == onewayL ||
//		map[posX ][posY] == twowayH ||
//		map[posX ][posY] == twowayDL ||
//		map[posX ][posY ] == twowayUL ||
//		map[posX ][posY ] == threewayD ||
//		map[posX ][posY ] == threewayU ||
//		map[posX ][posY ] == threewayL ||
//		map[posX ][posY ] == fourway ||
//		map[posX ][posY ] == roomoneL ||
//		map[posX ][posY ] == roomtwoH ||
//		map[posX ][posY ] == roomtwoUL ||
//		map[posX ][posY ] == roomtwoDL ||
//		map[posX ][posY ] == roomthreeD ||
//		map[posX ][posY ] == roomthreeU ||
//		map[posX ][posY ] == roomthreeL ||
//		map[posX ][posY ] == roomfour
//		)
//	{
//		return true;
//	}else
//		return false;
//}
//
//bool FloorGenerator::checkDown(int posX, int posY)
//{
//	if(
//		map[posX][posY] == onewayU ||
//		map[posX][posY] == twowayV ||
//		map[posX][posY] == twowayUR ||
//		map[posX][posY] == twowayUL ||
//		map[posX][posY] == threewayU ||
//		map[posX][posY] == threewayL ||
//		map[posX][posY] == threewayR ||
//		map[posX][posY] == fourway ||
//		map[posX][posY] == roomoneU ||
//		map[posX][posY] == roomtwoV ||
//		map[posX][posY] == roomtwoUR ||
//		map[posX][posY] == roomtwoUL ||
//		map[posX][posY] == threewayU ||
//		map[posX][posY] == threewayL ||
//		map[posX][posY] == threewayR ||
//		map[posX][posY] == roomfour ||
//		map[posX][posY] == ' '
//
//		)
//		return true;
//	else
//		return false;
//}
//bool FloorGenerator::checkDown2(int posX, int posY)
//{
//	if(
//		map[posX][posY] == onewayU ||
//		map[posX][posY] == twowayV ||
//		map[posX][posY] == twowayUR ||
//		map[posX][posY] == twowayUL ||
//		map[posX][posY] == threewayU ||
//		map[posX][posY] == threewayL ||
//		map[posX][posY] == threewayR ||
//		map[posX][posY] == fourway ||
//		map[posX][posY] == roomoneU ||
//		map[posX][posY] == roomtwoV ||
//		map[posX][posY] == roomtwoUR ||
//		map[posX][posY] == roomtwoUL ||
//		map[posX][posY] == threewayU ||
//		map[posX][posY] == threewayL ||
//		map[posX][posY] == threewayR ||
//		map[posX][posY] == roomfour 
//
//		)
//		return true;
//	else
//		return false;
//}
//
//void FloorGenerator::assignUpR(int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//
//	switch(temp)
//	{
//	case 0: 
//		//onewayD
//		{
//			if(posX -2 <= 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if(!checkUp2(posX-2, posY) &&
//				!checkLeft2(posX-1, posY-1) &&
//				!checkRight2(posX-1, posY+1)
//				)
//			{
//				map[posX - 1][posY] = onewayD; 								 
//			}
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 1: 
//		{
//			//twowayV
//			if((posX - 2) != 0)
//			{
//				if(checkUp(posX-2, posY) &&
//					!checkLeft2( posX-1, posY-1) &&
//					!checkRight2( posX-1, posY+1)
//					)
//				{
//					map[posX - 1][posY] = twowayV; 
//					nextRC(currentroom, posX, posY ); 
//					nextRC(twowayV, posX-1, posY);
//				}else
//					nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX - 2) <= 0)
//			{
//				nextRC(currentroom, posX, posY); 
//				break;
//			}
//			break;
//		}
//	case 2:
//		{
//			//threewayD
//
//			//cannot place this piece if the left or right areas are the edges
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			//check for existing left and right areas and see if they are compatible
//			if(
//				checkLeft(posX-1, posY-1)
//				//checkAvailable(map, posX - 1, posY - 1, tempholder)
//
//				&&
//				checkRight(posX-1, posY+1)
//				//checkAvailable(map, posX-1, posY+1, tempholder2)
//				&& 
//				!checkUp2(posX-2, posY)
//				)
//			{
//				map[posX - 1][posY] = threewayD;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayD, posX-1, posY);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//
//			break;
//		}
//	case 3:
//		//threewayL
//		{
//			//check the left and top to see if they are at the edge
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posX - 2) == 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			//check for existing left and top areas and see if they are compatible
//			if( 
//				checkLeft(posX-1, posY-1)
//				&&
//				checkUp(posX-2, posY)
//
//				&&
//				!checkRight2(posX-1, posY+1)
//
//				)
//			{
//				map[posX - 1][posY] = threewayL;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayL, posX-1, posY);
//				break;
//			}else
//				nextRC(roomfour, posX, posY);
//
//
//			break;
//		}
//	case 4:
//		//threewayR
//		{
//			//check the top and right areas if they are on the edge
//			if((posX - 2) == 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing top and right areas and see if they are compatible
//			if( checkUp( posX-2, posY)
//				&&
//				checkRight( posX-1, posY+1)
//				&&
//				!checkLeft2( posX-1, posY-1)
//				)
//			{
//				map[posX -1][posY] = threewayR;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayR, posX-1, posY);
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 5:
//		//fourway
//		{
//			//cannot place this piece if the left, right, or up areas are the edges
//			if((posY - 1) == 0) 
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//			if((posX - 2) == 0)
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			//check for existing left area and see if it is compatible
//			if(
//				checkLeft(posX-1, posY-1)
//				&&
//				checkRight(posX-1, posY+1)
//				&&
//				checkUp(posX-2, posY)								
//				)
//			{
//				map[posX - 1][posY] = fourway;
//				nextRC(currentroom, posX, posY);
//				nextRC(fourway, posX-1, posY);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 6:
//		//twowayDR
//		{
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			//check for existing right area and see if it is compatible
//			if(
//				!checkLeft2(posX-1, posY-1)
//				&&
//				checkRight(posX-1, posY+1)
//				&&
//				!checkUp2(posX-2, posY)	
//
//				)
//			{
//				map[posX - 1][posY] = twowayDR;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayDR, posX-1, posY);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//
//	case 7:
//		//twowayDL
//		{
//			if((posY - 1) == 0) 
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			//check for existing left area and see if it is compatible
//			if(
//				checkLeft( posX-1, posY-1)
//				&&
//				!checkRight2( posX-1, posY+1)
//				&&
//				!checkUp2( posX-2, posY)
//				)
//			{
//				map[posX - 1][posY] = twowayDL;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayDL, posX-1, posY);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	}
//
//
//}
//void FloorGenerator::assignUpC(int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//
//	int room = rand() % 2;
//
//	switch(temp)
//	{
//	case 0: 
//		//onewayD
//		{
//			if(posX -2 <= 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if(!checkUp2(posX-2, posY) &&
//				!checkLeft2( posX-1, posY-1) &&
//				!checkRight2(posX-1, posY+1)
//				)
//			{
//				if(room)
//					map[posX - 1][posY] = onewayD;
//				else
//					map[posX -1][posY] = roomoneD;
//			}
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 1: 
//		{
//			//twowayV
//			if((posX - 2) <= 0)
//			{
//				if(checkUp( posX-2, posY) &&
//					!checkLeft2( posX-1, posY-1) &&
//					!checkRight2( posX-1, posY+1)
//					)
//				{
//					if(room)
//					{
//						map[posX - 1][posY] = twowayV; 
//						nextRC(currentroom, posX, posY); 
//						nextRC(twowayV, posX-1, posY);
//					}else
//					{
//						map[posX - 1][posY] = roomtwoV; 
//						nextRC(currentroom, posX, posY); 
//						nextRC(roomtwoV, posX-1, posY);
//					}
//				}else
//					nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX - 2) <= 0)
//			{
//				nextRC(currentroom, posX, posY); 
//				break;
//			}
//			break;
//		}
//	case 2:
//		{
//			//threewayD
//
//			//cannot place this piece if the left or right areas are the edges
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			//check for existing left and right areas and see if they are compatible
//			if(
//				checkLeft( posX-1, posY-1)
//				//checkAvailable(floor, posX - 1, posY - 1, tempholder)
//
//				&&
//				checkRight( posX-1, posY+1)
//				//checkAvailable(floor, posX-1, posY+1, tempholder2)
//				&& 
//				!checkUp2( posX-2, posY)
//				)
//			{
//				if(room)
//				{
//					map[posX - 1][posY] = threewayD;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayD, posX-1, posY);
//				}else
//				{
//					map[posX - 1][posY] = roomthreeD;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeD, posX-1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//
//			break;
//		}
//	case 3:
//		//threewayL
//		{
//			//check the left and top to see if they are at the edge
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posX - 2) == 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			//check for existing left and top areas and see if they are compatible
//			if( 
//				checkLeft( posX-1, posY-1)
//				&&
//				checkUp(posX-2, posY)
//
//				&&
//				!checkRight2( posX-1, posY+1)
//
//				)
//			{
//				if(room)
//				{
//					map[posX - 1][posY] = threewayL;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayL, posX-1, posY);
//				}else
//				{
//					map[posX - 1][posY] = roomthreeL;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeL, posX-1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//	case 4:
//		//threewayR
//		{
//			//check the top and right areas if they are on the edge
//			if((posX - 2) == 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing top and right areas and see if they are compatible
//			if( checkUp( posX-2, posY)
//				&&
//				checkRight( posX-1, posY+1)
//				&&
//				!checkLeft2( posX-1, posY-1)
//				)
//			{
//				if(room)
//				{
//					map[posX -1][posY] = threewayR;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayR, posX-1, posY);
//				}else
//				{
//					map[posX -1][posY] = roomthreeR;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeR, posX-1, posY);
//				}
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 5:
//		//fourway
//		{
//			//cannot place this piece if the left, right, or up areas are the edges
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if((posX - 2) == 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing left area and see if it is compatible
//			if(
//				checkLeft( posX-1, posY-1)
//				&&
//				checkRight( posX-1, posY+1)
//				&&
//				checkUp( posX-2, posY)								
//				)
//			{
//				if(room)
//				{
//					map[posX - 1][posY] = fourway;
//					nextRC(currentroom, posX, posY);
//					nextRC(fourway, posX-1, posY);
//				}else
//				{
//					map[posX - 1][posY] = roomfour;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomfour, posX-1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 6:
//
//		//twowayDR
//		{
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			//check for existing right area and see if it is compatible
//			if(
//				!checkLeft2(posX-1, posY-1)
//				&&
//				checkRight( posX-1, posY+1)
//				&&
//				!checkUp2( posX-2, posY)	
//
//				)
//			{
//				if(room)
//				{
//					map[posX - 1][posY] = twowayDR;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayDR, posX-1, posY);
//				}else
//				{
//					map[posX - 1][posY] = twowayDR;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayDR, posX-1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//
//	case 7:
//		//twowayDL
//		{
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing left area and see if it is compatible
//			if(
//				checkLeft( posX-1, posY-1)
//				&&
//				!checkRight2( posX-1, posY+1)
//				&&
//				!checkUp2( posX-2, posY)
//				)
//			{
//				if(room)
//				{
//					map[posX - 1][posY] = twowayDL;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayDL, posX-1, posY);
//				}else
//				{
//					map[posX - 1][posY] = twowayDL;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayDL, posX-1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	}
//}
//
//
//void FloorGenerator::assignDownR(int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//	switch(temp)
//	{
//	case 0:
//		{
//			if(posX + 2 >= LIMIT -1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			//onewayU
//			if(!checkLeft2( posX+1, posY-1) &&
//				!checkRight2( posX+1, posY+1) &&
//				!checkDown2( posX+2, posY)
//				)
//			{
//				map[posX + 1][posY] = onewayU; 
//			}
//			nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 1:
//		//twowayV
//		{
//			if(posX + 2 >= LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY); 
//				break;
//			}
//			
//			if(checkDown( posX+2, posY) &&
//				!checkLeft2( posX+1, posY-1) &&
//				!checkRight2( posX+1, posY+1)
//				)
//			{
//				map[posX + 1][posY] = twowayV;
//				nextRC(currentroom, posX, posY); 
//				nextRC(twowayV, posX+1, posY);
//				}else
//					nextRC(currentroom, posX, posY);							 
//
//				break;
//			
//
//		
//			break;							
//
//		}
//
//	case 2:
//		//twowayUL
//		{
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing left area and see if it is compatible
//			if(
//				checkLeft( posX+1, posY-1) &&
//				!checkRight2( posX+1, posY+1) &&
//				!checkDown2( posX+2, posY)
//				)
//			{
//				map[posX + 1][posY] = twowayUL;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayUL, posX+1, posY);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//
//	case 3:
//		//twowayUR
//
//		{
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			//check for existing right area and see if it is compatible
//			if(
//				checkRight( posX+1, posY+1) &&
//				!checkLeft2( posX+1, posY-1) &&
//				!checkDown2( posX +2, posY)
//				)
//			{
//				map[posX + 1][posY] = twowayUR;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayUR, posX+1, posY);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 4:
//		//threewayU
//		if((posY - 1) == 0) 
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if((posY + 1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		//check left and right areas
//		if(checkLeft( posX+1, posY-1)
//			&&
//			checkRight( posX+1, posY+1) &&
//			!checkDown2( posX+2, posY)
//			){
//
//				map[posX + 1][posY] = threewayU;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayU, posX+1, posY);
//				break;
//		}else
//			nextRC(currentroom, posX, posY);
//
//		break;
//
//	case 5:
//		//threewayL
//		if((posY -1) == 0)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if((posX+1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if(checkLeft(posX+1, posY-1) &&
//			!checkRight2( posX+1, posY+1) &&
//			checkDown( posX+2, posY)
//			)
//		{
//			map[posX+1][posY] = threewayL;
//			nextRC(currentroom, posX, posY);
//			nextRC(threewayL, posX+1, posY);
//			break;
//		}else
//		{
//			nextRC(currentroom, posX, posY);
//		}
//
//		break;
//	case 6:
//		//threewayR
//
//		if((posY+1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if((posX +1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if(!checkLeft2( posX+1, posY-1) &&
//			checkRight( posX+1, posY+1) &&
//			checkDown( posX+2, posY)
//			)
//		{
//			map[posX+1][posY] = threewayR;
//			nextRC(currentroom, posX, posY);
//			nextRC(threewayR, posX+1, posY);
//			break;
//		}else
//		{
//			nextRC(currentroom, posX, posY);
//		}
//		break;
//	case 7:
//		//fourway
//		if( ((posY+1) == LIMIT-1) ||
//			((posY-1) == 0) ||
//			((posX+1) == LIMIT-1)
//			)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if(checkLeft( posX+1, posY-1) &&
//			checkRight( posX+1, posY+1) &&
//			checkDown( posX+2, posY)
//			)
//		{
//			map[posX+1][posY] = fourway;
//			nextRC(currentroom, posX, posY);
//			nextRC(fourway, posX+1, posY);
//			break;
//		}else
//		{
//			nextRC(currentroom, posX, posY);
//		}
//
//
//		break;
//
//
//	}//end switch
//
//}
//void FloorGenerator::assignDownC(int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//	int room = rand() % 2;
//	switch(temp)
//	{
//	case 0:
//		{
//			if(posX +2 >= LIMIT -1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			//onewayU
//			if(!checkLeft2(posX+1, posY-1) &&
//				!checkRight2(posX+1, posY+1) &&
//				!checkDown2(posX+2, posY)
//				)
//			{
//				if(room)
//					map[posX + 1][posY] = onewayU; 
//				else
//					map[posX + 1][posY] = roomoneU; 
//			}
//			nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 1:
//		//twowayV
//		{
//			
//			if(posX + 2 >= LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY); 
//				break;
//			}
//				if(checkDown(posX+2, posY) &&
//					!checkLeft2(posX+1, posY-1) &&
//					!checkRight2( posX+1, posY+1)
//					)
//				{
//					if(room)
//					{
//						map[posX + 1][posY] = twowayV;
//						nextRC(currentroom, posX, posY); 
//						nextRC(twowayV, posX+1, posY);
//					}else
//					{
//						map[posX + 1][posY] = roomtwoV;
//						nextRC(currentroom, posX, posY); 
//						nextRC(roomtwoV, posX+1, posY);
//					}
//				}else
//					nextRC(currentroom, posX, posY);							 
//
//				break;
//			
//
//			break;							
//
//		}
//
//	case 2:
//		//twowayUL
//		{
//			if((posY - 1) == 0) 
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing left area and see if it is compatible
//			if(
//				checkLeft(posX+1, posY-1) &&
//				!checkRight2(posX+1, posY+1) &&
//				!checkDown2( posX+2, posY)
//				)
//			{
//				if(room)
//				{
//					map[posX + 1][posY] = twowayUL;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayUL, posX+1, posY);
//				}else
//				{
//					map[posX + 1][posY] = roomtwoUL;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoUL, posX+1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//
//	case 3:
//		//twowayUR
//
//		{
//			if((posY + 1) == LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			//check for existing right area and see if it is compatible
//			if(
//				checkRight( posX+1, posY+1) &&
//				!checkLeft2( posX+1, posY-1) &&
//				!checkDown2( posX +2, posY)
//				)
//			{
//				if(room)
//				{
//					map[posX + 1][posY] = twowayUR;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayUR, posX+1, posY);
//				}else
//				{
//					map[posX + 1][posY] = roomtwoUR;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoUR, posX+1, posY);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 4:
//		//threewayU
//		if((posY - 1) == 0) 
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if((posY + 1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		//check left and right areas
//		if(checkLeft( posX+1, posY-1)
//			&&
//			checkRight( posX+1, posY+1) &&
//			!checkDown2( posX+2, posY)
//			){
//				if(room)
//				{
//					map[posX + 1][posY] = threewayU;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayU, posX+1, posY);
//				}else
//				{
//					map[posX + 1][posY] = roomthreeU;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeU, posX+1, posY);
//				}
//				break;
//		}else
//			nextRC(currentroom, posX, posY);
//
//		break;
//
//	case 5:
//		//threewayL
//		if((posY -1) == 0)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if((posX+1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if(checkLeft(posX+1, posY-1) &&
//			!checkRight2( posX+1, posY+1) &&
//			checkDown( posX+2, posY)
//			)
//		{
//			if(room)
//			{
//				map[posX+1][posY] = threewayL;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayL, posX+1, posY);
//			}else
//			{
//				map[posX+1][posY] = roomthreeL;
//				nextRC(currentroom, posX, posY);
//				nextRC(roomthreeL, posX+1, posY);
//			}
//			break;
//		}else
//		{
//			nextRC(currentroom, posX, posY);
//		}
//
//		break;
//	case 6:
//		//threewayR
//
//		if((posY+1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if((posX +1) == LIMIT-1)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if(!checkLeft2( posX+1, posY-1) &&
//			checkRight(posX+1, posY+1) &&
//			checkDown( posX+2, posY)
//			)
//		{
//			if(room)
//			{
//				map[posX+1][posY] = threewayR;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayR, posX+1, posY);
//			}else
//			{
//				map[posX+1][posY] = roomthreeR;
//				nextRC(currentroom, posX, posY);
//				nextRC(roomthreeR, posX+1, posY);
//			}
//			break;
//		}else
//		{
//			nextRC(currentroom, posX, posY);
//		}
//		break;
//	case 7:
//		//fourway
//		if( ((posY+1) == LIMIT-1) ||
//			((posY-1) == 0) ||
//			((posX+1) == LIMIT-1)
//			)
//		{
//			nextRC(currentroom, posX, posY);
//			break;
//		}
//
//		if(checkLeft( posX+1, posY-1) &&
//			checkRight( posX+1, posY+1) &&
//			checkDown( posX+2, posY)
//			)
//		{
//			if(room)
//			{
//				map[posX+1][posY] = fourway;
//				nextRC(currentroom, posX, posY);
//				nextRC(fourway, posX+1, posY);
//			}else
//			{
//				map[posX+1][posY] = roomfour;
//				nextRC(currentroom, posX, posY);
//				nextRC(roomfour, posX+1, posY);
//			}
//			break;
//		}else
//		{
//			nextRC(currentroom, posX, posY);
//		}
//
//
//		break;
//
//
//	}//end switch
//}
//
//void FloorGenerator::assignLeftR(int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//
//	switch(temp)
//	{
//	case 0:
//		//onewayR
//		{
//			if(posY-2 <= 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if( !checkUp2(posX-1, posY-1) &&
//				!checkDown2( posX+1, posY-1) &&
//				!checkLeft2( posX, posY-2))
//			{
//				map[posX][posY-1] = onewayR;
//			}
//			nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 1:
//		//twowayH
//		{
//			if( (posY-2) <= 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2( posX-1, posY-1) &&
//				!checkDown2( posX+1, posY-1) &&
//				checkLeft( posX, posY-2))
//			{
//				map[posX][posY-1] = twowayH;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayH, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 2:
//		//twowayUR
//		{
//			if( (posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY-1) &&
//				!checkDown2( posX+1, posY-1) &&
//				!checkLeft2( posX, posY-2))
//
//			{
//				map[posX][posY-1] = twowayUR;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayUR, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//
//	case 3:
//		//twowayDR
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			if( !checkUp2( posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				!checkLeft2(posX, posY-2))
//
//			{
//				map[posX][posY-1] = twowayDR;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayDR, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//		}
//		break;
//	case 4:
//		//threewayU
//		{
//			if( (posX-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(( posY-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(checkUp( posX-1, posY-1) &&
//				!checkDown2(posX+1, posY-1) &&
//				checkLeft(posX, posY-2))
//
//			{
//				map[posX][posY-1] = threewayU;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayU, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//	case 5:
//		//threewayD
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posY-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(!checkUp2( posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				checkLeft( posX, posY-2))
//
//			{
//				map[posX][posY-1] = threewayD;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayD, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 6:
//		//threewayR
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(checkUp( posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				!checkLeft2(posX, posY-2))
//
//			{
//				map[posX][posY-1] = threewayR;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayR, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//		}
//		break;
//	case 7:
//		//fourway
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( (posY-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(checkUp( posX-1, posY-1) &&
//				checkDown(posX+1, posY-1) &&
//				checkLeft(posX, posY-2))
//
//			{
//				map[posX][posY-1] = fourway;
//				nextRC(currentroom, posX, posY);
//				nextRC(fourway, posX, posY-1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//
//	}//end switch
//
//}
//void FloorGenerator::assignLeftC(int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//	int room = rand() % 2;
//	switch(temp)
//	{
//	case 0:
//		//onewayR
//		{
//			if(posY-2 <= 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//			if( !checkUp2(posX-1, posY-1) &&
//				!checkDown2(posX+1, posY-1) &&
//				!checkLeft2( posX, posY-2))
//			{
//				if(room)
//					map[posX][posY-1] = onewayR;
//				else
//					map[posX][posY-1] = roomoneR;
//			}
//			nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 1:
//		//twowayH
//		{
//			if( (posY-2) <= 0)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2(posX-1, posY-1) &&
//				!checkDown2(posX+1, posY-1) &&
//				checkLeft( posX, posY-2))
//			{
//				if(room)
//				{
//					map[posX][posY-1] = twowayH;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayH, posX, posY-1);
//				}else
//				{
//					map[posX][posY-1] = roomtwoH;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoH, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 2:
//		//twowayUR
//		{
//			if( (posX-1 <= 0))
//			{
//				nextRC(roomfour, posX, posY);
//				break;
//			}
//
//			if( checkUp(posX-1, posY-1) &&
//				!checkDown2( posX+1, posY-1) &&
//				!checkLeft2( posX, posY-2))
//
//			{
//				if(room)
//				{
//					map[posX][posY-1] = twowayUR;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayUR, posX, posY-1);
//				}
//				else
//				{
//					map[posX][posY-1] = roomtwoUR;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoUR, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//
//	case 3:
//		//twowayDR
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2(posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				!checkLeft2( posX, posY-2))
//
//			{
//				if(room)
//				{
//					map[posX][posY-1] = twowayDR;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayDR, posX, posY-1);
//				}else
//				{
//					map[posX][posY-1] = roomtwoDR;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoDR, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//
//	case 4:
//		//threewayU
//		{
//			if( (posX-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(( posY-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(checkUp( posX-1, posY-1) &&
//				!checkDown2( posX+1, posY-1) &&
//				checkLeft( posX, posY-2))
//
//			{
//				if(room)
//				{
//					map[posX][posY-1] = threewayU;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayU, posX, posY-1);
//				}else
//				{
//					map[posX][posY-1] = roomthreeU;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeU, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//	case 5:
//		//threewayD
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posY-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(!checkUp2( posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				checkLeft( posX, posY-2))
//
//			{
//				if(room)
//				{
//					map[posX][posY-1] = threewayD;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayD, posX, posY-1);
//				}else
//				{
//					map[posX][posY-1] = roomthreeD;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeD, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 6:
//		//threewayR
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(checkUp( posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				!checkLeft2( posX, posY-2))
//
//			{
//				if(room)
//				{
//					map[posX][posY-1] = threewayR;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayR, posX, posY-1);
//				}else
//				{
//					map[posX][posY-1] = roomthreeR;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeR, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//		}
//		break;
//	case 7:
//		//fourway
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( (posY-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(checkUp( posX-1, posY-1) &&
//				checkDown( posX+1, posY-1) &&
//				checkLeft( posX, posY-2))
//
//			{
//				if(room)
//				{
//					map[posX][posY-1] = fourway;
//					nextRC(currentroom, posX, posY);
//					nextRC(fourway, posX, posY-1);
//				}else
//				{
//					map[posX][posY-1] = roomfour;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomfour, posX, posY-1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//
//	}//end switch
//}
//
//void FloorGenerator::assignRightR( int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//
//	switch(temp)
//	{
//	case 0:
//		//onewayR
//		{
//			if(posY+1 >= LIMIT-1)
//			{
//				break;
//			}
//			if( !checkUp2(posX-1, posY+1) &&
//				!checkDown2(posX+1, posY+1) &&
//				!checkRight2(posX, posY+2))
//			{
//				map[posX][posY+1] = onewayR;
//			}
//			nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 1:
//		//twowayH
//		{
//			if( (posY+2) >= LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2(posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				checkRight( posX, posY+2))
//			{
//				map[posX][posY+1] = twowayH;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayH, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 2:
//		//twowayUL
//		{
//			if( (posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			if( checkUp(posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				!checkRight2( posX, posY+2))
//			{
//				map[posX][posY+1] = twowayUL;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayUL, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//
//	case 3:
//		//twowayDL
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			if( !checkUp2( posX-1, posY+1) &&
//				checkDown( posX+1, posY+1) &&
//				!checkRight2( posX, posY+2))
//			{
//				map[posX][posY+1] = twowayDL;
//				nextRC(currentroom, posX, posY);
//				nextRC(twowayDL, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//		}
//		break;
//	case 4:
//		//threewayU
//		{
//			if( (posX-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(( posY+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				checkRight( posX, posY+2))
//			{
//				map[posX][posY+1] = threewayU;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayU, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//	case 5:
//		//threewayD
//		{
//			if( (posX+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(( posY+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2( posX-1, posY+1) &&
//				checkDown2( posX+1, posY+1) &&
//				checkRight( posX, posY+2))
//			{
//				map[posX][posY+1] = threewayD;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayD, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 6:
//		//threewayL
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY+1) &&
//				checkDown( posX+1, posY+1) &&
//				!checkRight2( posX, posY+2))
//			{
//				map[posX][posY+1] = threewayL;
//				nextRC(currentroom, posX, posY);
//				nextRC(threewayL, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//		}
//		break;
//	case 7:
//		//fourway
//		{
//			if( (posX + 1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( (posY+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY+1) &&
//				checkDown( posX+1, posY+1) &&
//				checkRight(posX, posY+2))
//			{
//				map[posX][posY+1] = fourway;
//				nextRC(currentroom, posX, posY);
//				nextRC(fourway, posX, posY+1);
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//
//	}//end switch
//
//
//
//}
//void FloorGenerator::assignRightC( int posX, int posY, char currentroom)
//{
//	int temp = rand() % 8;
//	int room = rand() % 2;
//
//	switch(temp)
//	{
//	case 0:
//		//onewayR
//		{
//			if(posY+1 >= LIMIT-1)
//			{
//				break;
//			}
//			if( !checkUp2( posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				!checkRight2(posX, posY+2))
//			{
//				if(room)
//					map[posX][posY+1] = onewayR;
//				else
//					map[posX][posY+1] = roomoneR;
//			}
//			nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 1:
//		//twowayH
//		{
//			if( (posY+2) >= LIMIT-1)
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2( posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				checkRight(posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = twowayH;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayH, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = twowayH;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayH, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//	case 2:
//		//twowayUL
//		{
//			if( (posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			if( checkUp(posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				!checkRight2( posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = twowayUL;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayUL, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = roomtwoUL;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoUL, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//			break;
//		}
//
//	case 3:
//		//twowayDL
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//
//			if( !checkUp2( posX-1, posY+1) &&
//				checkDown( posX+1, posY+1) &&
//				!checkRight2( posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = twowayDL;
//					nextRC(currentroom, posX, posY);
//					nextRC(twowayDL, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = roomtwoDL;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomtwoDL, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//		}
//		break;
//	case 4:
//		//threewayU
//		{
//			if( (posX-1 <= 0) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(( posY+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY+1) &&
//				!checkDown2( posX+1, posY+1) &&
//				checkRight( posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = threewayU;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayU, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = roomthreeU;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeU, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//	case 5:
//		//threewayD
//		{
//			if( (posX+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if(( posY+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( !checkUp2( posX-1, posY+1) &&
//				checkDown2( posX+1, posY+1) &&
//				checkRight( posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = threewayD;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayD, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = roomthreeD;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeD, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//			break;
//		}
//	case 6:
//		//threewayL
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY+1) &&
//				checkDown( posX+1, posY+1) &&
//				!checkRight2( posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = threewayL;
//					nextRC(currentroom, posX, posY);
//					nextRC(threewayL, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = roomthreeL;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomthreeL, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//		}
//		break;
//	case 7:
//		//fourway
//		{
//			if( (posX+1 >= LIMIT-1))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if((posX-1 <= 0))
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( (posY+1 >= LIMIT-1) )
//			{
//				nextRC(currentroom, posX, posY);
//				break;
//			}
//
//			if( checkUp( posX-1, posY+1) &&
//				checkDown( posX+1, posY+1) &&
//				checkRight( posX, posY+2))
//			{
//				if(room)
//				{
//					map[posX][posY+1] = fourway;
//					nextRC(currentroom, posX, posY);
//					nextRC(fourway, posX, posY+1);
//				}else
//				{
//					map[posX][posY+1] = roomfour;
//					nextRC(currentroom, posX, posY);
//					nextRC(roomfour, posX, posY+1);
//				}
//				break;
//			}else
//				nextRC(currentroom, posX, posY);
//
//
//			break;
//		}
//
//	}//end switch
//
//
//}
//void FloorGenerator::nextRC(const char cor_room, int posX, int posY)
//{
//	switch(cor_room)
//	{
//	case onewayD:
//		//check position below for availability
//		if(posX != LIMIT-1)
//		{
//			if(map[posX + 1][posY] == ' ')
//			{
//				assignDownC( posX, posY, onewayD);
//
//
//
//			}//end checking for available
//
//		}//end checking down
//		break;
//	case onewayU:
//		
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, onewayU);
//				}
//
//			}//end checking up
//
//		break;
//	case onewayL:
//		{
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, onewayL);
//				}
//			}
//		break;
//		}
//	case onewayR:
//		{
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, onewayR);
//			}
//		break;
//		}
//	case twowayH:
//		{
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, twowayH);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, twowayH);
//			}
//		break;
//		}
//	case twowayV:
//		{
//			
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, twowayV);
//				}
//
//			}//end checking up
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, twowayV);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//		break;
//		}
//	case twowayDL:
//		{
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, twowayDL);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, twowayDL);
//				}
//			}
//		break;
//		}
//	case twowayDR:
//		{
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, twowayDR);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//			
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, twowayDR);
//			}
//		break;
//		}
//	case twowayUL:
//			{
//			
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, twowayUL);
//				}
//
//			}//end checking up
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, twowayUL);
//				}
//			}
//		break;
//		}
//	case twowayUR:
//		{
//			
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, twowayUR);
//				}
//
//			}//end checking up
//			
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, twowayUR);
//			}
//		break;
//		}
//	case threewayD:
//
//		{
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, threewayD);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, threewayD);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, threewayD);
//			}
//			break;
//		}
//	case threewayU:
//	{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, threewayU);
//				}
//
//			}//end checking up
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, threewayU);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, threewayU);
//			}
//			break;
//		}
//	case threewayL:
//{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, threewayL);
//				}
//
//			}//end checking up
//
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, threewayL);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, threewayL);
//				}
//			}
//			break;
//		}
//	case threewayR:
//		{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, threewayR);
//				}
//
//			}//end checking up
//
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, threewayR);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, threewayR);
//			}
//			break;
//		}
//	case fourway:
//		{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpC( posX, posY, fourway);
//				}
//
//			}//end checking up
//
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownC( posX, posY, fourway);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftC( posX, posY, fourway);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightC( posX, posY, fourway);
//			}
//
//			break;
//		}
//
//	case roomoneD:
//		//check position below for availability
//		if(posX != LIMIT-1)
//		{
//			if(map[posX + 1][posY] == ' ')
//			{
//				assignDownR( posX, posY, roomoneD);
//
//
//
//			}//end checking for available
//
//		}//end checking down
//		break;
//	case roomoneU:
//		
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomoneU);
//				}
//
//			}//end checking up
//		break;
//	case roomoneL:
//		{
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomoneL);
//				}
//			}
//		break;
//		}
//	case roomoneR:
//		{
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomoneR);
//			}
//		break;
//		}
//	case roomtwoH:
//		{
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomtwoH);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomtwoH);
//			}
//		break;
//		}
//	case roomtwoV:
//		{
//			
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomtwoV);
//				}
//
//			}//end checking up
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomtwoV);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//		break;
//		}
//
//	case roomtwoDR:
//		{
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomtwoDR);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//			
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomtwoDR);
//			}
//		break;
//		}
//	case roomtwoDL:
//
//		{
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomtwoDL);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomtwoDL);
//				}
//			}
//		break;
//		}
//	case roomtwoUR:
//		{
//			
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomtwoUR);
//				}
//
//			}//end checking up
//			
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomtwoUR);
//			}
//		break;
//		}
//	case roomtwoUL:
//		{
//			
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomtwoUL);
//				}
//
//			}//end checking up
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomtwoUL);
//				}
//			}
//		break;
//		}
//	case roomthreeD:
//		{
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomthreeD);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomthreeD);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomthreeD);
//			}
//			break;
//		}
//	case roomthreeU:
//		{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomthreeU);
//				}
//
//			}//end checking up
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomthreeU);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomthreeU);
//			}
//			break;
//		}
//	case roomthreeL:
//		{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomthreeL);
//				}
//
//			}//end checking up
//
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomthreeL);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomthreeL);
//				}
//			}
//			break;
//		}
//	case roomthreeR:
//		{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomthreeR);
//				}
//
//			}//end checking up
//
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomthreeR);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomthreeR);
//			}
//			break;
//		}
//
//	case roomfour:
//		{
//			//check the position above for availability
//			if(posX != 0)
//			{
//				if(map[posX -1][posY] == ' ')
//				{
//					assignUpR( posX, posY, roomfour);
//				}
//
//			}//end checking up
//
//			//check position below for availability
//			if(posX != LIMIT-1)
//			{
//				if(map[posX + 1][posY] == ' ')
//				{
//					assignDownR( posX, posY, roomfour);
//
//
//
//				}//end checking for available
//
//			}//end checking down
//
//			//check position left for availability
//			if(posY != 0)
//			{
//				if(map[posX][posY-1] == ' ')
//				{
//					assignLeftR( posX, posY, roomfour);
//				}
//			}
//
//			//check right position for availability
//			if(posY != LIMIT-1)
//			{
//				if(map[posX][posY+1] == ' ')
//					assignRightR( posX, posY, roomfour);
//			}
//
//			break;
//		}//end case roomfour
//	}//end switch
//}
//
//void FloorGenerator::generateMap()
//{
//	int x = rand() %LIMIT;
//	int y = rand() %LIMIT;
//
//	int startroom = rand()% 11 + 1;
//
//	if( y == 0 )
//	{
//		startroom = rand()%7;
//		switch(startroom)
//		{
//		case 0:	startroom = ROOMONEDOWN;		break;
//		case 1: startroom = ROOMONEUP; break;
//		case 2: startroom = ROOMONERIGHT; break;
//		case 3: startroom = ROOMTWOV; break;
//		case 4: startroom = ROOMTHREERIGHT; break;
//		case 5: startroom = ROOMTWODR; break;
//		case 6: startroom = ROOMTWOUR; break;
//		}
//
//	}
//
//	if( y == LIMIT-1 )
//	{
//		startroom = rand()%7;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONEDOWN; break;
//		case 1: startroom = ROOMONEUP; break;
//		case 2: startroom = ROOMONELEFT; break;
//		case 3: startroom = ROOMTWOV; break;
//		case 4: startroom = ROOMTHREELEFT; break;
//		case 5: startroom = ROOMTWODL; break;
//		case 6: startroom = ROOMTWOUL; break;
//		}
//
//	}
//
//	if( x == 0 )
//	{
//		startroom = rand() % 7;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONEDOWN; break;
//		case 1: startroom = ROOMONELEFT; break;
//		case 2: startroom = ROOMONERIGHT; break;
//		case 3: startroom = ROOMTWOH; break;
//		case 4: startroom = ROOMTHREEDOWN; break;
//		case 5: startroom = ROOMTWODR; break;
//		case 6: startroom = ROOMTWODL; break;
//		}
//	}
//
//	if( x == LIMIT-1)
//	{
//		startroom = rand() % 7;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONEUP; break;
//		case 1: startroom = ROOMONELEFT; break;
//		case 2: startroom = ROOMONERIGHT; break;
//		case 3: startroom = ROOMTWOH; break;
//		case 4: startroom = ROOMTHREEUP; break;
//		case 5: startroom = ROOMTWOUR; break;
//		case 6: startroom = ROOMTWOUL; break;
//		}
//	}
//
//	if( x == 0 && y == 0)
//	{
//		startroom = rand() % 3;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONERIGHT; break;
//		case 1: startroom = ROOMONEDOWN; break;
//		case 2: startroom = ROOMTWODR; break;
//		}
//	}
//
//	if(x == 0 && y == LIMIT-1)
//	{
//		startroom = rand() % 3;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONELEFT; break;
//		case 1: startroom = ROOMONEDOWN; break;
//		case 2: startroom = ROOMTWODL; break;
//		}
//	}
//
//
//	if(x == LIMIT-1 && y == 0)
//	{
//		startroom = rand() % 3;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONERIGHT; break;
//		case 1: startroom = ROOMONEUP; break;
//		case 2: startroom = ROOMTWOUR; break;
//		}
//	}
//
//	if(x == LIMIT-1 && y == LIMIT-1)
//	{
//		startroom = rand() % 3;
//		switch(startroom)
//		{
//		case 0: startroom = ROOMONELEFT; break;
//		case 1: startroom = ROOMONEUP; break;
//		case 2: startroom = ROOMTWOUL; break;
//		}
//	}
//	
//
//	switch(startroom)
//	{
//	case ROOMONEDOWN:
//		map[x][y] = roomoneD;
//		nextRC(roomoneD, x, y);
//		break;
//	case ROOMONEUP:
//		map[x][y] = roomoneU;
//		nextRC(roomoneU, x, y);
//		break;
//	case ROOMONELEFT:
//		map[x][y] = roomoneL;
//		nextRC(roomoneL, x, y);
//		break;
//	case ROOMONERIGHT:
//		map[x][y] = roomoneR;
//		nextRC(roomoneR, x, y);
//		break;
//	case ROOMTWOH:
//		map[x][y] = roomtwoH;
//		nextRC(roomtwoH, x, y);
//		break;
//	case ROOMTWOV:
//		map[x][y] = roomtwoV;
//		nextRC(roomtwoV, x, y);
//		break;
//	case ROOMTHREEDOWN:
//		map[x][y] = roomthreeD;
//		nextRC(roomthreeD, x, y);
//		break;
//	case ROOMTHREEUP:
//		map[x][y] = roomthreeU;
//		nextRC(roomthreeU, x, y);
//		break;
//	case ROOMTHREELEFT:
//		map[x][y] = roomthreeL;
//		nextRC(roomthreeL, x, y);
//		break;
//	case ROOMTHREERIGHT:
//		map[x][y] = roomthreeR;
//		nextRC(roomthreeR, x, y);
//		break;
//	case ROOMFOUR:
//		map[x][y] = roomfour;
//		nextRC(roomfour, x, y);
//		break;
//	case ROOMTWODL:
//		map[x][y] = roomtwoDL;
//		nextRC(roomtwoDL, x, y);
//		break;
//	case ROOMTWODR:
//		map[x][y] = roomtwoDR;
//		nextRC(roomtwoDR, x, y);
//		break;
//	case ROOMTWOUL:
//		map[x][y] = roomtwoUL;
//		nextRC(roomtwoUL, x, y);
//		break;
//	case ROOMTWOUR:
//		map[x][y] = roomtwoUR;
//		nextRC(roomtwoUR, x, y);
//		break;
//	}
//}
//
//void FloorGenerator::resetMap()
//{
//	for(int i = 0; i < LIMIT; i++)
//	{
//		for(int j = 0; j < LIMIT; j++)
//		{
//			map[i][j] = ' ';
//		}
//	}
//}
//
//char** FloorGenerator::getMap()
//{
//	return map;
//}
//
//void FloorGenerator::shutdown()
//{
//	for(int i = 0; i < LIMIT; i++)
//		delete map[i];
//
//	delete [] map;
//}