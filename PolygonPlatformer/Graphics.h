#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Graphics {
public:
    Graphics ();

    ~Graphics ();

    unsigned int getWindowWidth ();

    unsigned int getWindowHeight ();

    unsigned int getWindowStyle ();

    sf::VideoMode getVideoMode ();

    void setWindowWidth (const unsigned int width);

    void setWindowHeight (const unsigned int height);

    void setWindowStyle (const unsigned int style);

private:
    // Screen resolution and color mode
    unsigned int mWindowWidth;
    unsigned int mWindowHeight;
    unsigned int mBitsPerPixel;

	// sf::Style
	unsigned int mWindowStyle;

    sf::VideoMode mCurrentVideoMode;

    std::vector<sf::VideoMode> mVideoModes;

};

