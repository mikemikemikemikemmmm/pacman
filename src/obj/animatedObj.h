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
	Direction m_currentDirection;
	int m_speed;
	virtual void updatePosition() = 0;
	void updateAnimation();
	void setCanMoveDoor(const bool& val);
	void setCurrentAnimation(const AnimationData& data);
	void setCurDirection(const Direction& dir);
	void setSpeed(const int& s);
	AnimatedObj(
		const Texture2D& sprite,
		const AnimationData& curAnimation,
		const MapManager& mapManager,
		const Position& pos,
		const SpriteXY& spriteXY,
		const int& speed,
		const Direction& curDir
	);
	virtual ~AnimatedObj() = default;
	AnimatedObj() = delete;
};
