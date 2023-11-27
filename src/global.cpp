#include "global.h"

//direction 
bool Direction::operator==(const Direction& other) const {
	return other.x == x && other.y == y;
}
bool Direction::operator!=(const Direction& other) const {
	return other.x != x || other.y != y;
}
Direction Direction::operator*(const int& val) const {
	return Direction{ this->x * val,this->y * val };
}
std::string Direction::getAxis()const {
	if (std::abs(this->x) > 0) {
		return "x";
	}
	else {
		return "y";
	}
}
std::string Direction::getType() const {
	if (this->x == 0 && this->y == 0) {
		return "stay";
	}
	else if (this->x == 0 && this->y > 0) {
		return "down";
	}
	else if (this->x == 0 && this->y < 0) {
		return "up";
	}
	else if (this->x < 0 && this->y == 0) {
		return "left";
	}
	else {
		return "right";
	}
}

//position

const bool Position::operator==(const Position& other) const {
	return this->x == other.x && this->y == other.y;
};
const bool Position::operator!=(const Position& other) const {
	return this->x != other.x || this->y != other.y;
};
Position Position::operator-(const Position& other) const {
	return Position{
		this->x - other.x,
		this->y - other.y };
}
Position Position::operator*(const int& val) const {
	return Position{
		this->x * val,
		this->y * val
	};
}
Position Position::operator+(const Direction& dir) const {
	return Position{
		this->x + dir.x,
		this->y + dir.y
	};
}
Position Position::operator+(const Position& pos) const {
	return Position{
		this->x + pos.x,
		this->y + pos.y
	};
}
Position* Position::operator+=(const Position& pos) {
	this->x += pos.x;
	this->y += pos.y;
	return this;
}
int Position::getDistance() const {
	return this->x * this->x + this->y * this->y;
}
Direction Position::tranToDir() const {
	const int total = this->x + this->y;
	return { this->x / total,this->y / total };
}
Position Position::flipByYAxis(const Position& axisPos)const {
	return Position{ 2 * axisPos.x - this->x,this->y };
}
Position Position::flipByXAxis(const Position& axisPos)const {
	return Position{ this->x,2 * axisPos.y - this->y };
}


//mapindex

bool MapIndex::operator==(const MapIndex& other) const {
	return this->x == other.x && this->y == other.y;
};
bool MapIndex::operator!=(const MapIndex& other) const {
	return this->x != other.x || this->y != other.y;
};
const MapIndex MapIndex::operator-(const MapIndex& other) const {
	return MapIndex{
		this->x - other.x,
		this->y - other.y
	};
};
int MapIndex::getDistance() const {
	return x + y;
}
Position MapIndex::getPosition() const {
	return Position{ this->x * CELL_SIZE,this->y * CELL_SIZE };
}