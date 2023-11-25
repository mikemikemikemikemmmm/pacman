#pragma once
#include "../lib/raylib/include/raylib.h"
#include<vector>
#include<memory>
#include<cmath>
#include "utils.h"
#include "global.h"
#include "gameStatus.h"
#include "ghostManager.h"
#include "mapManager.h"
#include "./obj/wall.h"
#include "./obj/power.h"
#include "./obj/pacman.h"
#include "./obj/ghost.h"

class ObjManager {
public:
	const Texture2D& m_sprite;
	const GameStatusManager& m_gameStatusManager;
	const MapManager& m_mapManager;
	std::unique_ptr<GhostManager> m_ghostManager;
	PacmanObj m_pacman;
	std::vector<PowerObj> m_powerList;
	std::vector<WallObj> m_wallList;
	void handleKeyPressed(const Direction& dir){
		m_pacman.setNextTurnDirection(dir);
	}
	void checkEvent() {
		checkPacmanEatPower();
		checkPacmanMeetGhost();
	};
	void drawAllObj() {
		checkEvent();
		for (WallObj& w : m_wallList) {
			w.drawSelf();
		};
		for (PowerObj& p : m_powerList) {
			p.drawSelf();
		};
		m_ghostManager->drawAllGhost();
		m_pacman.drawSelf();
	}
	static bool checkTouchByTwoObj(const BaseObj& o1,const BaseObj& o2) {
		if (o1.m_pos.x == o2.m_pos.x) {
			return std::abs(o1.m_pos.y - o2.m_pos.y) <= OBJ_MEET_MAX_DISTANCE;
		}
		else if (o1.m_pos.y == o2.m_pos.y) {
			return std::abs(o1.m_pos.x - o2.m_pos.x) <= OBJ_MEET_MAX_DISTANCE;
		}
		else if (
			(
				std::abs(o1.m_pos.x - o2.m_pos.x) + 
				std::abs(o1.m_pos.y - o2.m_pos.y)
			) <=OBJ_MEET_MAX_DISTANCE
			) {
			return true;
		}
		else {
			return false;
		}
	}
	void checkPacmanEatPower() {
			for(auto& p : m_powerList) {
				if (this->checkTouchByTwoObj(p, m_pacman)) {
					m_powerList.erase(std::remove(m_powerList.begin(), m_powerList.end(), p), m_powerList.end());
					m_ghostManager->handlePacmanEatPower();
				}
			}
			if (m_powerList.empty()) {
				handleGameWin();
			}
		};
	void checkPacmanMeetGhost() {
			auto& ghostList = m_ghostManager->m_ghostList;
			for (auto& g : ghostList) {
				if (this->checkTouchByTwoObj(*g, m_pacman)) {
					if (g->m_moveStatus == GhostObj::MoveStatus::chase) {
						handleGameOver();
					}
					else {
						m_ghostManager->handlePacmanMeetGhost(*g);
					};
				};
			};
		};
	void handleGameOver() {

	}
	void handleGameWin() {

	}
	ObjManager(
		const GameStatusManager& gameStatusManager,
		const MapManager& mapManager,
		const Texture2D& sprite,
		const PacmanObj& pacman,
		const std::vector<WallObj>& wallList,
		const std::vector<PowerObj>& powerList
	) :
		m_gameStatusManager(gameStatusManager),
		m_mapManager(mapManager),
		m_sprite(sprite),
		m_pacman(pacman),
		m_wallList(wallList),
		m_powerList(powerList)
	{
		m_ghostManager = std::make_unique<GhostManager>(m_pacman, m_mapManager, m_sprite, m_powerList);
	}
};