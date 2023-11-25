#pragma once
#include<queue>
#include"global.h"
#include"mapManager.h"
#include"./obj/base.h"
struct Node {
	int x;
	int y;
	int stepCounter;
	bool lock;
	int cost;
};
typedef std::pair<Position, Direction> PathNode; //when at position,set direction.
std::queue<PathNode> getPathNodeQueue(const BaseObj& start, const BaseObj& end,const bool& canMoveDoor) {
	const Position posDiff = end.m_pos - start.m_pos;

}
