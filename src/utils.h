#pragma once
#include "../lib/raylib/include/raylib.h"
#include <unordered_map>
#include <queue>
#include "global.h"
Vector2 tranPosToVec2(const Position& pos);
MapIndex tranPosToMapIndex(const Position& pos);
MapIndex tranXYToMapIndex(const int& x, const int& y);
Position calculateDistance(const Position& p1, const Position& p2);