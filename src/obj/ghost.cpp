#include <unordered_map>
#include <string>
#include "ghost.h"
const std::unordered_map<GhostObj::GhostColor, const Position> GhostObj::m_startPosMap{
		{
			GhostObj::GhostColor::blinky ,
			BLINKY_START_POS
		},
		{
			GhostObj::GhostColor::pinky ,
			PINKY_START_POS
		},
		{
			GhostObj::GhostColor::inky ,
			INKY_START_POS
		},
		{
			GhostObj::GhostColor::clyde ,
			CLYDE_START_POS
		}
};
const std::unordered_map<GhostObj::GhostColor, const AnimationDataMap >GhostObj::m_animationDataMap{
		{
			GhostObj::GhostColor::blinky,
			{
				{"normal",AnimationData{0,80,8,true}},
				{"die",AnimationData{0,200,4,true}},
				{"panic",AnimationData{0,160,2,true}},
				{"panicEnd",AnimationData{20,160,2,true}},
			}
		},
		{
			GhostObj::GhostColor::pinky,
			{
				{"normal",AnimationData{0,100,8,true}},
				{"die",AnimationData{0,200,4,true}},
				{"panic",AnimationData{0,160,2,true}},
				{"panicEnd",AnimationData{20,160,2,true}},
			}
		},
		{
			GhostObj::GhostColor::inky,
			{
				{"normal",AnimationData{0,120,8,true}},
				{"die",AnimationData{0,200,4,true}},
				{"panic",AnimationData{0,160,2,true}},
				{"panicEnd",AnimationData{20,160,2,true}},
			}
		},
		{
			GhostObj::GhostColor::clyde,
			{
				{"normal",AnimationData{0,140,8,true}},
				{"die",AnimationData{0,200,4,true}},
				{"panic",AnimationData{0,160,2,true}},
				{"panicEnd",AnimationData{20,160,2,true}},
			}
		}
};
const std::unordered_map<GhostObj::AnimationStatus, std::string>GhostObj::m_animationNameMap{
		{
			GhostObj::AnimationStatus::normal,"normal"
		},
		{
			GhostObj::AnimationStatus::die,"die"
		},
		{
			GhostObj::AnimationStatus::panic,"panic"
		},
		{
			GhostObj::AnimationStatus::panicEnd,"panicEnd"
		},
};

