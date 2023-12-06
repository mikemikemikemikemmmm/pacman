#pragma once
#include <unordered_map>
#include <string>
#include "global.h"
#include "../lib/raylib/include/raylib.h"
struct KeepPlaySoundData {
	std::string soundName;
	long long keepPlayMilliseconds;
	long long currentSumMilliseconds;
	bool needDeleted;
};
class AudioManager {
private:
	std::unordered_map<std::string, Sound> m_soundMap;
	std::vector<KeepPlaySoundData> m_keepPlayList;
	bool m_isMuted;
public:
	void cleanKeepPlayList();
	void setIsMuted(const bool& b);
	void playMusic(const std::string& musicName);
	void playKeepMusic(const long long& millSecond);
	void pausePlayingKeepMusic();
	void setKeepPlayMusicForSecond(const std::string& musicName,const int& second);
	void stopPlayingMusic(const std::string& musicName);
	void stopPlayingAllMusic();
	~AudioManager();
	AudioManager();
};