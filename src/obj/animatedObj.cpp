#include "animatedObj.h"

void AnimatedObj::setCanMoveDoor(const bool& val) {
	if (val == m_canMoveDoor) {
		return;
	}
	m_canMoveDoor = val;
}

void AnimatedObj::setSpriteXY(const SpriteXY& spriteXY) {
	m_rec.x = spriteXY.x;
	m_rec.y = spriteXY.y;
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

AnimatedObj::AnimatedObj(const Texture2D& sprite, const AnimationData& curAnimation, const MapManager& mapManager, const Position& pos, const SpriteXY& spriteXY, const int& speed, const Direction& curDir) :
	m_currentAnimation(curAnimation),
	m_mapManager(mapManager),
	BaseObj(
		sprite,
		pos,
		spriteXY,
		speed,
		curDir
	) {}
