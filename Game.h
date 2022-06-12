#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Snake.h"
#include "World.h"
#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();
	Window* getWindow();
private:
	World world;
	Snake snake;

	Window window;
};

