#pragma once
#include <raylib.h>
#include <array>
#include <unordered_map>
#include <string>
#include <iostream>
#define LOG(e,a) std::cout <<e<<" , " << a <<std::endl;
//system
constexpr int CELL_SIZE = 30;
constexpr int SPRITE_SIZE = 20;
constexpr int SPRITE_START_X = ((CELL_SIZE - SPRITE_SIZE) / 2);
constexpr int SPRITE_START_Y = ((CELL_SIZE - SPRITE_SIZE) / 2);
constexpr unsigned char MAP_HEIGHT = 32;
constexpr unsigned char MAP_WIDTH = 28;
constexpr unsigned int SCREEN_HEIGHT = MAP_HEIGHT* CELL_SIZE;
constexpr unsigned int SCREEN_WIDTH = MAP_WIDTH * CELL_SIZE;
constexpr unsigned char TARGET_FPS = 60;
constexpr unsigned int FRAME_COST_MILLSECOND = 30;

//speed , must can be indivde by CELL_SIZE
constexpr int PACMAN_SPEED = 6;

//map
typedef std::array<std::array<char, MAP_WIDTH>, MAP_HEIGHT> MapType;
enum class MapCellType :char {
    Wall = 'w',
    Food = 's',
    Power = 'b',
    Empty = 'e'
};
constexpr MapType defaultGameMap = {{
    {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','w','w','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','b','w','w','w','w','s','w','w','w','w','w','s','w','w','s','w','w','w','w','w','s','w','w','w','w','b','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','s','w','w','s','w','w','w','w','w','w','w','w','s','w','w','s','w','w','w','w','s','w'},
    {'w','s','w','w','w','w','s','w','w','s','w','w','w','w','w','w','w','w','s','w','w','s','w','w','w','w','s','w'},
    {'w','s','s','s','s','s','s','w','w','s','s','s','s','w','w','s','s','s','s','w','w','s','s','s','s','s','s','w'},
    {'w','w','w','w','w','w','s','w','w','w','w','w','e','w','w','e','w','w','w','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','w','w','w','e','w','w','e','w','w','w','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','e','e','e','e','e','e','e','e','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','e','e','e','e','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','e','e','e','e','e','s','e','e','e','w','w','e','e','e','e','w','w','e','e','e','s','e','e','e','e','e','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','e','e','e','e','e','e','e','e','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','w','w','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','b','s','s','w','w','s','s','s','s','s','s','s','e','e','s','s','s','s','s','s','s','w','w','s','s','b','w'},
    {'w','w','w','s','w','w','s','w','w','s','w','w','w','w','w','w','w','w','s','w','w','s','w','w','s','w','w','w'},
    {'w','w','w','s','w','w','s','w','w','s','w','w','w','w','w','w','w','w','s','w','w','s','w','w','s','w','w','w'},
    {'w','s','s','s','s','s','s','w','w','s','s','s','s','w','w','s','s','s','s','w','w','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','w','w','w','w','w','w','s','w','w','s','w','w','w','w','w','w','w','w','w','w','s','w'},
    {'w','s','w','w','w','w','w','w','w','w','w','w','s','w','w','s','w','w','w','w','w','w','w','w','w','w','s','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
}};

//direction
struct Direction {
    int x;
    int y;
    bool operator==(const Direction& other) {
        return other.x == x && other.y == y;
    }
    bool operator!=(const Direction& other) {
        return other.x != x || other.y != y;
    }
};
constexpr Direction directionUp{ 0,-1 };
constexpr Direction directionDown{ 0,1 };
constexpr Direction directionRight{ 1,0 };
constexpr Direction directionLeft{ -1,0 };
constexpr Direction directionStay{0,0};
//animation
struct AnimationData {
    float startSpriteX;
    float startSpriteY;
    unsigned short totalFrame;
    bool isReapted;
};
typedef std::unordered_map<std::string,const AnimationData> AnimationDataMap;
struct MapIndex {
	int x;
	int y;
    bool operator==(const MapIndex& other) {
        return this->x == other.x && this->y == other.y;
    };
    friend std::ostream& operator<<(std::ostream& os, const MapIndex& mapIndex) {
        os << "X:" << mapIndex.x << " , Y:" << mapIndex.y;
        return os;
    }
};