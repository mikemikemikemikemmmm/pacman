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
	const static int m_maxIntValue = std::numeric_limits<int>::max();
	const std::shared_ptr <PacmanObj> m_pacmanPtr;
	const std::shared_ptr <MapManager> m_mapManager;
	const std::shared_ptr <Texture2D> m_spritePtr;
	const std::shared_ptr <std::vector<PowerObj>> m_powerList;
	std::vector<GhostObj*> m_ghostPtrList;
	Position* m_pacmanPosPtr = &(m_pacmanPtr->m_pos);
	GhostObj m_Blinky;
	void handlePacmanMeetGhost(GhostObj& g) {
		if (g.m_status == GhostObj::GhostStatus::Panic||
			g.m_status == GhostObj::GhostStatus::PanicEnd) {
			g.setStatus(GhostObj::GhostStatus::Die);
		}
	}
	void handleAsyncSetStatusWhenPacmanEatPower(const std::shared_ptr<std::vector<GhostObj*>>& gPtrList ) {
			std::this_thread::sleep_for(std::chrono::seconds(3));
			for (auto& gPtr : *gPtrList) {
				gPtr->setStatus(GhostObj::GhostStatus::PanicEnd);
			};
			std::this_thread::sleep_for(std::chrono::seconds(2));
			for (auto& gPtr : *gPtrList) {
				gPtr->setStatus(GhostObj::GhostStatus::Chase);
			};
	}
	void handlePacmanEatPower() {
		auto targetGhostPtrList = std::make_shared<std::vector<GhostObj*>>();
		for (auto& g : m_ghostPtrList) {
			if (g->m_status != GhostObj::GhostStatus::Die) {
				targetGhostPtrList->push_back(g);
				g->setStatus(GhostObj::GhostStatus::Panic);
			};
		};
		std::thread t(&GhostManager::handleAsyncSetStatusWhenPacmanEatPower,this, targetGhostPtrList);
		t.detach();
	}
	void drawAllGhost(){
		for (auto& gPtr: m_ghostPtrList) {
			setGhostTarget(*gPtr);
			gPtr->drawSelf();
		}
	};
	void setGhostTargetWhenChase(GhostObj& ghost) {	
		switch (ghost.m_color) {
			case GhostObj::GhostColor::Blinky: {
				ghost.setTargetPos(*m_pacmanPosPtr);
				break;
			}
			case GhostObj::GhostColor::Pinky: {
				Position targetPos = { *m_pacmanPosPtr * 2 - m_Blinky.m_pos };
				ghost.setTargetPos(targetPos);
				break;
			}
			case GhostObj::GhostColor::Inky: {
				auto powerSize = m_powerList->size();
				if (powerSize <= 1) {
					ghost.setTargetPos(*m_pacmanPosPtr);
					return;
				}
				int minIndex = 0;
				int min2Index = 0;
				int minDistance = m_maxIntValue;
				int min2Distance = m_maxIntValue - 1;
				for (int i = 0; i < m_powerList->size(); i++) {
					int diff = (*m_pacmanPosPtr - ((*m_powerList)[i].m_pos)).getDistance();
					if (diff > minDistance && diff <= min2Distance) {
						min2Index = i;
						min2Distance = diff;
					}
					else if (diff < minDistance) {
						minIndex = i;
						minDistance = diff;
					}
				}
				Position closestPowerToPacman = (*m_powerList)[min2Index].m_pos;
				ghost.setTargetPos(closestPowerToPacman);
				break;
			}
			case GhostObj::GhostColor::Clyde: {
				Direction pacmanOppositeDir = m_pacmanPtr->m_currentDirection*-4;
				ghost.setTargetPos(m_pacmanPtr->m_pos + pacmanOppositeDir);
				break;
			}
		}
	}
	void setGhostTarget(GhostObj& ghost) {
		switch (ghost.m_status)
		{
		case GhostObj::GhostStatus::Chase: {
			setGhostTargetWhenChase(ghost);
			break;
		}
		case GhostObj::GhostStatus::Die: {
			Position startPos = GhostObj::m_ghostStartPos.at(ghost.m_color);
			if (startPos ==ghost.m_pos) {
				ghost.setStatus(GhostObj::GhostStatus::WaitingForChase);
				return;
			}
			ghost.setTargetPos(startPos);
			break;
		}
		default: { //panic or panicEnd TODO
			break;
			}
		}
	}
	GhostManager(
		const std::shared_ptr<PacmanObj> pacmanPtr,
		const std::shared_ptr<MapManager> mapManagerPtr,
		const std::shared_ptr<Texture2D> spritePtr,
		const std::shared_ptr<std::vector<PowerObj>> powerList) :
		m_pacmanPtr(pacmanPtr),
		m_mapManager(mapManagerPtr),
		m_spritePtr(spritePtr),
		m_powerList(powerList),
		m_Blinky(GhostObj::GhostColor::Blinky, mapManagerPtr, spritePtr)
	{
		m_ghostPtrList.reserve(4);
		m_ghostPtrList.push_back(&m_Blinky); 
	}
};