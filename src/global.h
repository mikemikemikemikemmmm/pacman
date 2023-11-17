#pragma once
#include "../lib/raylib/include/raylib.h"
#include <array>
#include <unordered_map>
#include <string>
#include <iostream>
#include <future>
#include <chrono>
#define LOG(e,a) std::cout <<e<<" , " << a <<std::endl;

//direction
struct Direction {
    int x;
    int y;
    bool operator==(const Direction& other) const{
        return other.x == x && other.y == y;
    }
    bool operator!=(const Direction& other) const{
        return other.x != x || other.y != y;
    }
    Direction operator*(const int& val) const{
        return Direction{ this->x * val,this->y * val };
    }
    friend std::ostream& operator<<(std::ostream& os, const Direction& dir){
        os << "X:" << dir.x << " , Y:" << dir.y;
        return os;
    }
    const Direction mutiply (const int& val) const{
        return Direction{ this->x * val,this->y * val };
    }
};
constexpr Direction directionUp{ 0,-1 };
constexpr Direction directionDown{ 0,1 };
constexpr Direction directionRight{ 1,0 };
constexpr Direction directionLeft{ -1,0 };
constexpr Direction directionStay{ 0,0 };

struct Position {
    int x;
    int y;
    const bool operator==(const Position& other) const{
        return this->x == other.x && this->y == other.y;
    };
    const bool operator!=(const Position& other) const{
        return this->x != other.x || this->y != other.y;
    };
    friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
        os << "X:" << pos.x << " , Y:" << pos.y;
        return os;
    }
    Position operator-(const Position& other) const{
        return Position{
            this->x - other.x,
            this->y - other.y };
    }
    Position operator*(const int& val) const {
        return Position{
            this->x * val,
            this->y * val
        };
    }
    Position operator+(const Direction& dir) const {
        return Position{
            this->x + dir.x,
            this->y + dir.y
        };
    }
    int getDistance() const{
        return this->x * this->x + this->y * this->y;
    }
};

//system
constexpr int CELL_SIZE{ 30 };
constexpr int SPRITE_SIZE{ 20 };
constexpr int SPRITE_START_X{ ((CELL_SIZE - SPRITE_SIZE) / 2) };
constexpr int SPRITE_START_Y { ((CELL_SIZE - SPRITE_SIZE) / 2)};
constexpr unsigned char MAP_HEIGHT{ 32 };
constexpr unsigned char MAP_WIDTH {27};
constexpr unsigned int SCREEN_HEIGHT { MAP_HEIGHT* CELL_SIZE };
constexpr unsigned int SCREEN_WIDTH { MAP_WIDTH * CELL_SIZE };
constexpr unsigned char TARGET_FPS{ 60 };
constexpr unsigned int FRAME_COST_MILLSECOND{ 30 };
constexpr int OBJ_MEET_MAX_DISTANCE{ 6 };



//speed , must can be indivde by CELL_SIZE
constexpr int PACMAN_SPEED{ 6 };
constexpr int GHOST_NORMAL_SPEED {6};
constexpr int GHOST_PANIC_SPEED{ 6 };
constexpr int GHOST_DIE_SPEED{ 10 };

//map
class MapIndex {
public:
    int x;
    int y;
    bool operator==(const MapIndex& other) const{
        return this->x == other.x && this->y == other.y;
    };
    bool operator!=(const MapIndex& other) const {
        return this->x != other.x || this->y != other.y;
    };
    const MapIndex operator-(const MapIndex& other) const{
        return MapIndex{
            this->x-other.x,
            this->y-other.y
        };
    };
    friend std::ostream& operator<<(std::ostream& os, const MapIndex& mapIndex) {
        os << "X:" << mapIndex.x << " , Y:" << mapIndex.y;
        return os;
    }
    int getDistance() const {
        return x + y;
    }
    Position getPosition() const {
        return Position{ this->x * CELL_SIZE,this->y * CELL_SIZE };
    }
};
typedef std::array<std::array<char, MAP_WIDTH>, MAP_HEIGHT> MapType;
enum class MapCellType :char {
    Wall = 'w',
    Food = 's',
    Power = 'b',
    Empty = 'e',
    Door = 'd'
};
constexpr MapType defaultGameMap {{/////////////////////////
    {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','w','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','b','w','w','w','w','s','w','w','w','w','w','s','w','s','w','w','w','w','w','s','w','w','w','w','b','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','s','w','w','s','w','w','w','w','w','w','w','s','w','w','s','w','w','w','w','s','w'},
    {'w','s','w','w','w','w','s','w','w','s','w','w','w','w','w','w','w','s','w','w','s','w','w','w','w','s','w'},
    {'w','s','s','s','s','s','s','w','w','s','s','s','s','w','s','s','s','s','w','w','s','s','s','s','s','s','w'},
    {'w','w','w','w','w','w','s','w','w','w','w','w','e','w','e','w','w','w','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','w','w','w','e','w','e','w','w','w','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','e','e','e','e','e','e','e','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','d','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','e','e','e','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','e','e','e','w','w','e','e','e','w','w','e','e','e','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','e','e','e','e','e','e','e','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','w','w','w','w','w','s','w','w','e','w','w','w','w','w','w','w','e','w','w','s','w','w','w','w','w','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','w','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','s','w','w','w','w','s','w','w','w','w','w','s','w','s','w','w','w','w','w','s','w','w','w','w','s','w'},
    {'w','b','s','s','w','w','s','s','s','s','s','s','s','e','s','s','s','s','s','s','s','w','w','s','s','b','w'},
    {'w','w','w','s','w','w','s','w','w','s','w','w','w','w','w','w','w','s','w','w','s','w','w','s','w','w','w'},
    {'w','w','w','s','w','w','s','w','w','s','w','w','w','w','w','w','w','s','w','w','s','w','w','s','w','w','w'},
    {'w','s','s','s','s','s','s','w','w','s','s','s','s','w','s','s','s','s','w','w','s','s','s','s','s','s','w'},
    {'w','s','w','w','w','w','w','w','w','w','w','w','s','w','s','w','w','w','w','w','w','w','w','w','w','s','w'},
    {'w','s','w','w','w','w','w','w','w','w','w','w','s','w','s','w','w','w','w','w','w','w','w','w','w','s','w'},
    {'w','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','w'},
    {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
}};


//animation
constexpr int ANIMATION_MAX_COUNTER = 5;
struct AnimationData {
    float startSpriteX;
    float startSpriteY;
    unsigned short totalFrame;
    bool isReapted;
};
typedef std::unordered_map<std::string,const AnimationData> AnimationDataMap;
struct SpriteXY {
    float x;
    float y;
};

//pacman
constexpr Position PACMAN_START_POS  { 13 * CELL_SIZE,23 * CELL_SIZE };

//ghost 
constexpr Position BLINKY_START_POS{12 * CELL_SIZE , 14 * CELL_SIZE };
constexpr Position PINKY_START_POS{12 * CELL_SIZE , 14 * CELL_SIZE };
constexpr Position INKY_START_POS{13 * CELL_SIZE ,  14* CELL_SIZE };
constexpr Position CLYDE_START_POS{14 * CELL_SIZE , 14* CELL_SIZE };
//door
constexpr MapIndex DoorIndex{ 13 ,15  };
const Position DoorPos = DoorIndex.getPosition();