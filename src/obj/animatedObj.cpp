#include "animatedObj.h"

void AnimatedObj::setCanMoveDoor(const bool& val) {
	if (val == m_canMoveDoor) {
		return;
	}
	m_canMoveDoor = val;
}


void AnimatedObj::updateAnimation() {
	m_currentFrameIndex += 1;
	if (m_currentFrameIndex >= m_currentAnimation.totalFrame) {
		if (!m_currentAnimation.isReapted) {
			return;
		};
		m_currentFrameIndex = 0;
	};
	const float newSpriteX = m_currentAnimation.startSpriteX + static_cast<float>(m_currentFrameIndex * SPRITE_SIZE);
	const float newSpriteY = m_currentAnimation.startSpriteY;
	setSpriteXY(SpriteXY{ newSpriteX ,newSpriteY });
}

void AnimatedObj::setCurrentAnimation(const AnimationData& data) {
	m_currentAnimation = data;
	m_currentFrameIndex = 0;
	setSpriteXY({ data.startSpriteX,data.startSpriteY });
}
void AnimatedObj::setCurDirection(const Direction& dir) {
	m_currentDirection = dir;
}

void AnimatedObj::setSpeed(const int& s) {
	if (s == m_speed) {
		return;
	}
	m_speed = s;
}

AnimatedObj::AnimatedObj(
	const Texture2D& sprite, 
	const AnimationData& curAnimation, 
	const MapManager& mapManager, 
	const Position& pos, 
	const SpriteXY& spriteXY, 
	const int& speed, 
	const Direction& curDir
) :
	m_currentAnimation(curAnimation),
	m_mapManager(mapManager),
	m_speed(speed),
	m_currentDirection(curDir),
	BaseObj(
		sprite,
		pos,
		spriteXY
	) {}
