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

	bool getVsync ();

	sf::ContextSettings getContextSettings();

    void setWindowWidth (const unsigned int width);

    void setWindowHeight (const unsigned int height);

    void setWindowStyle (const unsigned int style);

	void setVsync(const bool vsync);

	void setAntialiasing(const unsigned int antialiasing);

	void setWindowPtr(sf::RenderWindow& target);

private:

	sf::RenderWindow* windowPtr;
    // Screen resolution and color mode
    unsigned int mWindowWidth;
    unsigned int mWindowHeight;
    unsigned int mBitsPerPixel;

	// sf::Style
	unsigned int mWindowStyle;

	bool mVsync;

    sf::VideoMode mCurrentVideoMode;

    std::vector<sf::VideoMode> mVideoModes;

	//Ustawienia do okna: antialiasing & depths
	sf::ContextSettings  mContextSettings;

};

