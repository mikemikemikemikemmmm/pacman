#pragma once
#include <unordered_map>
#include <string>
#include "../lib/raylib/include/raylib.h"
class AudioManager {
private:
	std::unordered_map<std::string, Sound> m_soundMap;
	std::string m_currentPlayingSoundName = "";
public:
	void playMusic(const std::string& musicName);
	void stopPlayingMusic();
	AudioManager();
	~AudioManager();
};