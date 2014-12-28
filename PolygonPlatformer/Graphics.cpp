#include "Graphics.h"


Graphics::Graphics () : mWindowWidth (1120), mWindowHeight (630), mBitsPerPixel (32U), mCurrentVideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel){
    // Obtaining native fullscreen modes.
	setAntialiasing(2);
	mWindowStyle = sf::Style::Fullscreen;
    mVideoModes = sf::VideoMode::getFullscreenModes();
	mVsync = true;
}


Graphics::~Graphics () {

}


unsigned int Graphics::getWindowWidth () {
    return mWindowWidth;
}

unsigned int Graphics::getWindowHeight () {
    return mWindowHeight;
}

unsigned int Graphics::getWindowStyle () {
    return mWindowStyle;
}

sf::VideoMode Graphics::getVideoMode () {
    return mCurrentVideoMode;
}

bool Graphics::getVsync () {
	return mVsync;
}

sf::ContextSettings Graphics::getContextSettings() {
	return mContextSettings;
}

void Graphics::setWindowWidth (const unsigned int width) {
    mWindowWidth = width;
}

void Graphics::setWindowHeight (const unsigned int height) {
    mWindowHeight = height;
}

void Graphics::setWindowStyle (const unsigned int style) {
    mWindowStyle = style;
}

void Graphics::setVsync(const bool vsync) {
	mVsync = vsync;
}

void Graphics::setAntialiasing(const unsigned int antialiasing) {
	mContextSettings.antialiasingLevel = antialiasing;
}

