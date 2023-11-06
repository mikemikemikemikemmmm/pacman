#pragma once
#include <raylib.h>
#include<vector>
#include<cmath>
#include "utils.h"
#include"global.h"
class GameMapManager {
public:
	MapType m_map;
	void setMapCol(const MapIndex& mapIndex, const MapCellType& cellType) {
		m_map[mapIndex.y][mapIndex.x]  = static_cast<char>(cellType) ;
	}
	char getMapCol(const MapIndex& mapIndex) {
		return m_map[mapIndex.y][mapIndex.x];
	};
	bool isWallByMapIndex(const MapIndex& mapIndex) {
		return getMapCol(mapIndex) == static_cast<char>(MapCellType::Wall);
	};
	bool notWallByMapIndex(const MapIndex& mapIndex) {
		return getMapCol(mapIndex) != static_cast<char>(MapCellType::Wall);
	};
	bool isWallByXY(const int& x,const int& y) {
		MapIndex XY = tranXYToMapIndex(x,y);
		return isWallByMapIndex(XY);
	};
	bool canMoveAtPosition(const int& x,const int& y) {
		MapIndex leftUpCorner = tranXYToMapIndex(x, y);
		MapIndex leftDownCorner = tranXYToMapIndex(x, y + CELL_SIZE-1);
		MapIndex rightUpCorner = tranXYToMapIndex(x + CELL_SIZE-1, y);
		MapIndex rightDownCorner = tranXYToMapIndex(x + CELL_SIZE-1, y + CELL_SIZE-1);
		//minus 1 due to origin position have one pixel.
		return notWallByMapIndex(leftUpCorner) &&
			notWallByMapIndex(leftDownCorner) &&
			notWallByMapIndex(rightUpCorner) &&
			notWallByMapIndex(rightDownCorner);
	};
	GameMapManager(const MapType& map) :m_map(map) {};
};