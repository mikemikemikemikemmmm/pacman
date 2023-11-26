#pragma once
#include <unordered_map>
#include <string>
#include "../lib/raylib/include/raylib.h"
class AudioManager {
private:
	std::unordered_map<std::string, Sound> m_soundMap;
	std::string m_currentPlayingSoundName;
public:
	void playMusic(const std::string& musicName) {
		if (musicName == m_currentPlayingSoundName) {
			return;
		}
		if (isPlayingMusic()) {
			stopMusic();
		}
		Sound& targetSound = m_soundMap.at(musicName);
		m_currentPlayingSoundName = musicName;
		PlaySound(targetSound);
	}
	bool isPlayingMusic() const {
		return m_currentPlayingSoundName != "";
	}
	void stopMusic() {
		if (!isPlayingMusic()) {
			return;
		}
		const Sound& currentSound = m_soundMap.at(m_currentPlayingSoundName);
		StopSound(currentSound);
		m_currentPlayingSoundName = "";
	}
	AudioManager() {
		InitAudioDevice();
		m_soundMap ={
			{"gameStart",LoadSound("resources/gameStart.wav")},
			{"eatGhost",LoadSound("resources/eatGhost.wav")},
			{"die",LoadSound("resources/die.wav")},
			{"gameWin",LoadSound("resources/gameWin.wav")},
			{"pacmanRun",LoadSound("resources/pacmanRun.wav")},
		};
	}
	~AudioManager() {
		stopMusic();
		for (auto& soundPair : m_soundMap) {
			UnloadSound(soundPair.second);
		}
		CloseAudioDevice();
	}
};