#pragma once
#include <unordered_map>
#include <string>
#include "../lib/raylib/include/raylib.h"
class AudioManager {
private:
	std::unordered_map<std::string, Sound> m_soundMap;
	std::string m_currentPlayingSoundName = "";
public:
	void playMusic(const std::string& musicName) {
		const Sound& targetSound = m_soundMap.at(musicName);
		if (musicName == m_currentPlayingSoundName && IsSoundPlaying(targetSound)) {
			return;
		}
		stopPlayingMusic();
		m_currentPlayingSoundName = musicName;
		PlaySound(targetSound);
	}
	void stopPlayingMusic() {
		if (m_currentPlayingSoundName == "") {
			return;
		}
		const Sound& currentSound = m_soundMap.at(m_currentPlayingSoundName);
		if (!IsSoundPlaying(currentSound)) {
			return;
		}
		StopSound(currentSound);
		m_currentPlayingSoundName = "";
	}
	AudioManager() {
		InitAudioDevice();
		m_soundMap = {
			{"gameStart",LoadSound("resources/gameStart.wav")},
			{"eatGhost",LoadSound("resources/eatGhost.wav")},
			{"gameOver",LoadSound("resources/gameOver.wav")},
			{"gameWin",LoadSound("resources/gameWin.wav")},
			{"pacmanRun",LoadSound("resources/pacmanRun.wav")},
			{"eatPower",LoadSound("resources/eatPower.wav")},
		};
	}
	~AudioManager() {
		stopPlayingMusic();
		for (auto& soundPair : m_soundMap) {
			UnloadSound(soundPair.second);
		}
		CloseAudioDevice();
	}
};