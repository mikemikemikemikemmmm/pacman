#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "base.h"
class PowerObj :public BaseObj {
public:
	bool operator ==(const PowerObj& other) const;
	bool operator !=(const PowerObj& other) const;
	void drawSelf(const bool& needUpdate, const Position& pos) override;
	PowerObj(
		const Position& pos,
		const Texture2D& sprite
	);
};