#pragma once
#include <SFML/Audio.hpp>
#include <list>
#include "SoundBufferHolder.h"


class SoundPlayer
{
public:
	SoundPlayer();
	void play(SoundEffect::ID effect);
	void removeStoppedSounds();
private:
	SoundBufferHolder mSoundBuffers;
	std::list<sf::Sound> mSounds;
};

