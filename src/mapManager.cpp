#include "mapManager.h"

const bool MapManager::notWallAndDoorByMapIndex(const MapIndex& mapIndex) const {
	const char targetChar = getMapCol(mapIndex);
	return targetChar != tranMapTypeToChar(MapCellType::Wall) &&
		targetChar != tranMapTypeToChar(MapCellType::Door);
}

const bool MapManager::notWallByMapIndex(const MapIndex& mapIndex) const {
	const char targetChar = getMapCol(mapIndex);
	return targetChar != tranMapTypeToChar(MapCellType::Wall);
}

const bool MapManager::checkXYType(const Position& pos, const MapCellType& cellType) const {
	const MapIndex XY = tranPosToMapIndex(pos);
	const char targetType = getMapCol(XY);
	return targetType == tranMapTypeToChar(cellType);
}

const char MapManager::getMapCol(const MapIndex& mapIndex) const {
	return m_map[mapIndex.y][mapIndex.x];
}

const char MapManager::tranMapTypeToChar(const MapCellType& cellType) const {
	return static_cast<char>(cellType);
}

const bool MapManager::canMoveAtPosition(const Position& pos, const bool& canMoveDoor) const {
	const int x = pos.x;
	const int y = pos.y;
	//minus 1 due to origin position have one pixel.
	const MapIndex leftUpCorner = tranXYToMapIndex(x, y);
	const MapIndex leftDownCorner = tranXYToMapIndex(x, y + CELL_SIZE - 1);
	const MapIndex rightUpCorner = tranXYToMapIndex(x + CELL_SIZE - 1, y);
	const MapIndex rightDownCorner = tranXYToMapIndex(x + CELL_SIZE - 1, y + CELL_SIZE - 1);
	if (canMoveDoor) {
		return notWallByMapIndex(leftUpCorner) &&
			notWallByMapIndex(leftDownCorner) &&
			notWallByMapIndex(rightUpCorner) &&
			notWallByMapIndex(rightDownCorner);
	}
	return notWallAndDoorByMapIndex(leftUpCorner) &&
		notWallAndDoorByMapIndex(leftDownCorner) &&
		notWallAndDoorByMapIndex(rightUpCorner) &&
		notWallAndDoorByMapIndex(rightDownCorner);
}
