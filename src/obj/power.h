#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "base.h"
class PowerObj :public BaseObj {
public:
	bool operator ==(const PowerObj& other) const {
		return this->m_pos == other.m_pos;
	}
	bool operator !=(const PowerObj& other) const {
		return this->m_pos != other.m_pos;
	}
	void drawSelf(const bool& needUpdate) override {
		DrawTextureRec(m_sprite, m_rec, tranPosToVec2(m_pos + SPRITE_START_POS), WHITE);
	}
	PowerObj(
		const Position& pos,
		const Texture2D& sprite
	) :
		BaseObj(
			sprite,
			pos,
			SpriteXY{ 168,160 },
			0,
			directionStay) {};
};