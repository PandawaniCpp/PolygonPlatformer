#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

namespace Music {
	enum ID{
		MENUTHEME,
		GAMETHEME
	};
}

class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();
	~MusicPlayer();
	void play(Music::ID theme);
	void stop();
	void setPaused(bool paused);
	void setVolume(float volume);
private:
	sf::Music mMusic;
	std::map<Music::ID, std::string> mFilenames;
	float mVolume;
};

