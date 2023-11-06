
#include "raylib.h"
#include "global.h"
#include "utils.h"
#include "gameMap.h"
#include "obj/wall.h"
#include "obj/pacman.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pacman");
    SetTargetFPS(TARGET_FPS);
    Texture2D sprite = LoadTexture("resources/pacman3.png");
    std::chrono::time_point<std::chrono::steady_clock> previousTime =
        std::chrono::steady_clock::now();
    float currentFrameIndex = 0;
    float totalFrameIndex = 10;
    long long lag = 0;
    int posX = CELL_SIZE;
    int posY = CELL_SIZE ;
    GameMapManager gameMapManager={ defaultGameMap };
    PacmanObj pacman= { posX,posY ,&sprite,&gameMapManager };
    std::vector<WallObj> wallList;
    for (int row = 0; row < gameMapManager.m_map.size(); row++) {
        for (int col = 0; col < gameMapManager.m_map[0].size(); col++) {
            if (gameMapManager.m_map[row][col] == 'w') {
                int x = col * CELL_SIZE;
                int y = row * CELL_SIZE;
                wallList.emplace_back(x, y, &sprite);
            }
        }
    }
    while (!WindowShouldClose())  
    {
        std::chrono::time_point<std::chrono::steady_clock> currentTime =
            std::chrono::steady_clock::now();
        auto delta_time = 
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-previousTime).count();
        lag += delta_time;
        previousTime += std::chrono::milliseconds(delta_time);
        while (lag >= FRAME_COST_MILLSECOND) {
            if (IsKeyPressed(KEY_RIGHT)) {
                pacman.setNextTurnDirection(directionRight);
            }
            else if (IsKeyPressed(KEY_LEFT)) {
                pacman.setNextTurnDirection(directionLeft);
            }
            else if (IsKeyPressed(KEY_UP)) {
                pacman.setNextTurnDirection(directionUp);
            }
            else if (IsKeyPressed(KEY_DOWN)) {
                pacman.setNextTurnDirection(directionDown);
            };
            lag -= FRAME_COST_MILLSECOND;
            BeginDrawing();
            ClearBackground(BLACK);
            pacman.drawSelf();
            for (auto w : wallList) {
                w.drawSelf();
            };
            EndDrawing();
        }
    }
    UnloadTexture(sprite);
    CloseWindow();             
    return 0;
}