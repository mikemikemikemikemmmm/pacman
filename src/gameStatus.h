#pragma once
#include <string>
#include <chrono>
#include <future>
class GameStatusManager {
public:
	bool isPlaying() const {
		return m_gameStatus == GameStatus::Playing;
	}
	bool isPaused() const {
		return m_gameStatus == GameStatus::Pause;
	}
	bool isStart() const {
		return m_gameStatus == GameStatus::Starting;
	}
	bool isGameOver() const {
		return m_gameStatus == GameStatus::Gameover;
	}
	bool isGameWin() const {
		return m_gameStatus == GameStatus::Win;
	}
	enum class GameStatus {
		Playing, Starting, Pause, Gameover, Win
	};
	GameStatus getGameStatus() const {
		return m_gameStatus;
	}
	void setGameStatus(const GameStatus& s) {
		m_gameStatus = s;
	};
private:
	GameStatus m_gameStatus = GameStatus::Starting;
};