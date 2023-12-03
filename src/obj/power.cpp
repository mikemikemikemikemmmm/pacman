#include "power.h"


bool PowerObj::operator ==(const PowerObj& other) const {
	return this->m_pos == other.m_pos;
}
bool PowerObj::operator !=(const PowerObj& other) const {
	return this->m_pos != other.m_pos;
}
void PowerObj::drawSelf(const bool& needUpdate, const Position& pos) {
	executeDraw(pos);
}

PowerObj::PowerObj(
	const Position& pos,
	const Texture2D& sprite
) :
	BaseObj(
		sprite,
		pos,
		SpriteXY{ 100,160 }
	) {
	setSpriteSize(SPRITE_SIZE, SPRITE_SIZE);
};