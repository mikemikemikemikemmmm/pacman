#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "../utils.h"
class BaseObj {
public:
	const Texture2D& m_sprite;
	Position m_pos;
	Position m_sprite_start_pos;
	Rectangle m_rec;
	virtual void drawSelf(const bool& needUpdate,const Position& position) = 0;
	void executeDraw(const Position& pos);
	void setPosition(const Position& pos);
	void setSpriteSize(const float& width,const float& height);
	void setSpriteXY(const SpriteXY& spriteXY);
	void setSpriteStartPos();
	BaseObj(
		const Texture2D& sprite,
		const Position& pos,
		const SpriteXY& spriteXY);
	virtual ~BaseObj() =default;
	BaseObj() = delete;
};