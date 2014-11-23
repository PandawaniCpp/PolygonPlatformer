#pragma once
#include <SFML/Graphics.hpp>
class Graphics{
public:
	Graphics();
	
	~Graphics();
	
	int getWindowWidth(){
		return mWindowWidth;
	}

	int getWindowHeight(){
		return mWindowHeight;
	}

	void setWindowWidth(unsigned int width){
		mWindowWidth = width;
	}

	void setWindowHeight(unsigned int height){
		mWindowHeight = height;
	}

private:
	unsigned int mWindowWidth;

	unsigned int mWindowHeight;

};

