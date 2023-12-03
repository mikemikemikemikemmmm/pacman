#include "ghostManager.h"

void GhostManager::handlePacmanEatPower() {
	auto targetGhostPtrList = std::vector<GhostObj*>();
	for (auto& g : m_ghostList) {
		if (g->m_animationStatus != GhostObj::AnimationStatus::die &&
			g->m_moveStatus != GhostObj::MoveStatus::stayAtStartPos&&
			g->m_moveStatus != GhostObj::MoveStatus::goOutDoor
			) {
			targetGhostPtrList.push_back(g);
			g->setAnimationStatus(GhostObj::AnimationStatus::panic);
			g->setMoveStatus(GhostObj::MoveStatus::panic);
		};
	};
	std::thread t([ptrList = std::move(targetGhostPtrList)]() {
		std::this_thread::sleep_for(std::chrono::seconds(GHOST_panic_SECOND));
		auto ghostWaitToPanicEndList = std::vector<GhostObj*>();
		for (auto& g : ptrList) {
			if (g->m_animationStatus == GhostObj::AnimationStatus::panic) {
				ghostWaitToPanicEndList.push_back(g);
				g->setAnimationStatus(GhostObj::AnimationStatus::panicEnd);
				g->setMoveStatus(GhostObj::MoveStatus::panic);
			}
		};
		if (ghostWaitToPanicEndList.empty()) {
			return;
		}
		std::this_thread::sleep_for(std::chrono::seconds(GHOST_panicEnd_SECOND));
		for (auto& g : ghostWaitToPanicEndList) {
			if (g->m_animationStatus == GhostObj::AnimationStatus::panicEnd) {
				g->setAnimationStatus(GhostObj::AnimationStatus::normal);
				g->setMoveStatus(GhostObj::MoveStatus::chase);
			}
		};
		});
	t.detach();
}

void GhostManager::drawAllGhost(const bool& needUpdate) {
	for (auto& g : m_ghostList) {
		handleGhostMoveStatus(*g);
		g->drawSelf(needUpdate,g->m_pos);
	}
}

void GhostManager::setGhostTargetWhenChase(GhostObj& ghost) {
	const Position& pacmanPos = m_pacman.getPacmanPos();
	const Position pacmanSymmetricPos = MAP_CENTER_POS * 2 - pacmanPos;
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
		ghost.setTargetPos(pacmanPos+m_pacman.m_currentDirection * 5);
		break;
	}
	case GhostObj::GhostColor::clyde: {
		ghost.setTargetPos(pacmanPos + m_pacman.m_currentDirection * -5);
		break;
	}
	}
}

void GhostManager::handleGhostMoveStatus(GhostObj& ghost) {
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
		ghost.setAnimationStatus(GhostObj::AnimationStatus::normal);
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
			ghost.setAnimationStatus(GhostObj::AnimationStatus::normal);
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
			ghost.setSpeed(0);
			return;
		}
		ghost.setTargetPos(startPos);
		break;
	}
	case GhostObj::MoveStatus::panic: {
		const Position& pacmanPos = m_pacman.getPacmanPos();
		const Position pacmanToCenterVector = { MAP_CENTER_POS - pacmanPos };
		const Position mapEdgePos = MAP_CENTER_POS + (pacmanToCenterVector * 2);
		ghost.setTargetPos(mapEdgePos);
		break;
	}
	}
}

GhostManager::GhostManager(const PacmanObj& pacman, const MapManager& mapManager, const Texture2D& sprite) :
	m_pacman(pacman),
	m_mapManager(mapManager),
	m_sprite(sprite),
	m_blinky(GhostObj::GhostColor::blinky, mapManager, sprite),
	m_pinky(GhostObj::GhostColor::pinky, mapManager, sprite),
	m_inky(GhostObj::GhostColor::inky, mapManager, sprite),
	m_clyde(GhostObj::GhostColor::clyde, mapManager, sprite)
{
	m_ghostList.reserve(4);
	m_ghostList.push_back(&m_blinky);
	m_ghostList.push_back(&m_pinky);
	m_ghostList.push_back(&m_inky);
	m_ghostList.push_back(&m_clyde);
}
