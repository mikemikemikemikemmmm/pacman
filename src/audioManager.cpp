#include "audioManager.h"

void AudioManager::cleanKeepPlayList()
{
	if (m_keepPlayList.size() == 0) {
		return;
	}
	for (auto& sound :m_keepPlayList) {
		stopPlayingMusic(sound.soundName);
	}
	m_keepPlayList.clear();
}

void AudioManager::setIsMuted(const bool& b)
{
	if (m_isMuted == b) {
		return;
	}
	m_isMuted = b;
}

void AudioManager::playMusic(const std::string& musicName) {
	const Sound& targetSound = m_soundMap.at(musicName);
	if (IsSoundPlaying(targetSound)) {
		return;
	}
	PlaySound(targetSound);
}

void AudioManager::playKeepMusic(const long long& millSecond)
{
	const int listLen = static_cast<int>(m_keepPlayList.size());
	if (listLen == 0) {
		return;
	}
	for (int i = 0; i < listLen; i++) {
		KeepPlaySoundData& targetData = m_keepPlayList[i];
		const bool isTimeOut = targetData.currentSumMilliseconds >= targetData.keepPlayMilliseconds;
		const bool isPlaying = IsSoundPlaying(m_soundMap.at(targetData.soundName));
		if (isTimeOut && isPlaying) {
			stopPlayingMusic(targetData.soundName);
			targetData.needDeleted = true;
		}
		else if (isTimeOut && !isPlaying) {
			targetData.needDeleted = true;
		}
		else {
			playMusic(targetData.soundName);
			targetData.currentSumMilliseconds += millSecond;
		}
	}
	m_keepPlayList.erase(
		std::remove_if(m_keepPlayList.begin(), 
		m_keepPlayList.end(), 
		[](const KeepPlaySoundData& targetData) {
			return targetData.needDeleted;
		}), 
		m_keepPlayList.end()
	);
}

void AudioManager::pausePlayingKeepMusic()
{
	for  (auto& soundData : m_keepPlayList) {
		const Sound& targetSound = m_soundMap.at(soundData.soundName);
		PauseSound(targetSound);
	}
}

void AudioManager::setKeepPlayMusicForSecond(const std::string& musicName, const int& second)
{
	auto hasItem = std::find_if(
		m_keepPlayList.begin(),
		m_keepPlayList.end(), 
		[&musicName](const KeepPlaySoundData& item) {
			return item.soundName == musicName;
		});
	if (hasItem != m_keepPlayList.end()) {
		auto& targetSound = *hasItem;
		targetSound.currentSumMilliseconds =0;
		targetSound.keepPlayMilliseconds = second * 1000;
		return;
	}
	else {
		playMusic(musicName);
		m_keepPlayList.push_back({
			musicName,
			second*1000,
			0,
			false }
		);
	}
}

void AudioManager::stopPlayingMusic(const std::string& musicName) {
	const Sound& targetSound = m_soundMap.at(musicName);
	if (IsSoundPlaying(targetSound)) {
		StopSound(targetSound);
	}
}

void AudioManager::stopPlayingAllMusic()
{
	for (auto& soundPair : m_soundMap) {
		const Sound& soundResource = soundPair.second;
		if (IsSoundPlaying(soundResource)) {
			StopSound(soundResource);
		};
	}
}

AudioManager::AudioManager():m_isMuted(false){
	InitAudioDevice();
	m_soundMap = {
		{ "gameStart",LoadSound("resources/gameStart.wav") },
		{ "gameOver",LoadSound("resources/gameOver.wav") },
		{ "gameWin",LoadSound("resources/gameWin.wav") },
		{ "background",LoadSound("resources/background.wav") },
		{ "eatGhost",LoadSound("resources/eatGhost.wav") },
		{ "eatPower",LoadSound("resources/eatPower.wav") },
		{ "eatFood",LoadSound("resources/eatFood.wav") },
	};
}

AudioManager::~AudioManager() {
	stopPlayingAllMusic();
	for (auto& soundPair : m_soundMap) {
		UnloadSound(soundPair.second);
	}
	CloseAudioDevice();
}
