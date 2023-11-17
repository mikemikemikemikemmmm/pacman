#include "utils.h"
#include <cmath>
Vector2 tranPosToVec2(const Position& pos)
{
    const float fX = static_cast<float>(pos.x);
    const float fY = static_cast<float>(pos.y);
        return Vector2{ fX,fY };
}
MapIndex tranPosToMapIndex(const Position& pos)
{
    const int indexX = static_cast<int>(std::floor(pos.x / CELL_SIZE));
    const int indexY = static_cast<int>(std::floor(pos.y / CELL_SIZE));
	return MapIndex{ indexX,indexY };
}

MapIndex tranXYToMapIndex(const int& x, const int& y)
{
    const int indexX = static_cast<int>(std::floor(x / CELL_SIZE));
    const int indexY = static_cast<int>(std::floor(y / CELL_SIZE));
	return MapIndex{ indexX,indexY };
}

Position calculateDistance(const Position& p1, const Position& p2)
{
    const int x = p2.x - p1.x;
    const int y = p2.y - p1.y;
    return Position();
}
