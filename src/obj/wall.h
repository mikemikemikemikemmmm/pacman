#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "base.h"
class WallObj :public BaseObj {
public:
	void drawSelf(const bool& needUpdate) override {
		DrawTextureRec(m_sprite, m_rec, tranPosToVec2(m_pos + SPRITE_START_POS), WHITE);
	}
	WallObj(
		const Position& pos,
		const Texture2D& sprite
	) :
		BaseObj(
			sprite,
			pos,
			SpriteXY{ 60,0 },
			0,
			directionStay) {};
};