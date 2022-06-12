#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone();
	bool isFullscreen();
	sf::Vector2u getWindowSize();

	void toggleFullscreen();

	void draw(sf::Drawable& drawable);
private:
	void setup(const std::string title, const sf::Vector2u& size);
	void destroy();
	void create();

	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;
	bool done;
	bool fullscreen;
};