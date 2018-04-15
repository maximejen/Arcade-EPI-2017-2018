/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibNibbler.cpp
*/

#include <ios>
#include <iostream>
#include <cstdlib>
#include "LibNibbler.hpp"

static const std::vector<std::string> NIBBLER_MAP = {
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"XXXXXX        XXX       XXX  X",
	"X                            X",
	"X       X             X      X",
	"X       X             X      X",
	"X       X             X      X",
	"X                            X",
	"X                            X",
	"X  X                      X  X",
	"X   X                    X   X",
	"X   X        XXXXX       X   X",
	"X  X        XXXXXXX       X  X",
	"X           XXXXXXX          X",
	"X      X    XXXXXXX    X     X",
	"X     X      XXXXX      X    X",
	"X     X                 X    X",
	"X      X               X     X",
	"X                            X",
	"X                            X",
	"X       X             X      X",
	"X       X             X      X",
	"X       X             X      X",
	"X                            X",
	"X  XXX        XXX       XXX  X",
	"X        X          X        X",
	"X         X        X         X",
	"X          X      X          X",
	"X                            X",
	"XX                          XX",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
};

Arcade::LibNibbler::LibNibbler()
{
	srand(time(NULL));
	this->init();
	this->curKey = Keys::NONE;
	this->lastKey = Keys::Z;
	this->score = 0;
	this->msgScore = new TextBox("Score: " + std::to_string(this->score),
		{0, 0}, 25, {120, 120, 120, 120}, {255, 255, 255, 255});
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	this->timeDisplay = t1;
	this->timer = t1;
	this->timeSleep = 0.6;

}

Arcade::LibNibbler::~LibNibbler()
{
	delete this->msgScore;
}

const std::string Arcade::LibNibbler::getName() const
{
	return "Nibbler";
}

bool Arcade::LibNibbler::init()
{
	std::pair<int, int> pos;

	this->mapSize.setX(MAP_WIDTH);
	this->mapSize.setY(MAP_HEIGHT);

	pos.first = 19;
	pos.second = 15;
	this->playerPos.push_back(pos);
	pos.first = this->playerPos[0].first + 1;
	pos.second = this->playerPos[0].second;
	this->playerPos.push_back(pos);
	pos.first = this->playerPos[0].first + 2;
	pos.second = this->playerPos[0].second;
	this->playerPos.push_back(pos);
	pos.first = this->playerPos[0].first + 3;
	pos.second = this->playerPos[0].second;
	this->playerPos.push_back(pos);
	this->objectPos.setY(5);
	this->objectPos.setX(5);

	return true;
}

bool Arcade::LibNibbler::checkSpawnPos()
{
	for (int i = 0 ; i < (int) this->playerPos.size() ; i++) {
		if (((int) this->objectPos.getY() ==
			(int) this->playerPos[i].first &&
			(int) this->objectPos.getX() ==
				(int) this->playerPos[i].second) ||
			(NIBBLER_MAP[this->objectPos.getY()][this->objectPos.getX()] ==
				'X')) {
			this->setObjectPos();
		}
	}
	return true;
}

void Arcade::LibNibbler::setObjectPos()
{
	this->objectPos.setY(rand() % MAP_HEIGHT);
	this->objectPos.setX(rand() % MAP_WIDTH);

	this->checkSpawnPos();
}

bool Arcade::LibNibbler::stop()
{
	return false;
}

void Arcade::LibNibbler::applyEvent(Keys key)
{
	this->curKey = key;
}

void Arcade::LibNibbler::update()
{
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
		t2 - this->timer);
	if (time_span.count() <= this->timeSleep)
		return;
	if (curKey == Keys::NONE) {
		this->movePlayer(this->lastKey);
	} else {
		if (!this->canGoBack(this->curKey)) {
			this->curKey = this->lastKey;
		}
		this->movePlayer(this->curKey);
		this->lastKey = this->curKey;
		this->curKey = Keys::NONE;
	}
	this->timer = t2;
}

void Arcade::LibNibbler::refresh(IGraphicLib &graphicLib)
{
	Vect<size_t> size = graphicLib.getScreenSize();
	if (size.getX() < size.getY()) {
		this->resize.setY(size.getX() / MAP_WIDTH);
		this->resize.setX(size.getX() / MAP_HEIGHT);
	} else {
		this->resize.setY(size.getY() / MAP_WIDTH);
		this->resize.setX(size.getY() / MAP_HEIGHT);
	}
	if (graphicLib.getName() == "Ncurses")
		this->resize.setY(this->resize.getY() * 2);
	this->msgScore->setPos({size.getY() / 40, size.getX() / 70});
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
		t2 - this->timeDisplay);
	if (time_span.count() >= 0.1) {
		graphicLib.clearWindow();
		this->display(graphicLib);
		this->displaymap(graphicLib);
		graphicLib.drawText(*this->msgScore);
		graphicLib.refreshWindow();
		this->timeDisplay = t2;
	}
}

void Arcade::LibNibbler::displaymap(IGraphicLib &graphicLib)
{
	for (int i = 0 ; i < (int) NIBBLER_MAP.size() ; i++) {
		for (int j = 0 ; j < (int) NIBBLER_MAP[i].size() ; j++) {
			if (NIBBLER_MAP[i][j] == 'X')
				this->drawPlayer(i, j, graphicLib,
					{0, 255, 50, 255}, false);
		}
	}
}

void Arcade::LibNibbler::display(IGraphicLib &graphicLib)
{
	this->drawPlayer(this->objectPos.getY(), this->objectPos.getX(),
		graphicLib, {244, 65, 65, 255},
		true);
	for (int i = 0 ; i < (int) this->playerPos.size() ; i++) {
		if (i == 0) {
			this->drawPlayer(this->playerPos[i].first,
				this->playerPos[i].second, graphicLib,
				{0, 255, 255, 255},
				true);

		} else
			this->drawPlayer(this->playerPos[i].first,
				this->playerPos[i].second, graphicLib,
				{244, 255, 255, 255},
				true);
	}
}

void
Arcade::LibNibbler::drawPlayer(size_t x, size_t y, IGraphicLib &graphicLib,
	Color color, bool space)
{
	y = y * this->resize.getY();
	x = x * this->resize.getX();
	Arcade::PixelBox pixelBox({this->resize.getX(), this->resize.getY()},
		{y, x}, color);
	if (space && graphicLib.getName() != "Ncurses")
		pixelBox.setSize(
			{this->resize.getX() - 1, this->resize.getY() - 1});
	graphicLib.drawPixelBox(pixelBox);
}

int Arcade::LibNibbler::checkFood(Keys dir)
{
	if (dir == Keys::Z) {
		if (this->playerPos[0].first - 1 ==
			(int) this->objectPos.getY() &&
			this->playerPos[0].second ==
				(int) this->objectPos.getX()) {
			//this->playerPos.insert(this->playerPos.begin(), std::make_pair(this->playerPos[0].first - 1, this->playerPos[0].second));
			this->playerPos.push_back(std::make_pair(
				this->playerPos[this->playerPos.size() -
					1].first - 1,
				this->playerPos[this->playerPos.size() -
					1].second));
			return (1);
		}
	} else if (dir == Keys::S) {
		if (this->playerPos[0].first + 1 ==
			(int) this->objectPos.getY() &&
			this->playerPos[0].second ==
				(int) this->objectPos.getX()) {
			this->playerPos.push_back(std::make_pair(
				this->playerPos[this->playerPos.size() -
					1].first - 1,
				this->playerPos[this->playerPos.size() -
					1].second));
			return (1);
		}
	} else if (dir == Keys::Q) {
		if (this->playerPos[0].first == (int) this->objectPos.getY() &&
			this->playerPos[0].second - 1 ==
				(int) this->objectPos.getX()) {
			this->playerPos.push_back(std::make_pair(
				this->playerPos[this->playerPos.size() -
					1].first - 1,
				this->playerPos[this->playerPos.size() -
					1].second));
			return (1);
		}
	} else if (dir == Keys::D) {
		if (this->playerPos[0].first == (int) this->objectPos.getY() &&
			this->playerPos[0].second + 1 ==
				(int) this->objectPos.getX()) {
			this->playerPos.push_back(std::make_pair(
				this->playerPos[this->playerPos.size() -
					1].first - 1,
				this->playerPos[this->playerPos.size() -
					1].second));
			return (1);
		}
	}
	return (0);
}


void Arcade::LibNibbler::movePlayer(Keys dir)
{
	if (this->checkFood(dir) == 1) {
		this->setObjectPos();
		this->score++;
		this->msgScore->setValue(
			"Score: " + std::to_string(this->score));
		if (this->timeSleep > 0.3)
			this->timeSleep -= 0.05;
	}
	this->moveSnake();
	switch ((int) dir) {
		case Keys::Z:
			this->playerPos[0].first--;
			break;
		case Keys::S :
			this->playerPos[0].first++;
			break;
		case Keys::Q :
			this->playerPos[0].second--;
			break;
		case Keys::D :
			this->playerPos[0].second++;
			break;
		default:
			break;
	}
	if (this->checkEnd())
		exit(0);
}

bool Arcade::LibNibbler::checkEnd()
{
	bool ret = false;

	for (int i = 1 ; i < (int) this->playerPos.size() ; i++) {
		if (this->playerPos[0] == this->playerPos[i]) {
			ret = true;
		}
	}
	if (this->playerPos[0].first < 0)
		ret = true;
	else if (this->playerPos[0].first >= MAP_HEIGHT)
		ret = true;
	else if (this->playerPos[0].second < 0)
		ret = true;
	else if (this->playerPos[0].second >= MAP_WIDTH)
		ret = true;
	if (NIBBLER_MAP[this->playerPos[0].first][this->playerPos[0].second] ==
		'X')
		return true;
	return ret;
}

bool Arcade::LibNibbler::canGoBack(Keys key)
{
	bool ret = true;

	if (this->playerPos.size() == 1)
		ret = true;
	else if (key == Keys::Z &&
		this->playerPos[1].first + 1 != this->playerPos[0].first) {
		ret = true;
	} else if (key == Keys::S &&
		this->playerPos[1].first - 1 != this->playerPos[0].first) {
		ret = true;

	} else if (key == Keys::Q &&
		this->playerPos[1].second + 1 != this->playerPos[0].second) {
		ret = true;

	} else if (key == Keys::D &&
		this->playerPos[1].second - 1 != this->playerPos[0].second) {
		ret = true;
	} else
		ret = false;
	return ret;
}

void Arcade::LibNibbler::moveSnake()
{
	auto tmp = this->playerPos;
	for (int i = 1 ; i < (int) this->playerPos.size() ; i++) {
		this->playerPos[i].first = tmp[i - 1].first;
		this->playerPos[i].second = tmp[i - 1].second;
	}
}

size_t Arcade::LibNibbler::getScore()
{
	return this->score;
}