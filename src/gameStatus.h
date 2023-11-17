#pragma once
#include <string>
#include <chrono>
#include <future>
class GameStatusManager {
public:
    enum class GameStatus {
        Playing,Starting,Pause,Gameover
    };
    GameStatus gameStatus = GameStatus::Starting;
    void setGameStatus(const GameStatus& s) {
        gameStatus = s;
    };
    GameStatusManager() {
    }
};