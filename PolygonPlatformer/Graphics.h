#pragma once
#include <SFML/Graphics.hpp>
class Graphics{
public:
	Graphics();
	
	~Graphics();
	
	int getWindowWidth();

	int getWindowHeight();

	void setWindowWidth(unsigned int width);

	void setWindowHeight(unsigned int height);

private:
	unsigned int mWindowWidth;

	unsigned int mWindowHeight;

};

