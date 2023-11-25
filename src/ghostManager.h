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
	std::vector<PowerObj>& m_powerList;
	std::vector<GhostObj*> m_ghostList;
	const static int m_maxIntValue = std::numeric_limits<int>::max();
	GhostObj m_blinky;
	void handlePacmanMeetGhost(GhostObj& g) const  {
		if (g.m_animationStatus == GhostObj::AnimationStatus::panic||
			g.m_animationStatus == GhostObj::AnimationStatus::panicEnd) {

			g.setAnimationStatus(GhostObj::AnimationStatus::die);
			g.setMoveStatus(GhostObj::MoveStatus::die);
		}
	}
	void handlePacmanEatPower() {
		auto targetGhostPtrList = std::vector<GhostObj*>();
		for (auto& g : m_ghostList) {
			if (g->m_animationStatus != GhostObj::AnimationStatus::die) {
				targetGhostPtrList.push_back(g);
				g->setAnimationStatus(GhostObj::AnimationStatus::panic);
				g->setMoveStatus(GhostObj::MoveStatus::panic);
			};
		};
		std::thread t([ptrList = std::move(targetGhostPtrList)]() {
			std::this_thread::sleep_for(std::chrono::seconds(GHOST_panic_SECOND));
			for (auto& g : ptrList) {
				if (g->m_animationStatus != GhostObj::AnimationStatus::panic) {
					return;
				}
				g->setAnimationStatus(GhostObj::AnimationStatus::panicEnd);
				std::this_thread::sleep_for(std::chrono::seconds(GHOST_panicEnd_SECOND));
				if (g->m_animationStatus != GhostObj::AnimationStatus::panicEnd) {
					return;
				}
				g->setAnimationStatus(GhostObj::AnimationStatus::normal);
				g->setMoveStatus(GhostObj::MoveStatus::chase);
			};
		});
		t.detach();
	}
	void drawAllGhost(){
		for (auto& g: m_ghostList) {
			handleGhostMoveStatus(*g);
			g->drawSelf();
		}
	};
	void setGhostTargetWhenChase(GhostObj& ghost) {	
		const Position& pacmanPos = m_pacman.getPacmanPos();
		switch (ghost.m_color) {
			case GhostObj::GhostColor::blinky: {
				ghost.setTargetPos(pacmanPos);
				break;
			}
			case GhostObj::GhostColor::pinky: {
				Position targetPos = { pacmanPos * 2 - m_blinky.m_pos };
				ghost.setTargetPos(targetPos);
				break;
			}
			case GhostObj::GhostColor::inky: {
				auto powerSize = m_powerList.size();
				if (powerSize <= 1) {
					ghost.setTargetPos(pacmanPos);
					return;
				}
				int minIndex = 0;
				int minDistance = m_maxIntValue;
				for (int i = 0; i < powerSize; i++) {
					int diff = (pacmanPos - (m_powerList[i].m_pos)).getDistance();
					if (diff < minDistance) {
						minIndex = i;
						minDistance = diff;
					}
				}
				Position closestPowerToPacman = m_powerList[minIndex].m_pos;
				ghost.setTargetPos(closestPowerToPacman);
				break;
			}
			case GhostObj::GhostColor::clyde: {
				Direction pacmanOppositeDir = m_pacman.m_currentDirection*-4;
				ghost.setTargetPos(m_pacman.m_pos + pacmanOppositeDir);
				break;
			}
		}
	}
	void handleGhostMoveStatus(GhostObj& ghost) {
		const GhostObj::MoveStatus& currentMove = ghost.m_moveStatus;
		switch (currentMove)
		{
		case GhostObj::MoveStatus::chase: {
			setGhostTargetWhenChase(ghost);
			break;
		}
		case GhostObj::MoveStatus::stayAtStartPos: {
			ghost.setSpeed(0);
			ghost.setMoveStatus(GhostObj::MoveStatus::goOutDoor);
			std::thread t([&ghost]() {
				std::this_thread::sleep_for(std::chrono::seconds(GHOST_stayAtStartPos_SECOND));
				ghost.setSpeed(GHOST_SPEED);
				});
			t.detach();
			break;
		}
		case GhostObj::MoveStatus::goOutDoor: {
			ghost.setCanMoveDoor(true);
			if (ghost.m_pos == DoorExitPos) {
				ghost.setMoveStatus(GhostObj::MoveStatus::chase);
				ghost.setCanMoveDoor(false);
				return;
			};
			ghost.setTargetPos(DoorExitPos);
			break;
		}
		case GhostObj::MoveStatus::die: {
			ghost.setCanMoveDoor(true);
			const Position& startPos = ghost.m_startPos;
			if (startPos == ghost.m_pos) {  // after be eaten and back to start pos.
				ghost.setMoveStatus(GhostObj::MoveStatus::stayAtStartPos);
				ghost.setAnimationStatus(GhostObj::AnimationStatus::normal);
				return;
			}
			ghost.setTargetPos(startPos);
			break;
		}
		case GhostObj::MoveStatus::panic: {
			const Position& pacmanPos = m_pacman.getPacmanPos();
			const Position pacmanToCenterVector = { MAP_CENTER_POS - pacmanPos };
			const Position mapEdgePos = MAP_CENTER_POS + (pacmanToCenterVector*2);
			ghost.setTargetPos(mapEdgePos);
			break;
		}
		}
	}
	GhostManager(
		const PacmanObj& pacman,
		const MapManager& mapManager,
		const Texture2D& sprite,
		std::vector<PowerObj>& powerList) :
		m_pacman(pacman),
		m_mapManager(mapManager),
		m_sprite(sprite),
		m_powerList(powerList),
		m_blinky(GhostObj::GhostColor::blinky, mapManager, sprite)
	{
		m_ghostList.reserve(4);
		m_ghostList.push_back(&m_blinky); 
	}
};