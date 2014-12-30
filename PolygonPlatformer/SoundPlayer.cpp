#include "SoundPlayer.h"


SoundPlayer::SoundPlayer()
	: mSoundBuffers()
	, mSounds()
{
	mSoundBuffers.load(SoundEffect::PLAYER_SHOOT,
		"./sounds/sound_effects/laser2.wav");
	mSoundBuffers.load(SoundEffect::ENEMY_SHOOT,
		"./sounds/sound_effects/laser4.wav");
	mSoundBuffers.load(SoundEffect::ENEMY_DIES,
		"./sounds/sound_effects/scratch2_16.wav");
	mSoundBuffers.load(SoundEffect::ENEMY_HIT,
		"./sounds/sound_effects/heartbeat2_16.wav");
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	mSounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([](const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}