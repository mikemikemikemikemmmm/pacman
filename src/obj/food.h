#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "base.h"
class FoodObj :public BaseObj {
public:
	void drawSelf(const bool& needUpdate,const Position& pos) override;
	FoodObj(
		const Position& pos,
		const Texture2D& sprite
	);
};