#include "TextureHolder.h"


void TextureHolder::load (Textures::ID id, const std::string& filename) {
    std::unique_ptr<sf::Texture> texture (new sf::Texture ());
    if (!texture->loadFromFile (filename))
        throw std::runtime_error ("TextureHolder::load - Failed to load " + filename);
    mTextureMap.insert (std::make_pair (id, std::move (texture)));
}


sf::Texture& TextureHolder::get (Textures::ID id) {
    auto found = mTextureMap.find (id);
    return *found->second;
}