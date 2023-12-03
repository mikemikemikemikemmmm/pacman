#include "food.h"
void FoodObj::drawSelf(const bool& needUpdate, const Position& pos)
{
	executeDraw(pos);
}
FoodObj::FoodObj(
	const Position& pos,
	const Texture2D& sprite
) :
	BaseObj(
		sprite,
		pos,
		SpriteXY{ 113,182 }
	) {
	setSpriteSize(8, 8);
};