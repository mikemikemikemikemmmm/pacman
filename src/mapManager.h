#pragma once
#include "../lib/raylib/include/raylib.h"
#include<vector>
#include<cmath>
#include "utils.h"
#include "global.h"
class MapManager {
private:
	const bool notWallAndDoorByMapIndex(const MapIndex& mapIndex) const;
	const bool notWallByMapIndex(const MapIndex& mapIndex) const;
	const bool checkXYType(const Position& pos, const MapCellType& cellType) const;
	const char getMapCol(const MapIndex& mapIndex) const;
public:
	const MapType m_map;
	const char tranMapTypeToChar(const MapCellType& cellType) const;
	const bool canMoveAtPosition(const Position& pos, const bool& canMoveDoor) const;
	MapManager(const MapType& map) :m_map(map) {};
};