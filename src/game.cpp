#include "game.h"
Game::Game() {
	initGameWindow();
	handleNewGame();
}
void Game::initGameWindow() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pacman");
	SetTargetFPS(TARGET_FPS);
	m_sprite = LoadTexture("resources/pacman3.png");
	font = LoadFont("resources/font2.ttf");
	std::srand(static_cast<unsigned int>(time(NULL)));
};
void Game::initStatus() {
	m_previousTime = std::chrono::steady_clock::now();
	m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Starting);
	m_audioManager.stopPlayingMusic();
}
void Game::initObj() {
	const char wallChar = m_mapManager.tranMapTypeToChar(MapCellType::Wall);
	const char powerChar = m_mapManager.tranMapTypeToChar(MapCellType::Power);
	auto wallList = std::vector<WallObj>();
	auto powerList = std::forward_list<PowerObj>();
	auto powerListIt = powerList.before_begin();
	for (int row = 0; row < m_mapManager.m_map.size(); row++) {
		for (int col = 0; col < m_mapManager.m_map[0].size(); col++) {
			if (m_mapManager.m_map[row][col] == wallChar) {
				const int x = col * CELL_SIZE;
				const int y = row * CELL_SIZE;
				wallList.emplace_back(Position{ x,y }, m_sprite);
			}
			else if (m_mapManager.m_map[row][col] == powerChar) {
				const int x = col * CELL_SIZE;
				const int y = row * CELL_SIZE;
				powerList.emplace_after(powerListIt, Position{ x,y }, m_sprite);
			}
		}
	}
	const PacmanObj pacman{
		PACMAN_START_POS,
		m_mapManager,
		m_sprite
	};
	m_objManager = std::make_unique<ObjManager>(
		m_audioManager,
		m_gameStatusManager,
		m_mapManager,
		m_sprite,
		pacman,
		wallList,
		powerList
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
		else if (IsKeyPressed(KEY_ENTER)) {
			m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Pause);
		}
	}
	else if (m_gameStatusManager.isPaused()) {
		if (IsKeyPressed(KEY_ENTER)) {
			m_gameStatusManager.setGameStatus(GameStatusManager::GameStatus::Playing);
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
	else if (m_gameStatusManager.isPaused()) {
		renderText({ "PAUSED!","","PRESS ENTER","","TO PLAY" });
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
void Game::renderText(const std::vector<std::string> contentList) {
	const int contentListSize = static_cast<int>(contentList.size());
	for (int i = 0; i < contentListSize; i++) {
		DrawTextEx(font, contentList[i].c_str(), tranPosToVec2({
			MAP_CENTER_POS.x - TEXT_SIZE * static_cast<int>(contentList[i].size() / 3),
			MAP_CENTER_POS.y - TEXT_SIZE * (contentListSize - i - 1),
			}), TEXT_SIZE, 0, YELLOW);
	}
}