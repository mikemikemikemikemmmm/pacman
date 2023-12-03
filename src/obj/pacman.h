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
	bool isDie() const;
	const std::string getAnimationNameByDir(const Direction& dir) const;
	void updatePosition() override;
public:
	const static AnimationDataMap m_animationDataMap;
	const Position& getPacmanPos() const;
	void setNextTurnDirection(const Direction& dir);
	void drawSelf(const bool& needUpdate, const Position& pos) override;
	PacmanObj(
		const Position& pos,
		const MapManager& mapManager,
		const Texture2D& sprite
	);
};