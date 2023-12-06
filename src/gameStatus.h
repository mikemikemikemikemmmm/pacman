#pragma once
#include <string>
#include <chrono>
#include <future>
class GameStatusManager {
public:
	bool isPlaying() const;
	bool isStart() const;
	bool isGameOver() const;
	bool isGameWin() const;
	enum class GameStatus {
		Playing, Starting, Gameover, Win
	};
	GameStatus getGameStatus() const;
	void setGameStatus(const GameStatus& s);
private:
	GameStatus m_gameStatus = GameStatus::Starting;
};