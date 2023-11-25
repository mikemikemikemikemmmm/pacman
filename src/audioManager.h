#pragma once
#include <unordered_map>
#include <string>
#include "../lib/raylib/include/raylib.h"
class AudioManager {
private:
	std::unordered_map<std::string, Music > m_soundMap;
	std::string m_currentPlayingSoundName;
	bool reapted = false;
public:
	void playMusic(const std::string& musicName,const bool& isLoop) {
		if (musicName == m_currentPlayingSoundName) {
			return;
		}
		if (isPlayingMusic()) {
			stopMusic();
		}
		Music& targetMusic = m_soundMap.at(musicName);
		m_currentPlayingSoundName = musicName;
		targetMusic.looping = isLoop;
		PlayMusicStream(targetMusic);
	}
	bool isPlayingMusic() const {
		return m_currentPlayingSoundName != "";
	}
	void stopMusic() {
		if (!isPlayingMusic()) {
			return;
		}
		const Music& currentMusic = m_soundMap.at(m_currentPlayingSoundName);
		StopMusicStream(currentMusic);
		m_currentPlayingSoundName = "";
	}
	AudioManager() {
		InitAudioDevice();
		m_soundMap ={/*
			{"gameStart",LoadMusicStream("resources/gameStart.wav")},
			{"eatGhost",LoadMusicStream("resources/eatGhost.wav")},
			{"die",LoadMusicStream("resources/die.wav")},
			{"gameWin",LoadMusicStream("resources/gameWin.wav")},*/
			{"pacmanRun",LoadMusicStream("resources/pacmanRun.mp3")},
		};
	}
	~AudioManager() {
		stopMusic();
		for (auto& soundPair : m_soundMap) {
			UnloadMusicStream(soundPair.second);
		}
		CloseAudioDevice();
	}
};