#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "base.h"
class WallObj :public BaseObj {
public:
	void drawSelf(const bool& needUpdate, const Position& pos) override;
	WallObj(
		const Position& pos,
		const Texture2D& sprite
	);
};