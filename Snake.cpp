#include "Snake.h"
Snake::Snake(int blockSize) {
	size = blockSize;
	bodyRect.setSize(sf::Vector2f(size-1, size-1));
	reset();
}

Snake::~Snake() {}

void Snake::reset() {
	body.clear();

	body.push_back(SnakeSegment(5, 7));
	body.push_back(SnakeSegment(5, 6));
	body.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	speed = 15; lives = 3; score = 0;
	lost = false;
}

void Snake::setDirection(Direction d) { dir = d; }
Direction Snake::getDirection() { return dir; }
int Snake::getSpeed() { return speed; }

sf::Vector2i Snake::getPosition() {
	return (!body.empty() ? body.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives() { return lives; }
int Snake::getScore() { return score; }

void Snake::IncreaseScore() { score += 10; }
bool Snake::hasLost() { return lost; }
void Snake::lose() { lost = true; }
void Snake::toggleLost() { lost = !lost; }

void Snake::extend() {
	if (body.empty()) return;
	SnakeSegment& tail_end = body[body.size()-1];

	if (body.size() > 1) {
		SnakeSegment& tail_start = body[body.size() - 2];
		if (tail_end.position.x == tail_start.position.x) {
			if (tail_end.position.y > tail_start.position.y) body.push_back(SnakeSegment(tail_start.position.x, tail_end.position.y + 1));
			else body.push_back(SnakeSegment(tail_start.position.x, tail_end.position.y - 1));
		}
		else {
			if (tail_end.position.x > tail_start.position.x) body.push_back(SnakeSegment(tail_end.position.x - 1, tail_end.position.y));
			else body.push_back(SnakeSegment(tail_end.position.x + 1, tail_end.position.y));
		}
	}
	else {
		if (dir == Direction::Up)         body.push_back(SnakeSegment(tail_end.position.x, tail_end.position.y - 1));
		else if (dir == Direction::Down)  body.push_back(SnakeSegment(tail_end.position.x, tail_end.position.y + 1));
		else if (dir == Direction::Left)  body.push_back(SnakeSegment(tail_end.position.x + 1, tail_end.position.y));
		else if (dir == Direction::Right) body.push_back(SnakeSegment(tail_end.position.x - 1, tail_end.position.y));
	}
}

void Snake::update() {
	if (body.empty() || dir == Direction::None) return;
	move(); checkCollision();
}

void Snake::move() {
	for (int i = body.size() - 1; i > 0; i--) {
		body[i].position = body[i - 1].position;
	}
	if (dir == Direction::Left) body[0].position.x--;
	else if (dir == Direction::Right) body[0].position.x++;
	else if (dir == Direction::Up) body[0].position.y--;
	else body[0].position.y++;
}

void Snake::checkCollision() {
	if (body.size() <= 4) return;
	SnakeSegment& head = body.front();
	for (auto i = body.begin() + 1; i != body.end(); ++i) {
		if (i->position == head.position) {
			int segments = body.end() - i;
			cut(segments);
			break;
		}
	}
}

void Snake::cut(int segments) {
	for (int i = 0; i < segments; i++) {
		body.pop_back();
	}
	lives--;
	if (lives == 0) {
		lose(); return;
	}
}

void Snake::render(sf::RenderWindow& window) {
	if (body.empty()) return;
	auto seg = body.begin();
	bodyRect.setFillColor(sf::Color::Yellow);
	bodyRect.setPosition(seg->position.x * size, seg->position.y * size);
	window.draw(bodyRect);

	bodyRect.setFillColor(sf::Color::Green);
	for (; seg++ != body.end();) {
		bodyRect.setPosition(seg->position.x * size, seg->position.y * size);
		window.draw(bodyRect);
	}
}