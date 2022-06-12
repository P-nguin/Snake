#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <vector>

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x,y) {}
	sf::Vector2i position;
};

using snakeVector = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(int blockSize);
	~Snake();

	void setDirection(Direction d);
	Direction getDirection();
	int getSpeed();
	sf::Vector2i getPosition();
	int getLives();
	int getScore();
	void IncreaseScore();
	bool hasLost();

	void lose();
	void toggleLost();

	void extend();
	void reset();

	void move();
	void update();
	void cut(int segments);
	void render(sf::RenderWindow& window);
private:
	void checkCollision();

	snakeVector body;
	int size, speed, score, lives;
	Direction dir;
	bool lost;
	sf::RectangleShape bodyRect;
};

