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
	void setCanMoveDoor(const bool& val) {
		if (val == m_canMoveDoor) {
			return;
		}
		m_canMoveDoor = val;
	}
	void setSpriteXY(const SpriteXY& spriteXY) {
		m_rec.x = spriteXY.x;
		m_rec.y = spriteXY.y;
	}
	void updateAnimation() {
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
	};
	void setCurrentAnimation(const AnimationData& data) {
		m_currentAnimation = data;
		m_currentFrameIndex = 0;
		setSpriteXY({ data.startSpriteX,data.startSpriteY });
	};
	AnimatedObj(
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
		BaseObj(
			sprite,
			pos,
			spriteXY,
			speed,
			curDir
		) {};
	virtual ~AnimatedObj() {};
	AnimatedObj() = delete;
};
