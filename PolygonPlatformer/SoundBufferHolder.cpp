#include "SoundBufferHolder.h"


void SoundBufferHolder::load(SoundEffect::ID id, const std::string& filename) {
	std::unique_ptr<sf::SoundBuffer> texture(new sf::SoundBuffer());
	if (!texture->loadFromFile(filename))
		throw std::runtime_error("SoundBufferLoader::load - Failed to load " + filename);
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}


sf::SoundBuffer& SoundBufferHolder::get(SoundEffect::ID id) {
	auto found = mTextureMap.find(id);
	return *found->second;
}