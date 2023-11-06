#include "utils.h"
#include <cmath>
Vector2 tranPosXYToVec2(const int& x, const int& y)
{
        float fX = static_cast<float>(x);
        float fY = static_cast<float>(y);
        return Vector2{ fX,fY };
}
MapIndex tranXYToMapIndex(const int& x, const int& y)
{
    int indexX = static_cast<int>(std::floor(x / CELL_SIZE)); 
    int indexY = static_cast<int>(std::floor(y / CELL_SIZE));
	return MapIndex{ indexX,indexY };
}
