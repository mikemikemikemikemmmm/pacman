#pragma once
#include "../lib/raylib/include/raylib.h"
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <future>
#include <chrono>
#define LOG(e) std::cout <<e<<std::endl;
#define LOG2(e,a) std::cout <<e<<" , " << a <<std::endl;
//system
constexpr int CELL_SIZE = 30;
constexpr int SPRITE_SIZE = 20;
constexpr int MAP_HEIGHT = 30;
constexpr int MAP_WIDTH = 27;
constexpr int MAP_START_Y = 0;
constexpr int MAP_START_X = 0;
constexpr int MAP_MAX_X = MAP_WIDTH * CELL_SIZE;
constexpr int MAP_MAX_Y = MAP_HEIGHT * CELL_SIZE;
constexpr int SCREEN_HEIGHT = MAP_START_Y+(MAP_HEIGHT - 1) * CELL_SIZE;
constexpr int SCREEN_WIDTH = MAP_START_X+MAP_WIDTH * CELL_SIZE;
constexpr int TARGET_FPS = 60;
constexpr int FRAME_COST_MILLSECOND = 30;
constexpr int TEXT_SIZE = 50;
constexpr int GAME_START_READY_WAIT_SECOND = 4;
//speed , must be divisible by CELL_SIZE
constexpr int PACMAN_SPEED = 6;
constexpr int GHOST_SPEED = 6;
constexpr int OBJ_MEET_MAX_DISTANCE = GHOST_SPEED + PACMAN_SPEED;

//direction
struct Direction {
	int x;
	int y;
	bool operator==(const Direction& other) const;
	bool operator!=(const Direction& other) const;
	Direction operator*(const int& val) const;
	friend std::ostream& operator<<(std::ostream& os, const Direction& dir) {
		os << dir.getType();
		return os;
	}
	std::string getAxis()const;
	std::string getType() const;
};
constexpr Direction directionUp{ 0,-1 };
constexpr Direction directionDown{ 0,1 };
constexpr Direction directionRight{ 1,0 };
constexpr Direction directionLeft{ -1,0 };
constexpr Direction directionStay{ 0,0 };
const std::array<Direction, 4> fourDirectionArray{ directionUp, directionDown, directionRight, directionLeft };


//position
struct Position {
	int x;
	int y;
	const bool operator==(const Position& other) const;
	const bool operator!=(const Position& other) const;
	Position operator-(const Position& other) const;
	Position operator*(const int& val) const;
	Position operator+(const Direction& dir) const;
	Position operator+(const Position& pos) const;
	Position* operator+=(const Position& pos);
	int getDistance() const;
	Direction tranToDir() const;
	Position flipByYAxis(const Position& axisPos)const;
	Position flipByXAxis(const Position& axisPos)const;
};

struct PositionHash {
	std::size_t operator()(const Position& p) const {
		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
	}
};
typedef std::unordered_set<Position, PositionHash> PositionSet;
constexpr Position MAP_START_POS{ MAP_START_X,MAP_START_Y };
//map
class MapIndex {
public:
	int x;
	int y;
	bool operator==(const MapIndex& other) const;
	bool operator!=(const MapIndex& other) const;
	const MapIndex operator-(const MapIndex& other) const;
	friend std::ostream& operator<<(std::ostream& os, const MapIndex& mapIndex) {
		os << "X:" << mapIndex.x << " , Y:" << mapIndex.y;
		return os;
	}
	int getDistance() const;
	Position getPosition() const;
};
typedef std::array<std::array<char, MAP_WIDTH>, MAP_HEIGHT> MapType;
enum class MapCellType :char {
	Wall = 'w',
	Food = 's',
	Power = 'b',
	Empty = 'e',
	Door = 'd'
};
constexpr MapType defaultGameMap{ {
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
	{'w','w','w','w','w','w','s','e','e','e','w','w','e','e','e','w','w','e','e','e','s','w','w','w','w','w','w'},
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
} };
const Position MAP_CENTER_POS = MapIndex{ MAP_WIDTH / 2 ,MAP_HEIGHT / 2 }.getPosition();

//animation
constexpr int ANIMATION_MAX_COUNTER = 5;
struct AnimationData {
	float startSpriteX;
	float startSpriteY;
	unsigned short totalFrame;
	bool isReapted;
	bool operator==(const AnimationData& other)const {
		return this->startSpriteX == other.startSpriteX &&
			this->startSpriteY == other.startSpriteY &&
			this->totalFrame == other.totalFrame &&
			this->isReapted == other.isReapted;
	};
};
typedef std::unordered_map<std::string, AnimationData> AnimationDataMap;
struct SpriteXY {
	float x;
	float y;
};

//pacman
constexpr Position PACMAN_START_POS{ 13 * CELL_SIZE,21 * CELL_SIZE };

//ghost 
constexpr Position BLINKY_START_POS{ 12 * CELL_SIZE , 13 * CELL_SIZE };
constexpr Position PINKY_START_POS{ 13 * CELL_SIZE , 13 * CELL_SIZE };
constexpr Position INKY_START_POS{ 13 * CELL_SIZE ,  13 * CELL_SIZE };
constexpr Position CLYDE_START_POS{ 14 * CELL_SIZE , 13 * CELL_SIZE };
constexpr int GHOST_stayAtStartPos_SECOND = 2;
constexpr int GHOST_panic_SECOND = 4;
constexpr int GHOST_panicEnd_SECOND = 4;

//door
constexpr MapIndex DoorIndex{ 13 ,12 };
const Position DoorPos = DoorIndex.getPosition();
constexpr MapIndex DoorExitIndex{ 13 ,11 };
const Position DoorExitPos = DoorExitIndex.getPosition();