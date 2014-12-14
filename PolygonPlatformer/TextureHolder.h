#include <SFML/Graphics.hpp>
#include <memory>
#pragma once


namespace Textures {
    enum ID {
        PLAYER, ENEMY_FIGHTER,GAME_BACKGROUND,GROUND
    };
}

class TextureHolder {
public:

    void load (Textures::ID id, const std::string& filename);
    sf::Texture& get (Textures::ID id);
private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture> > mTextureMap;



};