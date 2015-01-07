#include "Graphics.h"

//1120 630
Graphics::Graphics() : mWindowWidth(1366),
mWindowHeight(768),
mBitsPerPixel(32U),
mFullscreen(0),
gameName("Polygon Platformer"),
mCurrentVideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel){
    // Obtaining native fullscreen modes.
	setAntialiasing(2);

	if (mFullscreen) {
		mWindowStyle = sf::Style::Fullscreen;

		mWindowWidth = sf::VideoMode::getDesktopMode().width;
		mWindowHeight = sf::VideoMode::getDesktopMode().height;
		mCurrentVideoMode = sf::VideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel);
	}
	else
		mWindowStyle = sf::Style::Close;
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

bool Graphics::getFullscreen() {
	return mFullscreen;
}

std::string Graphics::getGameName() {
	return gameName;
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

void Graphics::setWindowPtr(sf::RenderWindow& target) {
	windowPtr = &target;
}

void Graphics::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		if (mFullscreen == fullscreen)
			return;
		else {
			mFullscreen = fullscreen;
			windowPtr->close();
			mWindowStyle = sf::Style::Fullscreen;
			mWindowWidth = sf::VideoMode::getDesktopMode().width;
			mWindowHeight = sf::VideoMode::getDesktopMode().height;
			mCurrentVideoMode = sf::VideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel);
			windowPtr->create(mCurrentVideoMode, gameName, mWindowStyle, mContextSettings);
			windowPtr->setVerticalSyncEnabled(getVsync());
			windowPtr->setMouseCursorVisible(false);
			windowPtr->setIcon(window_icon.width, window_icon.height, window_icon.pixel_data);
			windowPtr->setKeyRepeatEnabled(false);
			return;
		}
	}
	else {
		if (mFullscreen == fullscreen)
			return;
		else {
			mFullscreen = fullscreen;
			windowPtr->close();
			mWindowStyle = sf::Style::Close;
			mWindowWidth = 1240;
			mWindowHeight = 630;
			mCurrentVideoMode = sf::VideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel);
			windowPtr->create(mCurrentVideoMode, gameName, mWindowStyle, mContextSettings);
			windowPtr->setVerticalSyncEnabled(getVsync());
			windowPtr->setMouseCursorVisible(false);
			windowPtr->setIcon(window_icon.width, window_icon.height, window_icon.pixel_data);
			windowPtr->setKeyRepeatEnabled(false);
			return;
		}
	}
	return;
}

void Graphics::changeFullscreen() {
	if (mFullscreen == 0) {
		mFullscreen = 1;
		windowPtr->close();
		mWindowStyle = sf::Style::Fullscreen;
		mWindowWidth = sf::VideoMode::getDesktopMode().width;
		mWindowHeight = sf::VideoMode::getDesktopMode().height;
		mCurrentVideoMode = sf::VideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel);
		windowPtr->create(mCurrentVideoMode, gameName, mWindowStyle, mContextSettings);
		windowPtr->setVerticalSyncEnabled(getVsync());
		windowPtr->setMouseCursorVisible(false);
		windowPtr->setIcon(window_icon.width, window_icon.height, window_icon.pixel_data);
		windowPtr->setKeyRepeatEnabled(false);
		return;
	}
	else {
		mFullscreen = 0;
		windowPtr->close();
		mWindowStyle = sf::Style::Close;
		mWindowWidth = 1366;
		mWindowHeight = 768;
		mCurrentVideoMode = sf::VideoMode(mWindowWidth, mWindowHeight, mBitsPerPixel);
		windowPtr->create(mCurrentVideoMode, gameName, mWindowStyle, mContextSettings);
		windowPtr->setVerticalSyncEnabled(getVsync());
		windowPtr->setMouseCursorVisible(false);
		windowPtr->setIcon(window_icon.width, window_icon.height, window_icon.pixel_data);
		windowPtr->setKeyRepeatEnabled(false);
		return;
	}
}
