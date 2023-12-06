#include "game.h"
Game::Game() {
	initGameWindow();
	handleNewGame();
}
void Game::initGameWindow() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pacman");
	SetWindowMinSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetTargetFPS(TARGET_FPS);
	m_sprite = LoadTexture("resources/pacman3.png");
	font = LoadFont("resources/font2.ttf");
	std::srand(static_cast<unsigned int>(time(NULL)));
};
void Game::initStatus() {
	m_previousTime = std::chrono::steady_clock::now();
	m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Starting);
	m_audioManager.cleanKeepPlayList();
	m_audioManager.stopPlayingAllMusic();
}
void Game::handlePlayMusic(const long long& lag)
{
	if (m_gameStatusManager.isPlaying()) {
		m_audioManager.playKeepMusic(lag);
		m_audioManager.playMusic("background");
	}
	else {
		m_audioManager.stopPlayingMusic("background");
	}
}
void Game::initObj() {
	const char wallChar = m_mapManager.tranMapTypeToChar(MapCellType::Wall);
	const char powerChar = m_mapManager.tranMapTypeToChar(MapCellType::Power);
	const char foodChar = m_mapManager.tranMapTypeToChar(MapCellType::Food);
	PositionSet foodPosSet;
	PositionSet wallPosSet;
	PositionSet powerPosSet;
	const int mapRow = static_cast<int>(m_mapManager.m_map.size());
	const int mapCol = static_cast<int>(m_mapManager.m_map[0].size());
	for (int row = 0; row < mapRow; row++) {
		for (int col = 0; col < mapCol; col++) {
			const int x = col * CELL_SIZE;
			const int y = row * CELL_SIZE;
			if (m_mapManager.m_map[row][col] == wallChar) {
				wallPosSet.emplace(Position{ x, y });
			}
			else if (m_mapManager.m_map[row][col] == powerChar) {
				powerPosSet.emplace(Position{ x, y });
			}
			else if (m_mapManager.m_map[row][col] == foodChar) {
				foodPosSet.emplace(Position{ x, y });
			}
		}
	}
	m_objManager = std::make_unique<ObjManager>(
		m_audioManager,
		m_gameStatusManager,
		m_mapManager,
		m_sprite,
		wallPosSet,
		powerPosSet,
		foodPosSet
	);
}
void Game::handleInput() {
	if (m_gameStatusManager.isPlaying()) {
		if (IsKeyPressed(KEY_RIGHT)) {
			m_objManager->handleKeyPressed(directionRight);
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			m_objManager->handleKeyPressed(directionLeft);
		}
		else if (IsKeyPressed(KEY_UP)) {
			m_objManager->handleKeyPressed(directionUp);
		}
		else if (IsKeyPressed(KEY_DOWN)) {
			m_objManager->handleKeyPressed(directionDown);
		}
	}
	else if (m_gameStatusManager.isGameWin() || m_gameStatusManager.isGameOver()) {
		if (IsKeyPressed(KEY_ENTER)) {
			handleNewGame();
		}
	};
}
void Game::handleRenderText() {
	if (m_gameStatusManager.isStart()) {
		renderText({ "READY!" });
	}
	else if (m_gameStatusManager.isGameWin()) {
		renderText({ "YOU WIN!","","PRESS ENTER TO START","", "A NEW GAME" });
	}
	else if (m_gameStatusManager.isGameOver()) {
		renderText({ "GAME OVER!","","PRESS ENTER TO START","","A NEW GAME" });
	}
}
void Game::handleGameLoop() {
	std::thread t([this]() {
		std::this_thread::sleep_for(std::chrono::seconds(GAME_START_READY_WAIT_SECOND));
		this->m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Playing);
		});
	t.detach();
	m_audioManager.playMusic("gameStart");
	while (!WindowShouldClose()) {
		const std::chrono::time_point<std::chrono::steady_clock> currentTime =
			std::chrono::steady_clock::now();
		const auto delta_time =
			std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_previousTime).count();
		m_lag += delta_time;
		m_previousTime += std::chrono::milliseconds(delta_time);
		while (m_lag >= FRAME_COST_MILLSECOND) {
			handlePlayMusic(m_lag);
			m_lag = 0;
			handleInput();
			BeginDrawing();
			ClearBackground(BLACK);
			m_objManager->drawAllObj();
			handleRenderText();
			EndDrawing();
		}
	}
	if (WindowShouldClose()) {
		handleCloseWindow();
	}
}
void Game::handleCloseWindow() {
	UnloadTexture(m_sprite);
	UnloadFont(font);
	CloseWindow();
}
void Game::handleNewGame() {
	initStatus();
	initObj();
	handleGameLoop();
}
void Game::renderText(const std::vector<std::string>& contentList) {
	const int contentListSize = static_cast<int>(contentList.size());
	for (int i = 0; i < contentListSize; i++) {
		DrawTextEx(font, contentList[i].c_str(), tranPosToVec2({
			MAP_CENTER_POS.x - TEXT_SIZE * static_cast<int>(contentList[i].size() / 3),
			MAP_CENTER_POS.y - TEXT_SIZE * (contentListSize - i - 1),
			}), TEXT_SIZE, 0, YELLOW);
	}
}
