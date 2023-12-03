#include "pacman.h"
const AnimationDataMap PacmanObj::m_animationDataMap = {
		{"die", AnimationData{0,240,12,false} },
		{"up", AnimationData{0,40,3,true} },
		{"down", AnimationData{0,60,3,true} },
		{"right", AnimationData{0,20,3,true} },
		{"left", AnimationData{0,0,3,true} },
		{"stay", AnimationData{40,0,1,true} },
};

bool PacmanObj::isDie() const {
	return m_currentAnimation == m_animationDataMap.at("die");
}
const std::string PacmanObj::getAnimationNameByDir(const Direction& dir) const {
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
void PacmanObj::updatePosition() 
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
const Position& PacmanObj::getPacmanPos() const {
	return m_pos;
}
void PacmanObj::setNextTurnDirection(const Direction& dir) {
	if (m_nextTurnDir == dir) {
		return;
	}
	m_nextTurnDir = dir;
}
void PacmanObj::drawSelf(const bool& needUpdate,const Position& pos)  {
	executeDraw(pos);
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
PacmanObj::PacmanObj(
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