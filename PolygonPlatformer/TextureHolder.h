#include <SFML/Graphics.hpp>
#include <memory>
#pragma once


namespace Textures {
    enum ID {
        HEALTHBAR_RED,
		HEALTHBAR_GREEN,
		PLAYER_RIGHT_ANIMATION,
		PLAYER_RIGHT,
		PLAYER_LEFT,
		PLAYER_HIT,
		FRIENDLY_BULLET,
		ENEMY_BULLET,
		BLOOD,
		ENEMY_FIGHTER,
		ENEMY_FAT,
		ENEMY_SWARM,
		ENEMY_KAMIKAZE,
		GAME_BACKGROUND,
		GROUND,
		MENU,
		TITLE,
		PAUSE,
		UPGRADE
    };
}

class TextureHolder {
public:

    void load (Textures::ID id, const std::string& filename);
    sf::Texture& get (Textures::ID id);
private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture> > mTextureMap;



};