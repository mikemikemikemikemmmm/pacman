#include "gameStatus.h"

bool GameStatusManager::isPlaying() const {
	return m_gameStatus == GameStatus::Playing;
}


bool GameStatusManager::isStart() const {
	return m_gameStatus == GameStatus::Starting;
}

bool GameStatusManager::isGameOver() const {
	return m_gameStatus == GameStatus::Gameover;
}

bool GameStatusManager::isGameWin() const {
	return m_gameStatus == GameStatus::Win;
}

GameStatusManager::GameStatus GameStatusManager::getGameStatus() const {
	return m_gameStatus;
}

void GameStatusManager::setGameStatus(const GameStatus& s) {
	m_gameStatus = s;
}

