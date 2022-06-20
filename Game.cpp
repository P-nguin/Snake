#include "Game.h"

Game::Game() : window("HI", sf::Vector2u(800, 600)), snake(world.getBlockSize()), world(sf::Vector2u(800, 600)) {

}

Game::~Game() {}

void Game::update() {
	float dt = 1.0f / snake.getSpeed();
	if (elapsed >= dt) {
		snake.update();
		world.update(snake);
		elapsed -= dt;
		if (snake.hasLost()) {
			snake.reset();
		}
	}

	window.update();
}

void Game::render() {
	window.beginDraw();
	world.render(*window.getRenderWindow());
	world.render(*window.getRenderWindow());
	window.endDraw();
}

Window* Game::getWindow() {
	return &window;
}

void Game::handleInput() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && snake.getDirection() != Direction::Down) {
		snake.setDirection(Direction::Down);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && snake.getDirection() != Direction::Up) {
		snake.setDirection(Direction::Down);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && snake.getDirection() != Direction::Left) {
		snake.setDirection(Direction::Right);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && snake.getDirection() != Direction::Right) {
		snake.setDirection(Direction::Left);
	}
}

int main(int agrc, void** argv[]) {
	Game game;
	while (!game.getWindow()->isDone()) {
		game.handleInput();
		game.update();
		game.render();
	}
}