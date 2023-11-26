#pragma once
#include <unordered_map>
#include <algorithm> 
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include "animatedObj.h"
class GhostObj : public AnimatedObj {
public:
    const enum class MoveStatus {
        chase, die, panic, stayAtStartPos, goOutDoor
    };
    const enum class AnimationStatus {
        normal, die, panic, panicEnd,
    };
    const enum class GhostColor {
        blinky, pinky, inky, clyde
    };
    const GhostColor m_color;
    const Position m_startPos;
    AnimationStatus m_animationStatus = AnimationStatus::normal;
    MoveStatus m_moveStatus = MoveStatus::stayAtStartPos;
    Position m_targetPos = PACMAN_START_POS;
    bool isChase() const{
        return m_moveStatus == MoveStatus::chase;
    }
    void setTargetPos(const Position& pos) {
        if (m_targetPos == pos) {
            return;
        };
        m_targetPos = pos;
    }
    void setMoveStatus(const MoveStatus& nextStatus) {
        if (m_moveStatus == nextStatus) {
            return;
        };
        switch (m_moveStatus)
        {
        case MoveStatus::chase: {
            if (nextStatus == MoveStatus::die || nextStatus == MoveStatus::goOutDoor || nextStatus == MoveStatus::stayAtStartPos) {
                return;
            }
            break;
        }
        case MoveStatus::die: {
            if (nextStatus != MoveStatus::stayAtStartPos) {
                return;
            }
            break;
        }
        case MoveStatus::panic: {
            if (nextStatus == MoveStatus::stayAtStartPos || nextStatus == MoveStatus::goOutDoor) {
                return;
            }
            break;
        }
        case MoveStatus::stayAtStartPos: {
            if (nextStatus != MoveStatus::goOutDoor) {
                return;
            }
            break; }
        case MoveStatus::goOutDoor: {
            if (nextStatus != MoveStatus::chase) {
                return;
            }
            break;
        }
        }
        m_moveStatus = nextStatus;
    };
    void setAnimationStatus(const AnimationStatus& nextStatus) {
        if (m_animationStatus == nextStatus) {
            return;
        }
        switch (m_animationStatus)
        {
        case GhostObj::AnimationStatus::normal: {
            if (nextStatus == GhostObj::AnimationStatus::die ||
                nextStatus == GhostObj::AnimationStatus::panicEnd
                ) {
                return;
            }
            break;
        }
        case GhostObj::AnimationStatus::die: {
            if (nextStatus == GhostObj::AnimationStatus::panic ||
                nextStatus == GhostObj::AnimationStatus::panicEnd
                ) {
                return;
            }
            break;
        }
        case GhostObj::AnimationStatus::panic: {
            if (nextStatus == GhostObj::AnimationStatus::normal) {
                return;
            }
            break;
        }
        }
        m_animationStatus = nextStatus;
        auto animationName = m_animationNameMap.at(nextStatus);
        auto animationData = m_animationDataMap.at(m_color).at(animationName);
        setCurrentAnimation(animationData);
    };
    void drawSelf(const bool& needUpdate) override {
        const Vector2 positionVec2 = tranPosToVec2(m_pos+ SPRITE_START_POS);
        DrawTextureRec(m_sprite,m_rec, positionVec2,WHITE);
        if (needUpdate) {
            updatePosition();
            if (m_animateCounter >= ANIMATION_MAX_COUNTER) {
                updateAnimation();
                m_animateCounter = 0;
            }
            else {
                m_animateCounter += 1;
            }
        }
    };
    GhostObj(
        const GhostColor& color,
        const MapManager& mapManager,
        const Texture2D& sprite
        ) :
        m_color(color),
        m_startPos(m_startPosMap.at(color)),
        AnimatedObj(
            sprite,
            m_animationDataMap.at(color).at("normal"),
            mapManager,
            m_startPosMap.at(color),
            SpriteXY{ 
                m_animationDataMap.at(color).at("normal").startSpriteX,
                m_animationDataMap.at(color).at("normal").startSpriteY
            },
            GHOST_SPEED,
            directionStay
            )
    {
        setCanMoveDoor(true);
    };
private:
    const static std::unordered_map<AnimationStatus, std::string>
        m_animationNameMap;
    const static std::unordered_map<GhostColor, const Position>
        m_startPosMap;
    const static std::unordered_map<GhostColor, const AnimationDataMap>
        m_animationDataMap;
    int m_animateCounter = 0;
    static Direction getDirByAxisAndVal(const std::string& axis, const int& val) {
        if (axis == "y") {
            if (val > 0) {
                return directionDown;
            }
            return directionUp;
        }
        if (axis == "x") {
            if (val > 0) {
                return directionRight;
            }
            return directionLeft;
        }
        throw "qwe";
    }
    Direction getNextPositionDir() {
        const Position posDiff = m_targetPos - m_pos;
        const Direction curOppositeDir = m_currentDirection * -1;
        const Direction yDiffDir = getDirByAxisAndVal("y", posDiff.y);
        const Direction xDiffDir = getDirByAxisAndVal("x", posDiff.x);
        const bool canMoveByXDiffDir = m_mapManager.canMoveAtPosition(m_pos + xDiffDir, m_canMoveDoor) && curOppositeDir != xDiffDir;
        const bool canMoveByYDiffDir = m_mapManager.canMoveAtPosition(m_pos + yDiffDir, m_canMoveDoor) && curOppositeDir != yDiffDir;
        if (posDiff.x == 0 && canMoveByYDiffDir) {
            return yDiffDir;
        }
        if (posDiff.y == 0 && canMoveByXDiffDir) {
            return xDiffDir;
        }
        if (canMoveByXDiffDir && canMoveByYDiffDir) {
            int randomIndex = std::rand() % 2;
            if (randomIndex == 1) {
                return yDiffDir;
            }
            else {
                return xDiffDir;
            }
        }
        if (canMoveByXDiffDir) {
            return xDiffDir;
        }
        if (canMoveByYDiffDir) {
            return yDiffDir;
        }
        Direction priorityDir = directionStay;
        Direction secondaryDir = directionStay;
        std::string priorityAxis = std::abs(posDiff.y) > std::abs(posDiff.x) ? "x" : "y";
        for (const Direction& dir : fourDirectionArray) {
            if (m_mapManager.canMoveAtPosition(m_pos + dir, m_canMoveDoor) && dir != curOppositeDir) {
                if (dir.getAxis() == priorityAxis) {
                    priorityDir = dir;
                }
                else {
                    secondaryDir = dir;
                }
            }
        }
        if (priorityDir != directionStay) {
            return priorityDir;
        }
        else if (secondaryDir != directionStay) {
            return secondaryDir;
        }
        else {
            return curOppositeDir;
        }
    }
    void updatePosition() override {
        const Direction nextDir = getNextPositionDir();
        if (nextDir != m_currentDirection) {
            setCurDirection(nextDir);
        }
        const Position nextPos{
            m_pos.x + m_speed * nextDir.x,
            m_pos.y + m_speed * nextDir.y
        };
        setPosition(nextPos);
    };
};


