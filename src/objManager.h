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
	const std::shared_ptr<Texture2D> m_spritePtr;
	const std::shared_ptr<GameStatusManager> m_gameStatusManagerPtr;
	const std::shared_ptr <MapManager> m_mapManagerPtr;
	const std::shared_ptr <PacmanObj> m_pacmanPtr;
	std::shared_ptr<std::vector<PowerObj>>m_powerList;
	std::shared_ptr<std::vector<WallObj>> m_wallList;
	GhostManager m_ghostManager;
	void handleKeyPressed(const Direction& dir){
		m_pacmanPtr->setNextTurnDirection(dir);
	}
	void checkEvent() {
		checkPacmanEatPower();
		checkPacmanMeetGhost();
	};
	void drawAllObj() {
		checkEvent();
		for (WallObj& w : *m_wallList) {
			w.drawSelf();
		};
		for (PowerObj& p : *m_powerList) {
			p.drawSelf();
		};
		m_ghostManager.drawAllGhost();
		m_pacmanPtr->drawSelf();
	}
	bool checkTouchByTwoObj(const BaseObj& o1,const BaseObj& o2) {
		if (o1.m_pos.x == o2.m_pos.x) {
			return std::abs(o1.m_pos.y - o2.m_pos.y) <= OBJ_MEET_MAX_DISTANCE;
		}
		else if (o1.m_pos.y == o2.m_pos.y) {
			return std::abs(o1.m_pos.x - o2.m_pos.x) <= OBJ_MEET_MAX_DISTANCE;
		}
		else if (
			(std::abs(o1.m_pos.x - o2.m_pos.x) + std::abs(o1.m_pos.y - o2.m_pos.y)) <= OBJ_MEET_MAX_DISTANCE
			) {
			return true;
		}
		else {
			return false;
		}
	}
	void checkPacmanEatPower() {
			for(auto& p : *m_powerList) {
				if (checkTouchByTwoObj(p, *m_pacmanPtr)) {
					m_powerList->erase(std::remove(m_powerList->begin(), m_powerList->end(), p), m_powerList->end());
					m_ghostManager.handlePacmanEatPower();
				}
			}
			if (m_powerList->empty()) {
				handleGameWin();
			}
		};
	void checkPacmanMeetGhost() {
			auto& ghostList = m_ghostManager.m_ghostPtrList;
			for (auto& g : ghostList) {
				if (checkTouchByTwoObj(*g, *m_pacmanPtr)) {
					if (g->m_status == GhostObj::GhostStatus::Chase) {
						handleGameOver();
					}
					else {
						m_ghostManager.handlePacmanMeetGhost(*g);
					};
				};
			};
		};
	void handleGameOver() {

	}
	void handleGameWin() {

	}
	ObjManager(
		const std::shared_ptr<GameStatusManager> gameStatusManagerPtr,
		const std::shared_ptr<MapManager> mapManagerPtr,
		const std::shared_ptr<Texture2D> spritePtr,
		const std::shared_ptr<PacmanObj> pacmanPtr,
		const std::shared_ptr<std::vector<WallObj>> wallList,
		const std::shared_ptr<std::vector<PowerObj>> powerList
	) :
		m_gameStatusManagerPtr(gameStatusManagerPtr),
		m_mapManagerPtr(mapManagerPtr),
		m_spritePtr(spritePtr),
		m_pacmanPtr(pacmanPtr),
		m_wallList(wallList),
		m_powerList(powerList),
		m_ghostManager(pacmanPtr, mapManagerPtr, spritePtr, powerList)
	{
	}
	~ObjManager() {
	}
};