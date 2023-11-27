#include "wall.h"

WallObj::WallObj(
	const Position& pos,
	const Texture2D& sprite
) :
	BaseObj(
		sprite,
		pos,
		SpriteXY{ 60,0 },
		0,
		directionStay) {};
void WallObj::drawSelf(const bool& needUpdate) {
	DrawTextureRec(m_sprite, m_rec, tranPosToVec2(m_pos + SPRITE_START_POS), WHITE);
}
