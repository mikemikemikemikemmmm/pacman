#pragma once
#include <algorithm>
#include <string>
#include "base.h"
#include "../mapManager.h"
class AnimatedObj :public BaseObj {
public:
	const MapManager& m_mapManager;
	AnimationData m_currentAnimation;
	int m_currentFrameIndex = 0;
	bool m_canMoveDoor = false;
	virtual void updatePosition() = 0;
	void setCanMoveDoor(const bool& val);
	void setSpriteXY(const SpriteXY& spriteXY);
	void updateAnimation();
	void setCurrentAnimation(const AnimationData& data);
	AnimatedObj(
		const Texture2D& sprite,
		const AnimationData& curAnimation,
		const MapManager& mapManager,
		const Position& pos,
		const SpriteXY& spriteXY,
		const int& speed,
		const Direction& curDir
	);
	virtual ~AnimatedObj() {};
	AnimatedObj() = delete;
};
