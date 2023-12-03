#pragma once
#include "../lib/raylib/include/raylib.h"
#include<vector>
#include<memory>
#include<optional>
#include<unordered_set>
#include<cmath>
#include<forward_list>
#include "gameStatus.h"
#include "ghostManager.h"
#include "audioManager.h"
#include "./obj/wall.h"
#include "./obj/power.h"
#include "./obj/pacman.h"
#include "./obj/food.h"
#include "./obj/ghost.h"

class ObjManager {
public:
	const Texture2D& m_sprite;
	const MapManager& m_mapManager;
	GameStatusManager& m_gameStatusManager;
	AudioManager& m_audioManager;
	std::unique_ptr<GhostManager> m_ghostManager;
	PacmanObj m_pacman;
	WallObj m_wall;
	PowerObj m_power;
	FoodObj m_food;
	PositionSet m_wallPositionSet;
	PositionSet m_powerPositionSet;
	PositionSet m_foodPositionSet;

	static bool checkTouchByTwoPosition(const Position& p1, const Position& p2);
	void checkEvent();
	void checkPacmanEatPower();
	void checkPacmanMeetGhost();
	void checkPacmanEatFood();
	void drawAllObj();
	void handleKeyPressed(const Direction& dir);
	void handleGameOver();
	void handleGameWin();
	ObjManager(
		AudioManager& audioManager,
		GameStatusManager& gameStatusManager,
		const MapManager& mapManager,
		const Texture2D& sprite,
		const PositionSet& wallPosSet,
		const PositionSet& powerPosSet,
		const PositionSet& foodPosSet
	);
};