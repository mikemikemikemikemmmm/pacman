#pragma once
#include <vector>
#include <thread>
#include <array>
#include <memory>
#include <tuple>
#include <future>
#include <functional>
#include <algorithm>
#include "mapManager.h"
#include "obj/power.h"
#include "obj/pacman.h"
#include "obj/ghost.h"
class GhostManager {
public:
	const PacmanObj& m_pacman;
	const MapManager& m_mapManager;
	const Texture2D& m_sprite;
	std::vector<GhostObj*> m_ghostList;
	const static int m_maxIntValue = std::numeric_limits<int>::max();
	GhostObj m_blinky;
	GhostObj m_pinky;
	GhostObj m_inky;
	GhostObj m_clyde;
	void handlePacmanEatPower();
	void drawAllGhost(const bool& needUpdate);
	void setGhostTargetWhenChase(GhostObj& ghost);
	void handleGhostMoveStatus(GhostObj& ghost);
	GhostManager(
		const PacmanObj& pacman,
		const MapManager& mapManager,
		const Texture2D& sprite);
};