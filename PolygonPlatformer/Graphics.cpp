#include "Graphics.h"


Graphics::Graphics () : mWindowWidth (1120), mWindowHeight (630), mBitsPerPixel (32U), mCurrentVideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel){
    // Obtaining native fullscreen modes.
	mWindowStyle = sf::Style::Close;
    mVideoModes = sf::VideoMode::getFullscreenModes();
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

void Graphics::setWindowWidth (const unsigned int width) {
    mWindowWidth = width;
}

void Graphics::setWindowHeight (const unsigned int height) {
    mWindowHeight = height;
}

void Graphics::setWindowStyle (const unsigned int style) {
    mWindowStyle = style;
}

