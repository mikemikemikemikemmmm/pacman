#include "base.h"

void BaseObj::executeDraw(const Position& pos)
{
	const Vector2 positionVec2 = tranPosToVec2(pos + m_sprite_start_pos);
	DrawTextureRec(m_sprite, m_rec, positionVec2, WHITE);
}

void BaseObj::setPosition(const Position& pos) {
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void BaseObj::setSpriteSize(const float& width, const float& height)
{
	m_rec.height = height;
	m_rec.width = width;
	setSpriteStartPos();
}
void BaseObj::setSpriteXY(const SpriteXY& spriteXY) {
	m_rec.x = spriteXY.x;
	m_rec.y = spriteXY.y;
}
void BaseObj::setSpriteStartPos() {
	const int x = (CELL_SIZE - static_cast<int>(m_rec.width)) / 2;
	const int y = (CELL_SIZE - static_cast<int>(m_rec.height)) / 2;
	m_sprite_start_pos = Position{ x,y };
}



BaseObj::BaseObj(
	const Texture2D& sprite, 
	const Position& pos, 
	const SpriteXY& spriteXY
) :
	m_sprite(sprite),
	m_pos(pos),
	m_rec({ spriteXY.x,spriteXY.y,SPRITE_SIZE,SPRITE_SIZE}),
	m_sprite_start_pos({ 
	(CELL_SIZE - SPRITE_SIZE) / 2 ,
	(CELL_SIZE - SPRITE_SIZE) / 2 
		})
{}
