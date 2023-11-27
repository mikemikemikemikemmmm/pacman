#include "base.h"

void BaseObj::setPosition(const Position& pos) {
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void BaseObj::setCurDirection(const Direction& dir) {
	m_currentDirection = dir;
}

void BaseObj::setSpeed(const int& s) {
	if (s == m_speed) {
		return;
	}
	m_speed = s;
}

BaseObj::BaseObj(const Texture2D& sprite, const Position& pos, const SpriteXY& spriteXY, const int& speed, const Direction& currentDirection) :
	m_sprite(sprite),
	m_speed(speed),
	m_pos(pos),
	m_spriteXY(spriteXY),
	m_currentDirection(currentDirection)
{}
