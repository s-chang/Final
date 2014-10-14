#include "FloorGenerator.h"
#include <iostream>

FloorGenerator::FloorGenerator()
{
	map = 0;
}

FloorGenerator::FloorGenerator(const FloorGenerator &floor)
{
	resetMap();
	for(int i = 0; i < LIMIT; i++)
	{
		for(int j = 0; j < LIMIT; j++)
		{
			map[i][j] = floor.map[i][j];
		}
	}
	room_num = floor.room_num;
	add_room = floor.add_room;
}

FloorGenerator::~FloorGenerator()
{}

FloorGenerator *FloorGenerator::instance()
{
	static FloorGenerator generator;
	return &generator;
}

void FloorGenerator::resetMap()
{
	shutdown();

	map = new unsigned char* [LIMIT];

	for(int i = 0; i < LIMIT; i++)
		map[i] = new unsigned char[LIMIT];

	for(int i = 0; i < LIMIT; i++)
	{
		for(int j = 0; j < LIMIT; j++)
			map[i][j] = ' ';
	}

	emptyCor();
	emptyRoom();
	emptyQueue();
}

void FloorGenerator::shutdown()
{
	if(map)
	{
		for(int i = 0; i < LIMIT; i++)
		{
			delete map[i];
		}

		delete [] map;
	}
}

std::vector<Corridor> FloorGenerator::getCorridor()
{
	return corridor;
}

std::vector<Room> FloorGenerator::getRoom()
{
	return rooms;
}

bool FloorGenerator::checkUp(int posX, int posY)
{	
	if( map[posX][posY] == oneD ||
		map[posX ][posY] == twoV ||
		map[posX ][posY ] == twoDR ||
		map[posX ][posY ] == twoDL ||
		map[posX ][posY ] == threeD ||
		map[posX ][posY ] == threeL ||
		map[posX ][posY ] == threeR ||
		map[posX ][posY ] == four ||
		map[posX ][posY ] == roomoneD ||
		map[posX ][posY ] == roomtwoV ||
		map[posX ][posY ] == roomtwoDL ||
		map[posX ][posY ] == roomtwoDR ||
		map[posX ][posY ] == roomthreeD ||
		map[posX ][posY ] == roomthreeL ||
		map[posX ][posY ] == roomthreeR ||
		map[posX ][posY ] == roomfour ||
		map[posX ][posY ] == blank
		)		
		return true;
	else 
		return false;
}

bool FloorGenerator::checkDown(int posX, int posY)
{
	if(
		map[posX][posY] == oneU ||
		map[posX][posY] == twoV ||
		map[posX][posY] == twoUR ||
		map[posX][posY] == twoUL ||
		map[posX][posY] == threeU ||
		map[posX][posY] == threeL ||
		map[posX][posY] == threeR ||
		map[posX][posY] == four ||
		map[posX][posY] == roomoneU ||
		map[posX][posY] == roomtwoV ||
		map[posX][posY] == roomtwoUR ||
		map[posX][posY] == roomtwoUL ||
		map[posX][posY] == roomthreeU ||
		map[posX][posY] == roomthreeL ||
		map[posX][posY] == roomthreeR ||
		map[posX][posY] == roomfour ||
		map[posX][posY] == ' '

		)
		return true;
	else
		return false;
}

bool FloorGenerator::checkLeft(int posX, int posY)
{
	if(map[posX][posY] == oneR ||
		map[posX ][posY] == twoH ||
		map[posX ][posY] == twoDR ||
		map[posX ][posY] == twoUR ||
		map[posX ][posY ] == threeD ||
		map[posX ][posY] == threeU ||
		map[posX ][posY] == threeR ||
		map[posX ][posY ] == four ||
		map[posX ][posY ] == roomoneR ||
		map[posX ][posY ] == roomtwoH ||
		map[posX ][posY ] == roomtwoUR ||
		map[posX ][posY ] == roomtwoDR ||
		map[posX ][posY] == roomthreeD ||
		map[posX ][posY ] == roomthreeU ||
		map[posX ][posY ] == roomthreeR ||
		map[posX ][posY ] == roomfour ||
		map[posX ][posY ] == ' '
		)
	{
		return true;
	}else
		return false;
}

bool FloorGenerator::checkRight(int posX, int posY)
{
	if(map[posX ][posY ] == oneL ||
		map[posX ][posY] == twoH ||
		map[posX ][posY] == twoDL ||
		map[posX ][posY ] == twoUL ||
		map[posX ][posY ] == threeD ||
		map[posX ][posY ] == threeU ||
		map[posX ][posY ] == threeL ||
		map[posX ][posY ] == four ||
		map[posX ][posY ] == roomoneL ||
		map[posX ][posY ] == roomtwoH ||
		map[posX ][posY ] == roomtwoUL ||
		map[posX ][posY ] == roomtwoDL ||
		map[posX ][posY ] == roomthreeD ||
		map[posX ][posY ] == roomthreeU ||
		map[posX ][posY ] == roomthreeL ||
		map[posX ][posY ] == roomfour ||
		map[posX ][posY ] == blank
		)
	{
		return true;
	}else
		return false;
}

bool FloorGenerator::checkUp2(int posX, int posY)
{
	if( map[posX][posY] == oneD ||
		map[posX ][posY] == twoV ||
		map[posX ][posY ] == twoDR ||
		map[posX ][posY ] == twoDL ||
		map[posX ][posY ] == threeD ||
		map[posX ][posY ] == threeL ||
		map[posX ][posY ] == threeR ||
		map[posX ][posY ] == four ||
		map[posX ][posY ] == roomoneD ||
		map[posX ][posY ] == roomtwoV ||
		map[posX ][posY ] == roomtwoDL ||
		map[posX ][posY ] == roomtwoDR ||
		map[posX ][posY ] == roomthreeD ||
		map[posX ][posY ] == roomthreeL ||
		map[posX ][posY ] == roomthreeR ||
		map[posX ][posY ] == roomfour 
		)		
		return true;
	else 
		return false;
}

bool FloorGenerator::checkDown2(int posX, int posY)
{
	if(
		map[posX][posY] == oneU ||
		map[posX][posY] == twoV ||
		map[posX][posY] == twoUR ||
		map[posX][posY] == twoUL ||
		map[posX][posY] == threeU ||
		map[posX][posY] == threeL ||
		map[posX][posY] == threeR ||
		map[posX][posY] == four ||
		map[posX][posY] == roomoneU ||
		map[posX][posY] == roomtwoV ||
		map[posX][posY] == roomtwoUR ||
		map[posX][posY] == roomtwoUL ||
		map[posX][posY] == roomthreeU ||
		map[posX][posY] == roomthreeL ||
		map[posX][posY] == roomthreeR ||
		map[posX][posY] == roomfour 

		)
		return true;
	else
		return false;
}

bool FloorGenerator::checkLeft2(int posX, int posY)
{
	if(map[posX][posY] == oneR ||
		map[posX ][posY] == twoH ||
		map[posX ][posY] == twoDR ||
		map[posX ][posY] == twoUR ||
		map[posX ][posY ] == threeD ||
		map[posX ][posY] == threeU ||
		map[posX ][posY] == threeR ||
		map[posX ][posY ] == four ||
		map[posX ][posY ] == roomoneR ||
		map[posX ][posY ] == roomtwoH ||
		map[posX ][posY ] == roomtwoUR ||
		map[posX ][posY ] == roomtwoDR ||
		map[posX ][posY] == roomthreeD ||
		map[posX ][posY ] == roomthreeU ||
		map[posX ][posY ] == roomthreeR ||
		map[posX ][posY ] == roomfour
		)
	{
		return true;
	}else
		return false;
}

bool FloorGenerator::checkRight2(int posX, int posY)
{
	if(map[posX ][posY ] == oneL ||
		map[posX ][posY] == twoH ||
		map[posX ][posY] == twoDL ||
		map[posX ][posY ] == twoUL ||
		map[posX ][posY ] == threeD ||
		map[posX ][posY ] == threeU ||
		map[posX ][posY ] == threeL ||
		map[posX ][posY ] == four ||
		map[posX ][posY ] == roomoneL ||
		map[posX ][posY ] == roomtwoH ||
		map[posX ][posY ] == roomtwoUL ||
		map[posX ][posY ] == roomtwoDL ||
		map[posX ][posY ] == roomthreeD ||
		map[posX ][posY ] == roomthreeU ||
		map[posX ][posY ] == roomthreeL ||
		map[posX ][posY ] == roomfour
		)
	{
		return true;
	}else
		return false;
}

void FloorGenerator::generateMap(int floornum)
{
	//start with a clean map.
	resetMap();

	//Determine how many rooms the floor will have.
	switch(floornum)
	{
	case 1: case 2: case 3: case 4:
		{
			room_num = rand() % 2 + 5;
			break;
		}	
	case 6: case 7: case 8: case 9:
		{
			room_num = rand() % 2 + 7;
			break;
		}	
	case 11: case 12: case 13: case 14:
		{
			room_num = rand() % 2 + 9;
			break;
		}
	case 5: case 10: case 15:
		{
			room_num = 2;
			break;
		}
	}

	//Determine the starting point of the first room.
	Room starting;
	starting.setX(LIMIT / 2);
	starting.setY(LIMIT / 2);
	starting.setTreasure(false);
	starting.setStairs(false);
	starting.setType(true);
	starting.setArrival(true);

	//decrement the amount of rooms
	room_max = room_num;
	--room_num;


	unsigned char begin = ' ';

	//Determine the starting room

	//15 types of rooms
	int temp_num = rand() %15;

	switch(temp_num)
	{
	case 0: begin = roomoneU; break;
	case 1: begin = roomoneD; break;
	case 2: begin = roomoneL; break;
	case 3: begin = roomoneR; break;
	case 4: begin = roomtwoH; break;
	case 5: begin = roomtwoV; break;
	case 6: begin = roomtwoUR; break;
	case 7: begin = roomtwoDR; break;
	case 8: begin = roomtwoDL; break;
	case 9: begin = roomtwoUL; break;
	case 10: begin = roomthreeU; break;
	case 11: begin = roomthreeD; break;
	case 12: begin = roomthreeL; break;
	case 13: begin = roomthreeR; break;
	case 14: begin = roomfour; break;
	}

	starting.setIcon(begin);


	if(floornum == 5 || floornum == 10 || floornum == 15)
	{
		starting.setX(LIMIT/2);
		starting.setY(LIMIT/2);
		starting.setIcon(roomoneU);
	}

	map[starting.getX()][starting.getY()] = starting.getIcon();
	start.push(starting);
	rooms.push_back(starting);

	addRC(floornum);

	if(!checkValidMap())
	{
		while(!checkValidMap())
		{
			resetMap();
			emptyQueue();
			emptyCor();
			emptyRoom();

			room_num = room_max - 1;

			map[starting.getX()][starting.getY()] = starting.getIcon();
			start.push(starting);
			rooms.push_back(starting);
			addRC(floornum);
		}
	}

	//assign stairs to a room
	unsigned int stair_num = rand() % (rooms.size() - 1) + 1;

	for(unsigned int i = 0; i < rooms.size(); i++)
	{
		//arrival room should always be the first room in the vector
		if(rooms[i].getArrival())
			continue;
		//set the stairs to a room
		if(i == stair_num)
			rooms[i].setStairs(true);

		//if the room isn't the arrival room, and the room doesn't have stairs, it can have a treasure
		if(!rooms[i].getArrival() && !rooms[i].getStairs())
		{
			int temp = rand() % 2;
			if(temp == 1)
				rooms[i].setTreasure(true);
		}
	}	
}

void FloorGenerator::checkAvailableU(int posX, int posY, bool room)
{
	//check position above for edge
	if(posX-1 >= 0)
	{
		//check for availability
		if(map[posX-1][posY] == ' ')
		{
			//determine whether to assign a room or corridor
			if(room_num != 0 && !room)
			{
				int temp = rand() % 2;
				if(temp == 0)
					add_room = false;
				else
					add_room = true;

				if(add_room)
				{
					--room_num; 
					assignUp(add_room);
				}//end if
				else
					assignUp(add_room);
			}else  //end if
			{
				add_room = false;
				assignUp(add_room);
			}//end else
		}//endif
	}//endif
}

void FloorGenerator::checkAvailableD(int posX, int posY, bool room)
{
	//check position below for edge
	if(posX+1  <= LIMIT - 1)
	{
		//check for availability
		if(map[posX+1][posY] == ' ')
		{
			//determine whether to assign a room or corridor
			if(room_num != 0 && !room)
			{
				int temp = rand() % 2;
				if(temp == 0)
					add_room = false;
				else
					add_room = true;
				if(add_room)
				{
					--room_num;
					assignDown(add_room);
				}//end if
				else
					assignDown(add_room);
			}else  //end if
			{
				add_room = false;
				assignDown(add_room);
			}//end else
		}//endif
	}//endif
}

void FloorGenerator::checkAvailableL(int posX, int posY, bool room)
{
	//check position to the left for edge
	if(posY -1 >= 0)
	{
		//check for availability
		if(map[posX][posY-1] == ' ')
		{
			//determine whether to assign a room or corridor
			if(room_num != 0 && !room)
			{
				int temp = rand() % 2;
				if(temp == 0)
					add_room = false;
				else
					add_room = true;
				if(add_room)
				{
					--room_num; 
					assignLeft(add_room);
				}//end if
				else
					assignLeft(add_room);
			}else  //end if
			{
				add_room = false;
				assignLeft(add_room);
			}//end else
		}//endif
	}//endif
}

void FloorGenerator::checkAvailableR(int posX, int posY, bool room)
{
	//check position to the right for edge
	if(posY+1 <= LIMIT-1)
	{
		//check for availability
		if(map[posX][posY+1] == ' ')
		{
			//determine whether to assign a room or corridor
			if(room_num != 0 && !room)
			{
				int temp = rand() % 2;
				if(temp == 0)
					add_room = false;
				else
					add_room = true;
				if(add_room)
				{
					--room_num; 
					assignRight(add_room);
				}//end if
				else
					assignRight(add_room);
			}else  //end if
			{
				add_room = false;
				assignRight(add_room);
			}//end else
		}//endif
	}//endif
}

void FloorGenerator::addRC(int floornum)
{
	//Determine whether the floor is fixed or generated
	if(floornum == 5 || floornum == 10 || floornum == 15)
	{
		Corridor next;
		next.setX(start.front().getX()-1);
		next.setY(start.front().getY());
		next.setIcon(twoV);
		start.pop();
		map[next.getX()][next.getY()] = next.getIcon(); 
		corridor.push_back(next);

		Room boss;
		boss.setX(next.getX() - 1);
		boss.setY(next.getY());
		boss.setIcon(roomoneD);
		boss.setStairs(true);
		boss.setTreasure(false);
		--room_num;
		rooms.push_back(boss);

		map[boss.getX()][boss.getY()] = boss.getIcon();


	}//end if
	else
	{
		while(!start.empty())
		{
			//use temporary containers
			int posX = start.front().getX();
			int posY = start.front().getY();
			unsigned char icon = start.front().getIcon();
			bool type = start.front().getType();

			//Check the start queue to determine what to add next
			switch(icon)
			{
			case oneD: case roomoneD:
				{
					checkAvailableD(posX, posY, type);
					start.pop();
					break;
				}//end oneD
			case oneU: case roomoneU:
				{
					checkAvailableU(posX, posY, type);
					start.pop();
					break;
				}//end oneU
			case oneL: case roomoneL:
				{
					checkAvailableL(posX, posY, type);
					start.pop();
					break;
				}
			case oneR: case roomoneR:
				{
					checkAvailableR(posX, posY, type);
					start.pop();
					break;
				}
			case twoH: case roomtwoH:
				{
					checkAvailableL(posX, posY, type);
					checkAvailableR(posX, posY, type);
					start.pop();
					break;
				}
			case twoV: case roomtwoV:
				{
					checkAvailableU(posX, posY, type);
					checkAvailableD(posX, posY, type);
					start.pop();
					break;
				}
			case twoUR: case roomtwoUR:
				{
					checkAvailableU(posX, posY, type);
					checkAvailableR(posX, posY, type);
					start.pop();
					break;
				}
			case twoDR: case roomtwoDR:
				{
					checkAvailableD(posX, posY, type);
					checkAvailableR(posX, posY, type);
					start.pop();
					break;
				}
			case twoDL: case roomtwoDL:
				{
					checkAvailableD(posX, posY, type);
					checkAvailableL(posX, posY, type);
					start.pop();
					break;
				}
			case twoUL: case roomtwoUL:
				{
					checkAvailableU(posX, posY, type);
					checkAvailableL(posX, posY, type);
					start.pop();
					break;
				}
			case threeU: case roomthreeU:
				{
					checkAvailableU(posX, posY, type);
					checkAvailableL(posX, posY, type);
					checkAvailableR(posX, posY, type);
					start.pop();
					break;
				}
			case threeD: case roomthreeD:
				{
					checkAvailableD(posX, posY, type);
					checkAvailableL(posX, posY, type);
					checkAvailableR(posX, posY, type);
					start.pop();
					break;
				}
			case threeL: case roomthreeL:
				{
					checkAvailableL(posX, posY, type);
					checkAvailableD(posX, posY, type);
					checkAvailableU(posX, posY, type);
					start.pop();
					break;
				}
			case threeR: case roomthreeR:
				{
					checkAvailableR(posX, posY, type);
					checkAvailableD(posX, posY, type);
					checkAvailableU(posX, posY, type);
					start.pop();
					break;
				}
			case four: case roomfour:
				{
					checkAvailableL(posX, posY, type);
					checkAvailableR(posX, posY, type);
					checkAvailableD(posX, posY, type);
					checkAvailableU(posX, posY, type);
					start.pop();
					break;
				}

			}//end switch
		}//end while
	}//end else
}

void FloorGenerator::assignUp(bool room)
{
	//8 different types of Corridors can be assigned
	int temp = rand() % 8;
	int posX = start.front().getX();
	int posY = start.front().getY();

	const int ONED = 0, TWOV = 1, TWODR = 2, TWODL = 3, THREED = 4, THREEL = 5, THREER = 6, FOUR = 7;

	switch(temp)
	{
	case ONED: 
		{
			//create temp variables to store checks
			bool up, left, right;

			//determine whether or not to check for up, left, right due to limits
			if(posX-2 < 0)
				up = true;
			else
				up = !checkUp2(posX-2, posY);

			if(posY-1 < 0)
				left = true;
			else
				left = !checkLeft2(posX-1, posY-1);

			if(posY+1 > LIMIT-1)
				right = true;
			else
				right = !checkRight2(posX-1, posY+1);


			if(up && left && right)					
			{
				if(room)
					pushRoom(posX-1, posY, roomoneD, room);
				else
					pushCor(posX-1, posY, oneD, room);
			}else
				assignUp(room);
			break;
		}
	case TWOV:
		{
			//check for available position above where this piece is placed
			if(posX - 2 < 0)
			{
				//can't push assign a new piece
				assignUp(room);
				break;
			}else
			{
				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = false;
				else
					up = checkUp(posX-2, posY);

				if(posY-1 < 0)
					left = true;
				else
					left = !checkLeft2(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX-1, posY+1);


				//check for compatibility
				if(up && left && right)
				{
					//create a twoV corridor to push
					if(room)
						pushRoom(posX-1, posY, roomtwoV, room);
					else
						pushCor(posX-1, posY, twoV, room);
				}else
					assignUp(room);
			}
			break;
		}
	case TWODR:
		{
			//check right for availability
			if((posY+1) > LIMIT-1)
			{
				//can't push right, assign a new piece
				assignUp(room);
				break;
			}else
			{
				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = true;
				else
					up = !checkUp2(posX-2, posY);

				if(posY-1 < 0)
					left = true;
				else
					left = !checkLeft2(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX-1, posY+1);

				//check for existing areas for compatibility
				if(up && left && right)
				{
					if(room)
						pushRoom(posX-1, posY, roomtwoDR, room);
					else
						pushCor(posX-1, posY, twoDR, room);
				}else
					assignUp(room);
			}
			break;
		}
	case TWODL:
		{
			//Check left for availability
			if((posY-1) < 0)
			{
				//can't assign left, assign a new piece
				assignUp(room);
				break;
			}else
			{
				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = true;
				else
					up = !checkUp2(posX-2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX-1, posY+1);

				//check existing areas for compatibility
				if(up && left && right)
				{
					//push twoDL corridor to the queue
					if(room)
						pushRoom(posX-1, posY, roomtwoDL, room);
					else
						pushCor(posX-1, posY, twoDL, room);
				}else
					assignUp(room);
			}
			break;
		}
	case THREED:
		{
			//check left and right for edges
			if((posY - 1) < 0)
			{
				//can't assign left, assign a new piece
				assignUp(room);
				break;
			}
			else if(posY +1 > LIMIT)
			{
				//can't assign right, assign a new piece
				assignUp(room);
				break;
			}
			else
			{
				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = true;
				else
					up = !checkUp2(posX-2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX-1, posY+1);

				//check for existing areas for compatibility
				if( up && left && right)
				{
					//push threeD corridor onto the queue
					if(room)
						pushRoom(posX-1, posY, roomthreeD, room);
					else
						pushCor(posX-1, posY, threeD, room);
				}else
					assignUp(room);
			}
			break;
		}
	case THREEL:
		{
			//check left and top
			if((posY-1) < 0)
			{
				//can't assign left, assign a new piece
				assignUp(room);
				break;
			}
			if((posX-2) < 0)
			{
				assignUp(room);
				break;
			}
			else
			{
				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = false;
				else
					up = checkUp(posX-2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX-1, posY+1);

				//check existing areas
				if(up && left && right)
				{
					if(room)
						pushRoom(posX-1, posY, roomthreeL, room);
					else
						pushCor(posX-1, posY, threeL, room);
					break;
				}else
					assignUp(room);
			}

			break;
		}
	case THREER:
		{
			//check top and right
			if((posX-2) < 0)
			{
				assignUp(room);
				break;
			}else if(posY + 1 > LIMIT-1)
			{
				assignUp(room);
				break;
			}else
			{

				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = false;
				else
					up = checkUp(posX-2, posY);

				if(posY-1 < 0)
					left = true;
				else
					left = !checkLeft2(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX-1, posY+1);

				//check top and right for compatibility
				if(up && left && right)
				{
					//push threeR corridor onto the queue
					if(room)
						pushRoom(posX-1, posY, roomthreeR, room);
					else
						pushCor(posX-1, posY, threeR, room);
					break;
				}else
					assignUp(room);
			}
			break;
		}
	case FOUR:
		{
			//check up, left and right
			if(posY -1 < 0)
			{
				assignUp(room);
				break;
			}else if(posY+1 > LIMIT-1)
			{
				assignUp(room);
				break;
			}else if(posX-2 < 0)
			{
				assignUp(room);
				break;
			}else
			{
				//create temp variables to store checks
				bool up, left, right;

				//determine whether or not to check for up, left, right due to limits
				if(posX-2 < 0)
					up = false;
				else
					up = checkUp(posX-2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX-1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX-1, posY+1);

				if(up && left && right)
				{
					if(room)
						pushRoom(posX-1, posY, roomfour, room);
					else
						pushCor(posX-1, posY, four, room);
				}else
					assignUp(room);
			}
			break;
		}
	}//end switch
}

void FloorGenerator::assignDown(bool room)
{
	int temp = rand() % 8;
	int posX = start.front().getX();
	int posY = start.front().getY();

	const int ONEU = 0, TWOV = 1, TWOUL= 2, TWOUR = 3, THREEU = 4, THREEL = 5, THREER = 6, FOUR = 7;

	switch(temp)
	{
	case ONEU:
		{
			bool down, left, right;

			if(posX+2 > LIMIT-1)
				down = true;
			else
				down = !checkDown2(posX+2, posY);

			if(posY-1 < 0)
				left = true;
			else
				left = !checkLeft2(posX+1, posY-1);

			if(posY+1 > LIMIT-1)
				right = true;
			else
				right = !checkRight2(posX+1, posY+1);

			if(down && left && right)
			{
				if(room)
					pushRoom(posX+1, posY, roomoneU, room);
				else
					pushCor(posX+1, posY, oneU, room);
			}else
				assignDown(room);
			break;
		}
	case TWOV:
		{
			if(posX + 2 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;

				if(posX+2 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+2, posY);

				if(posY-1 < 0)
					left = true;
				else
					left = !checkLeft2(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomtwoV, room);
					else
						pushCor(posX+1, posY, twoV, room);
					break;
				}else
					assignDown(room);
			}
			break;
		}
	case TWOUL:
		{
			if(posY-1 < 0)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;
				if(posX+2 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomtwoUL, room);
					else
						pushCor(posX+1, posY, twoUL, room);

				}else
					assignDown(room);
			}
			break;
		}
	case TWOUR:
		{
			if(posY+1 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;

				if(posX+2 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+2, posY);

				if(posY-1 < 0)
					left = true;
				else
					left = !checkLeft2(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomtwoUR, room);
					else
						pushCor(posX+1, posY, twoUR, room);
				}else
					assignDown(room);
			}
			break;
		}
	case THREEU:
		{
			if(posY-1 < 0)
			{
				assignDown(room);
				break;
			}else if(posY+1 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;
				if(posX+2 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomthreeU, room);
					else
						pushCor(posX+1, posY, threeU, room);

				}else
					assignDown(room);

			}
			break;
		}
	case THREEL:
		{
			if(posY-1 < 0)
			{
				assignDown(room);
				break;
			}else if(posX+2 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;

				if(posX+2 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomthreeL, room);
					else
						pushCor(posX+1, posY, threeL, room);
				}else
					assignDown(room);
			}
			break;
		}
	case THREER:
		{
			if(posY+1 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else if(posX+2 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;

				if(posX+2 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+2, posY);

				if(posY-1 < 0)
					left = true;
				else
					left = !checkLeft2(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomthreeR, room);
					else
						pushCor(posX+1, posY, threeR, room);
				}else
					assignDown(room);
			}
			break;
		}
	case FOUR:
		{
			if(posY+1 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else if(posY-1 < 0)
			{
				assignDown(room);
				break;
			}else if(posX+2 > LIMIT-1)
			{
				assignDown(room);
				break;
			}else
			{
				bool down, left, right;
				if(posX+2 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+2, posY);

				if(posY-1 < 0)
					left = false;
				else
					left = checkLeft(posX+1, posY-1);

				if(posY+1 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX+1, posY+1);

				if(down && left && right)
				{
					if(room)
						pushRoom(posX+1, posY, roomfour, room);
					else
						pushCor(posX+1, posY, four, room);
				}else
					assignDown(room);
			}
			break;
		}
	}//end switch

}

void FloorGenerator::assignLeft(bool room)
{
	int temp = rand() % 8;
	int posX = start.front().getX();
	int posY = start.front().getY();

	const int ONER = 0, TWOH = 1, TWOUR= 2, TWODR = 3, THREEU = 4, THREED = 5, THREER = 6, FOUR = 7;

	switch(temp)
	{
	case ONER:
		{
			bool up, down, left;

			if(posX-1 < 0)
				up = true;
			else
				up = !checkUp2(posX-1, posY-1);
			if(posX+1 > LIMIT-1)
				down = true;
			else
				down = !checkDown2(posX+1, posY-1);
			if(posY-2 < 0)
				left = true;
			else
				left = !checkLeft2(posX, posY-2);

			if(up && down && left)
			{
				if(room)
					pushRoom(posX, posY-1, roomoneR, room);
				else
					pushCor(posX, posY-1, oneR, room);
			}else
				assignLeft(room);
			break;
		}
	case TWOH:
		{
			if(posY-2 < 0)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = true;
				else
					up = !checkUp2(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+1, posY-1);
				if(posY-2 < 0)
					left = false;
				else
					left = checkLeft(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomtwoH, room);
					else
						pushCor(posX, posY-1, twoH, room);
				}else
					assignLeft(room);
			}
			break;
		}
	case TWOUR:
		{
			if(posX-1 < 0)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+1, posY-1);
				if(posY-2 < 0)
					left = true;
				else
					left = !checkLeft2(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomtwoUR, room);
					else
						pushCor(posX, posY-1, twoUR, room);
				}else
					assignLeft(room);
			}
			break;
		}
	case TWODR:
		{
			if(posX+1 > LIMIT-1)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = true;
				else
					up = !checkUp2(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY-1);
				if(posY-2 < 0)
					left = true;
				else
					left = !checkLeft2(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomtwoDR, room);
					else
						pushCor(posX, posY-1, twoDR, room);
				}else
					assignLeft(room);
			}
			break;
		}
	case THREEU:
		{
			if(posX-1 < 0)
			{
				assignLeft(room);
				break;
			}else if(posY-2 < 0)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+1, posY-1);
				if(posY-2 < 0)
					left = false;
				else
					left = checkLeft(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomthreeU, room);
					else
						pushCor(posX, posY-1, threeU, room);
				}else
					assignLeft(room);
			}
			break;
		}
	case THREED:
		{
			if(posX+1 > LIMIT-1)
			{
				assignLeft(room);
				break;
			}else if(posY-2 < 0)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = true;
				else
					up = !checkUp2(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY-1);
				if(posY-2 < 0)
					left = false;
				else
					left = checkLeft(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomthreeD, room);
					else
						pushCor(posX, posY-1, threeD, room);
				}else
					assignLeft(room);
			}

			break;
		}
	case THREER:
		{
			if(posX+1 > LIMIT-1)
			{
				assignLeft(room);
				break;
			}else if(posX-1 < 0)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY-1);
				if(posY-2 < 0)
					left = true;
				else
					left = !checkLeft2(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomthreeR, room);
					else
						pushCor(posX, posY-1, threeR, room);
				}else
					assignLeft(room);
			}
			break;
		}
	case FOUR:
		{
			if(posX+1 > LIMIT-1)
			{
				assignLeft(room);
				break;
			}else if(posX-1 < 0)
			{
				assignLeft(room);
				break;
			}else if(posY-2 < 0)
			{
				assignLeft(room);
				break;
			}else
			{
				bool up, down, left;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY-1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY-1);
				if(posY-2 < 0)
					left = false;
				else
					left = checkLeft(posX, posY-2);

				if(up && down && left)
				{
					if(room)
						pushRoom(posX, posY-1, roomfour, room);
					else
						pushCor(posX, posY-1, four, room);
				}else
					assignLeft(room);
			}
			break;
		}
	}
}

void FloorGenerator::assignRight(bool room)
{
	int temp = rand() % 8;
	int posX = start.front().getX();
	int posY = start.front().getY();

	const int ONEL = 0, TWOH = 1, TWOUL= 2, TWODL = 3, THREEU = 4, THREED = 5, THREEL = 6, FOUR = 7;

	switch(temp)
	{
	case ONEL:
		{
			bool up, down, right;

			if(posX-1 < 0)
				up = true;
			else
				up = !checkUp2(posX-1, posY+1);
			if(posX+1 > LIMIT-1)
				down = true;
			else
				down = !checkDown2(posX+1, posY+1);
			if(posY+2 > LIMIT-1)
				right = true;
			else
				right = !checkRight2(posX, posY+2);

			if(up && down && right)
			{
				if(room)
					pushRoom(posX, posY+1, roomoneL, room);
				else
					pushCor(posX, posY+1, oneL, room);
			}else
				assignRight(room);

			break;
		}
	case TWOH:
		{
			if(posY+2 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = true;
				else
					up = !checkUp2(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomtwoH, room);
					else
						pushCor(posX, posY+1, twoH, room);
				}else
					assignRight(room);
			}
			break;
		}
	case TWOUL:
		{
			if(posX-1 < 0)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomtwoUL, room);
					else
						pushCor(posX, posY+1, twoUL, room);
				}else
					assignRight(room);
			}
			break;
		}
	case TWODL:
		{
			if(posX+1 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = true;
				else
					up = !checkUp2(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomtwoDL, room);
					else
						pushCor(posX, posY+1, twoDL, room);
				}else
					assignRight(room);
			}
			break;
		}
	case THREEU:
		{
			if(posX-1 < 0)
			{
				assignRight(room);
				break;
			}else if(posY+2 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = true;
				else
					down = !checkDown2(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomthreeU, room);
					else
						pushCor(posX, posY+1, threeU, room);
				}else
					assignRight(room);
			}
			break;
		}
	case THREED:
		{
			if(posX+1 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else if(posY+2 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = true;
				else
					up = !checkUp2(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomthreeD, room);
					else
						pushCor(posX, posY+1, threeD, room);
				}else
					assignRight(room);
			}
			break;
		}
	case THREEL:
		{
			if(posX+1 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else if(posX-1 < 0)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = true;
				else
					right = !checkRight2(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomthreeL, room);
					else
						pushCor(posX, posY+1, threeL, room);
				}else
					assignRight(room);
			}
			break;
		}
	case FOUR:
		{
			if(posX + 1 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else if(posX -1 < 0)
			{
				assignRight(room);
				break;
			}else if(posY+2 > LIMIT-1)
			{
				assignRight(room);
				break;
			}else
			{
				bool up, down, right;

				if(posX-1 < 0)
					up = false;
				else
					up = checkUp(posX-1, posY+1);
				if(posX+1 > LIMIT-1)
					down = false;
				else
					down = checkDown(posX+1, posY+1);
				if(posY+2 > LIMIT-1)
					right = false;
				else
					right = checkRight(posX, posY+2);

				if(up && down && right)
				{
					if(room)
						pushRoom(posX, posY+1, roomfour, room);
					else
						pushCor(posX, posY+1, four, room);
				}else
					assignRight(room);
			}
			break;
		}
	}
}

void FloorGenerator::pushCor(int x, int y, unsigned char icon, bool type)
{
	Corridor temp;
	temp.setIcon(icon);
	temp.setX(x);
	temp.setY(y);
	temp.setType(type);
	map[temp.getX()][temp.getY()] = temp.getIcon();
	start.push(temp);
	corridor.push_back(temp);
}

void FloorGenerator::pushRoom(int x, int y, unsigned char icon, bool type)
{
	Room temp;
	temp.setIcon(icon);
	temp.setX(x);
	temp.setY(y);
	temp.setType(type);
	map[temp.getX()][temp.getY()] = temp.getIcon();
	start.push(temp);
	rooms.push_back(temp);
}

bool FloorGenerator::checkValidMap()
{
	if(room_num == 0)
		return true;
	else
		return false;
}

void FloorGenerator::emptyQueue()
{
	while(!start.empty())
		start.pop();
}

void FloorGenerator::emptyRoom()
{
	rooms.clear();
}

void FloorGenerator::emptyCor()
{
	corridor.clear();
}