#pragma once
#include "../lib/raylib/include/raylib.h"
#include<vector>
#include<memory>
#include<optional>
#include<cmath>
#include<forward_list>
#include "gameStatus.h"
#include "ghostManager.h"
#include "audioManager.h"
#include "./obj/wall.h"
#include "./obj/power.h"
#include "./obj/pacman.h"
#include "./obj/ghost.h"

class ObjManager {
public:
	const Texture2D& m_sprite;
	const MapManager& m_mapManager;
	GameStatusManager& m_gameStatusManager;
	AudioManager& m_audioManager;
	std::unique_ptr<GhostManager> m_ghostManager;
	std::forward_list<PowerObj> m_powerList;
	std::vector<WallObj> m_wallList;
	PacmanObj m_pacman;
	static bool checkTouchByTwoObj(const BaseObj& o1, const BaseObj& o2);
	void checkEvent();
	void checkPacmanEatPower();
	void checkPacmanMeetGhost();
	void drawAllObj();
	void handleKeyPressed(const Direction& dir);
	void handleGameOver();
	void handleGameWin();
	ObjManager(
		AudioManager& audioManager,
		GameStatusManager& gameStatusManager,
		const MapManager& mapManager,
		const Texture2D& sprite,
		const PacmanObj& pacman,
		const std::vector<WallObj>& wallList,
		const std::forward_list<PowerObj>& powerList
	);
};