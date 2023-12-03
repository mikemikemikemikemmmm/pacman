#include "wall.h"

void WallObj::drawSelf(const bool& needUpdate, const Position& pos) {
	executeDraw(pos);
}
WallObj::WallObj(
	const Position& pos,
	const Texture2D& sprite
) :
	BaseObj(
		sprite,
		pos,
		SpriteXY{ 60,0 }
) {};
