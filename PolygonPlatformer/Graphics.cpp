#include "Graphics.h"


Graphics::Graphics(){
	mWindowWidth = 800;
	mWindowHeight = 600;
}


Graphics::~Graphics(){

}


int Graphics::getWindowWidth(){
	return mWindowWidth;
}

int Graphics::getWindowHeight(){
	return mWindowHeight;
}

void Graphics::setWindowWidth(unsigned int width){
	mWindowWidth = width;
}

void Graphics::setWindowHeight(unsigned int height){
	mWindowHeight = height;
	sf::VideoMode::getDesktopMode
}

