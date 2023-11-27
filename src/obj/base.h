#pragma once
#include "../../lib/raylib/include/raylib.h"
#include "../global.h"
#include "../utils.h"
class BaseObj {
public:
	const Texture2D& m_sprite;
	int m_speed;
	SpriteXY m_spriteXY;
	float m_spriteWidth = SPRITE_SIZE;
	float m_spriteHieght = SPRITE_SIZE;
	Position m_pos;
	Direction  m_currentDirection;
	Rectangle m_rec{
		m_spriteXY.x,
		m_spriteXY.y,
		m_spriteWidth,
		m_spriteHieght
	};
	virtual void drawSelf(const bool& needUpdate) = 0;
	void setPosition(const Position& pos);
	void setCurDirection(const Direction& dir);
	void setSpeed(const int& s);
	BaseObj(
		const Texture2D& sprite,
		const Position& pos,
		const SpriteXY& spriteXY,
		const int& speed,
		const Direction& currentDirection);
	virtual ~BaseObj() {};
	BaseObj() = delete;
};