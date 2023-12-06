#include "objManager.h"
void ObjManager::handleKeyPressed(const Direction& dir) {
	m_pacman.setNextTurnDirection(dir);
}

void ObjManager::checkEvent() {
	checkPacmanEatPower();
	checkPacmanMeetGhost();
	checkPacmanEatFood();
	checkGameWin();
}

void ObjManager::drawAllObj() {
	const bool& isGameOver = m_gameStatusManager.isGameOver();
	const bool& isPlaying = m_gameStatusManager.isPlaying();
	if (isPlaying) {
		checkEvent();
	}
	for (const Position& wallPos : m_wallPositionSet) {
		m_wall.drawSelf(true, wallPos);
	};
	for (const Position& powerPos : m_powerPositionSet) {
		m_power.drawSelf(true, powerPos);
	};
	for (const Position& foodPos : m_foodPositionSet) {
		m_food.drawSelf(true, foodPos);
	};
	if (!isGameOver) {
		m_ghostManager->drawAllGhost(isPlaying);
	}
	m_pacman.drawSelf(isPlaying || isGameOver, m_pacman.m_pos);
}

bool ObjManager::checkTouchByTwoPosition(const Position& p1, const Position& p2) {
	if (p1.x == p2.x) {
		return std::abs(p1.y - p2.y) <= OBJ_MEET_MAX_DISTANCE;
	}
	else if (p1.y == p2.y) {
		return std::abs(p1.x - p2.x) <= OBJ_MEET_MAX_DISTANCE;
	}
	else if (
		(
			std::abs(p1.x - p2.x) +
			std::abs(p1.y - p2.y)
			) <= OBJ_MEET_MAX_DISTANCE
		) {
		return true;
	}
	else {
		return false;
	}
}

void ObjManager::checkPacmanEatPower() {
	std::optional<Position> powerPosBeEaten;
	for (auto& powerPos : m_powerPositionSet) {
		if (this->checkTouchByTwoPosition(powerPos, m_pacman.m_pos)) {
			powerPosBeEaten = powerPos;
			break;
		}
	}
	if (powerPosBeEaten.has_value()) {
		m_audioManager.setKeepPlayMusicForSecond("eatPower", GHOST_panic_SECOND + GHOST_panicEnd_SECOND);
		m_powerPositionSet.erase(powerPosBeEaten.value());
		m_ghostManager->handlePacmanEatPower();
	}
}

void ObjManager::checkPacmanMeetGhost() {
	auto& ghostList = m_ghostManager->m_ghostList;
	for (auto& g : ghostList) {
		if (this->checkTouchByTwoPosition((*g).m_pos, m_pacman.m_pos)) {
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

void ObjManager::checkPacmanEatFood()
{
	std::optional<Position> foodPosBeEaten;
	for (auto& foodPos : m_foodPositionSet) {
		if (this->checkTouchByTwoPosition(foodPos, m_pacman.m_pos)) {
			foodPosBeEaten = foodPos;
			break;
		}
	}
	if (foodPosBeEaten.has_value()) {
		m_audioManager.playMusic("eatFood");
		m_foodPositionSet.erase(foodPosBeEaten.value());
	}
}

void ObjManager::handleGameOver() {
	m_pacman.setCurrentAnimation(PacmanObj::m_animationDataMap.at("die"));
	m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Gameover);
	m_audioManager.stopPlayingAllMusic();
	m_audioManager.cleanKeepPlayList();
	m_audioManager.playMusic("gameOver");
}

void ObjManager::handleGameWin() {
	m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Win);
	m_audioManager.stopPlayingAllMusic();
	m_audioManager.cleanKeepPlayList();
	m_audioManager.playMusic("gameWin");
}

void ObjManager::checkGameWin()
{
	if (m_powerPositionSet.size() == 0&&
		m_foodPositionSet.size() == 0
		) {
		handleGameWin();
	}
}

ObjManager::ObjManager(
	AudioManager& audioManager,
	GameStatusManager& gameStatusManager,
	const MapManager& mapManager,
	const Texture2D& sprite,
	PositionSet& wallPosSet,
	PositionSet& powerPosSet,
	PositionSet& foodPosSet
) :
	m_audioManager(audioManager),
	m_gameStatusManager(gameStatusManager),
	m_mapManager(mapManager),
	m_sprite(sprite),
	m_wallPositionSet(std::move(wallPosSet)),
	m_powerPositionSet(std::move(powerPosSet)),
	m_foodPositionSet(std::move(foodPosSet)),
	m_wall({ Position{0,0},sprite }),
	m_power({ Position{0,0},sprite }),
	m_food({ Position{0,0},sprite }),
	m_pacman(PACMAN_START_POS, mapManager, sprite)
{
	m_ghostManager = std::make_unique<GhostManager>(m_pacman, m_mapManager, m_sprite);
}
