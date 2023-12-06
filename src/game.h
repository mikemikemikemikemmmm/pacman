#pragma once
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <ctime> 
#include <forward_list>
#include <unordered_set>
#include "../lib/raylib/include/raylib.h"
#include "objManager.h"
class Game {
private:
	Texture2D m_sprite;
	Font font;
	GameStatusManager m_gameStatusManager;
	MapManager m_mapManager{ defaultGameMap };
	std::unique_ptr<ObjManager> m_objManager;
	std::chrono::time_point<std::chrono::steady_clock> m_previousTime;
	AudioManager m_audioManager;
	long long m_lag = 0;
	void initGameWindow() ;
	void initStatus();
	void initObj();
	void renderText(const std::vector<std::string>& contentList);
	void handlePlayMusic(const long long& lag);
	void handleInput();
	void handleRenderText();
	void handleGameLoop();
	void handleCloseWindow();
	void handleNewGame();
public:
	Game();
};