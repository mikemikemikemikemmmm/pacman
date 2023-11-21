#pragma once
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
		
#include "../lib/raylib/include/raylib.h"
#include "gameStatus.h"
#include "global.h"
#include "utils.h"
#include "mapManager.h"
#include "objManager.h"
#include "obj/wall.h"
#include "obj/pacman.h"
class Game {
private:
    std::shared_ptr<MapManager> m_mapManager;
    std::shared_ptr<ObjManager> m_objManager;
    std::shared_ptr<Texture2D> m_sprite;
    std::shared_ptr<GameStatusManager> m_gameStatusManager;
    std::chrono::time_point<std::chrono::steady_clock> m_previousTime;
	long long m_lag = 0;
	void initGameWindow() {
		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pacman");
		SetTargetFPS(TARGET_FPS);
        m_sprite = std::make_shared<Texture2D>(LoadTexture("resources/pacman3.png"));
        m_mapManager = std::make_shared<MapManager>(defaultGameMap);
	};
    void initState() {
        m_previousTime =std::chrono::steady_clock::now();
        m_gameStatusManager= std::make_shared<GameStatusManager>();
    }
    void initObj() {
        const char wallChar = m_mapManager->tranMapTypeToChar(MapCellType::Wall);
        const char powerChar = m_mapManager->tranMapTypeToChar(MapCellType::Power);
        const auto wallList = std::make_shared<std::vector<WallObj>>();
        const auto powerList = std::make_shared<std::vector<PowerObj>>();
        for (int row = 0; row < m_mapManager->m_map.size(); row++) {
            for (int col = 0; col < m_mapManager->m_map[0].size(); col++) {
                if (m_mapManager->m_map[row][col] == wallChar) {
                    const int x = col * CELL_SIZE;
                    const int y = row * CELL_SIZE;
                    wallList->emplace_back(Position{ x,y }, m_sprite);
                }
                else if (m_mapManager->m_map[row][col] == powerChar) {
                    const int x = col * CELL_SIZE;
                    const int y = row * CELL_SIZE;
                    powerList->emplace_back(Position{ x,y }, m_sprite);
                }
            }
        }
        const auto pacmanStr = std::make_shared<PacmanObj>(
            PACMAN_START_POS,
            m_mapManager,
            m_sprite
        );
        m_objManager = std::make_shared<ObjManager>(m_gameStatusManager,m_mapManager, m_sprite, pacmanStr,wallList,powerList);
    }
    void handleInput() {
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
        };
    }
    void handleStartPlayGame() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        m_gameStatusManager->setGameStatus(GameStatusManager::GameStatus::Playing);
        auto ghostPtrList = m_objManager->m_ghostManager.m_ghostPtrList;

    }
	void handleGameLoop() {
        while(!WindowShouldClose()){
            const std::chrono::time_point<std::chrono::steady_clock> currentTime =
                std::chrono::steady_clock::now();
            const auto delta_time =
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_previousTime).count();
            m_lag += delta_time;
            m_previousTime += std::chrono::milliseconds(delta_time);

            while (m_lag >= FRAME_COST_MILLSECOND) {
                m_lag = 0;
                //if (m_gameStatusManager->gameStatus == GameStatusManager::GameStatus::Playing) {
                    handleInput();
                //}
                BeginDrawing();
                ClearBackground(BLACK);
                m_objManager->drawAllObj();
                EndDrawing();
            }
        }
	}
    void handleCloseWindow() {
        UnloadTexture(*m_sprite);
        CloseWindow();
    }
public:
	Game() {
		initGameWindow();
        initState();
        initObj();
        handleGameLoop();
        handleCloseWindow();
	}
};