#include "MusicPlayer.h"


MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(20.f) {
	mFilenames[Music::MENUTHEME] = "./sounds/music/Menu.ogg";
	mFilenames[Music::GAMETHEME] = "./sounds/music/Boss.ogg";
};

MusicPlayer::~MusicPlayer() {};

void MusicPlayer::play(Music::ID theme) {
	std::string filename = mFilenames[theme];
	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");
	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
};

void MusicPlayer::stop(){
	mMusic.stop();
};

void MusicPlayer::setPaused(bool paused){
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
};

void MusicPlayer::setVolume(float volume){
	mVolume = volume;
};
