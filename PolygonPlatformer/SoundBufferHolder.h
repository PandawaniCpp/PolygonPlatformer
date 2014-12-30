#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>

namespace SoundEffect {
	enum ID {
		PLAYER_SHOOT,
		PLAYER_HIT,
		PLAYER_DIES,
		GAME_OVER,
		ENEMY_SHOOT,
		ENEMY_HIT,
		ENEMY_DIES
	};
}

class SoundBufferHolder {
public:

	void load(SoundEffect::ID id, const std::string& filename);
	sf::SoundBuffer& get(SoundEffect::ID id);
private:
	std::map<SoundEffect::ID, std::unique_ptr<sf::SoundBuffer> > mTextureMap;



};
