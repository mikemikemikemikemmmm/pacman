#pragma once
#include <unordered_map>
#include <algorithm> 
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include "animatedObj.h"
class GhostObj : public AnimatedObj {
public:
	const enum class MoveStatus {
		chase, die, panic, stayAtStartPos, goOutDoor
	};
	const enum class AnimationStatus {
		normal, die, panic, panicEnd,
	};
	const enum class GhostColor {
		blinky, pinky, inky, clyde
	};
	const GhostColor m_color;
	const Position m_startPos;
	AnimationStatus m_animationStatus = AnimationStatus::normal;
	MoveStatus m_moveStatus = MoveStatus::stayAtStartPos;
	Position m_targetPos = PACMAN_START_POS;
	bool isChase() const;
	void setTargetPos(const Position& pos);
	void setMoveStatus(const MoveStatus& nextStatus);;
	void setAnimationStatus(const AnimationStatus& nextStatus);;
	void drawSelf(const bool& needUpdate) override;;
	GhostObj(
		const GhostColor& color,
		const MapManager& mapManager,
		const Texture2D& sprite
	);
private:
	const static std::unordered_map<AnimationStatus, std::string>
		m_animationNameMap;
	const static std::unordered_map<GhostColor, const Position>
		m_startPosMap;
	const static std::unordered_map<GhostColor, const AnimationDataMap>
		m_animationDataMap;
	int m_animateCounter = 0;
	static Direction getDirByAxisAndVal(const std::string& axis, const int& val);
	Direction getNextPositionDir();
	void updatePosition() override;;
};


