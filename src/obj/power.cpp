#include "power.h"


bool PowerObj::operator ==(const PowerObj& other) const {
	return this->m_pos == other.m_pos;
}
bool PowerObj::operator !=(const PowerObj& other) const {
	return this->m_pos != other.m_pos;
}
void PowerObj::drawSelf(const bool& needUpdate) {
	DrawTextureRec(m_sprite, m_rec, tranPosToVec2(m_pos + SPRITE_START_POS), WHITE);
}

PowerObj::PowerObj(
	const Position& pos,
	const Texture2D& sprite
) :
	BaseObj(
		sprite,
		pos,
		SpriteXY{ 168,160 },
		0,
		directionStay) {};