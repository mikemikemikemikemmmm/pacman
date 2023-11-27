#include "objManager.h"
void ObjManager::handleKeyPressed(const Direction& dir) {
	m_pacman.setNextTurnDirection(dir);
}

void ObjManager::checkEvent() {
	checkPacmanEatPower();
	checkPacmanMeetGhost();
}

void ObjManager::drawAllObj() {
	const bool& isGameOver = m_gameStatusManager.isGameOver();
	const bool& isPlaying = m_gameStatusManager.isPlaying();
	if (isPlaying) {
		checkEvent();
	}
	for (WallObj& w : m_wallList) {
		w.drawSelf(true);
	};
	for (PowerObj& p : m_powerList) {
		p.drawSelf(true);
	};
	if (!isGameOver) {
		m_ghostManager->drawAllGhost(isPlaying);
	}
	m_pacman.drawSelf(isPlaying || isGameOver);
}

bool ObjManager::checkTouchByTwoObj(const BaseObj& o1, const BaseObj& o2) {
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
			) <= OBJ_MEET_MAX_DISTANCE
		) {
		return true;
	}
	else {
		return false;
	}
}

void ObjManager::checkPacmanEatPower() {
	std::optional<PowerObj*> powerPtrBeEaten;
	for (auto& p : m_powerList) {
		if (this->checkTouchByTwoObj(p, m_pacman)) {
			powerPtrBeEaten = &p;
			break;
		}
	}
	if (powerPtrBeEaten.has_value()) {
		m_audioManager.playMusic("eatPower");
		m_powerList.remove(*(powerPtrBeEaten.value()));
		m_ghostManager->handlePacmanEatPower();
		if (m_powerList.empty()) {
			handleGameWin();
		}
	}
}

void ObjManager::checkPacmanMeetGhost() {
	auto& ghostList = m_ghostManager->m_ghostList;
	for (auto& g : ghostList) {
		if (this->checkTouchByTwoObj(*g, m_pacman)) {
			if (g->m_animationStatus == GhostObj::AnimationStatus::normal) {
				handleGameOver();
			}
			else if (
				g->m_animationStatus == GhostObj::AnimationStatus::panic ||
				g->m_animationStatus == GhostObj::AnimationStatus::panicEnd
				) {
				g->setAnimationStatus(GhostObj::AnimationStatus::die);
				g->setMoveStatus(GhostObj::MoveStatus::die);
				m_audioManager.playMusic("eatGhost");
			}
		}
	};
}

void ObjManager::handleGameOver() {
	m_pacman.setCurrentAnimation(PacmanObj::m_animationDataMap.at("die"));
	m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Gameover);
	m_audioManager.playMusic("gameOver");
}

void ObjManager::handleGameWin() {
	m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Win);
	m_audioManager.playMusic("gameWin");
}

ObjManager::ObjManager(AudioManager& audioManager, GameStatusManager& gameStatusManager, const MapManager& mapManager, const Texture2D& sprite, const PacmanObj& pacman, const std::vector<WallObj>& wallList, const std::forward_list<PowerObj>& powerList) :
	m_audioManager(audioManager),
	m_gameStatusManager(gameStatusManager),
	m_mapManager(mapManager),
	m_sprite(sprite),
	m_pacman(pacman),
	m_wallList(wallList),
	m_powerList(powerList)
{
	m_ghostManager = std::make_unique<GhostManager>(m_pacman, m_mapManager, m_sprite);
}
