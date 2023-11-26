#pragma once
#include <unordered_map>
#include<utility>
#include "../../lib/raylib/include/raylib.h"
#include "../mapManager.h"
#include "base.h"
#include "animatedObj.h"
class PacmanObj :public AnimatedObj {
private:
	Direction m_nextTurnDir;
	int m_animateCounter = 0;
	bool isDie() const {
		return m_currentAnimation == m_animationDataMap.at("die");
	}
	const std::string getAnimationNameByDir(const Direction& dir) const {
		if (dir == directionUp) {
			return "up";
		}
		else if (dir == directionDown) {
			return "down";
		}
		else if (dir == directionRight) {
			return "right";
		}
		else if (dir == directionLeft) {
			return "left";
		}
		else {
			return "stay";
		}
	}
	void updatePosition() override
	{
		if (m_nextTurnDir != directionStay) {
			const int turnedX = m_pos.x + m_speed * m_nextTurnDir.x;
			const int turnedY = m_pos.y + m_speed * m_nextTurnDir.y;
			const Position turnedPos{ turnedX, turnedY };
			const bool posCanTurn = m_mapManager.canMoveAtPosition(turnedPos, m_canMoveDoor);
			if (posCanTurn) {
				setPosition(turnedPos);
				setCurDirection(m_nextTurnDir);
				const std::string aniName = getAnimationNameByDir(m_nextTurnDir);
				setCurrentAnimation(m_animationDataMap.at(aniName));
				setNextTurnDirection(directionStay);
				return;
			}
		}
		const int straightMoveX = m_pos.x + m_speed * m_currentDirection.x;
		const int straightMoveY = m_pos.y + m_speed * m_currentDirection.y;
		const Position straightMovePos{ straightMoveX, straightMoveY };
		const bool posCanMove = m_mapManager.canMoveAtPosition(straightMovePos, m_canMoveDoor);
		if (posCanMove) {
			setPosition(straightMovePos);
		}
		else {
			setCurDirection(directionStay);
			const std::string aniName = getAnimationNameByDir(m_nextTurnDir);
			setCurrentAnimation(m_animationDataMap.at(aniName));
		}

	}
public:
	const static AnimationDataMap m_animationDataMap;
	const Position& getPacmanPos() const {
		return m_pos;
	}
	void setNextTurnDirection(const Direction& dir) {
		if (m_nextTurnDir == dir) {
			return;
		}
		m_nextTurnDir = dir;
	}
	void drawSelf(const bool& needUpdate) override {
		const Vector2 positionVec2 = tranPosToVec2(m_pos + SPRITE_START_POS);
		DrawTextureRec(m_sprite, m_rec, positionVec2, WHITE);
		if (needUpdate) {
			if (!isDie()) {
				updatePosition();
			}
			if (m_animateCounter >= ANIMATION_MAX_COUNTER) {
				updateAnimation();
				m_animateCounter = 0;
			}
			else {
				m_animateCounter += 1;
			}
		}
	};
	PacmanObj(
		const Position& pos,
		const MapManager& mapManager,
		const Texture2D& sprite
	) :
		m_nextTurnDir(directionStay),
		AnimatedObj(
			sprite,
			PacmanObj::m_animationDataMap.at("stay"),
			mapManager,
			pos,
			SpriteXY{ m_currentAnimation.startSpriteX,m_currentAnimation.startSpriteY },
			PACMAN_SPEED,
			directionStay
		)
	{
	};
};