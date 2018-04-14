/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include <ios>
#include <iostream>
#include <cstdlib>
#include <map>
#include "LibPacman.hpp"

static std::vector<std::string> PACMAN_MAP = {
	"   XXXXXXXXXXXXXXXXXXXXX   ",
	"   X.........X.........X   ",
	"   X.XXX.XXX.X.XXX.XXX.X   ",
	"   XoX X.X X.X.X X.X XoX   ",
	"   X.XXX.XXX.X.XXX.XXX.X   ",
	"   X...................X   ",
	"   X.XXX.X.XXXXX.X.XXX.X   ",
	"   X.XXX.X.XXXXX.X.XXX.X   ",
	"   X.....X...X...X.....X   ",
	"   XXXXX.XXX X XXX.XXXXX   ",
	"       X.X       X.X       ",
	"       X.X XX XX X.X       ",
	"   XXXXX.X X   X X.XXXXX   ",
	"   X    .  X   X  .    X   ",
	"   XXXXX.X XXXXX X.XXXXX   ",
	"       X.X       X.X       ",
	"       X.X XXXXX X.X       ",
	"   XXXXX.X XXXXX X.XXXXX   ",
	"   X.........X.........X   ",
	"   X.XXX.XXX.X.XXX.XXX.X   ",
	"   Xo..X..... .....X..oX   ",
	"   XXX.X.X.XXXXX.X.X.XXX   ",
	"   XXX.X.X.XXXXX.X.X.XXX   ",
	"   X.....X...X...X.....X   ",
	"   X.XXXXXXX.X.XXXXXXX.X   ",
	"   X...................X   ",
	"   XXXXXXXXXXXXXXXXXXXXX   "
};

static const std::map<Arcade::Keys, int> FIRST_ACTION = {
	{Arcade::Keys::Z, 0},
	{Arcade::Keys::S, 0},
	{Arcade::Keys::Q, -1},
	{Arcade::Keys::D, 1},
};

static const std::map<Arcade::Keys, int> SECOND_ACTION = {
	{Arcade::Keys::Z, -1},
	{Arcade::Keys::S, 1},
	{Arcade::Keys::Q, 0},
	{Arcade::Keys::D, 0},
};

Arcade::LibPacman::LibPacman()
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
	this->lifes = 3;

}

Arcade::LibPacman::~LibPacman()
{
	delete this->msgScore;
}

const std::string Arcade::LibPacman::getName() const
{
	return "Nibbler";
}

bool Arcade::LibPacman::init()
{
	std::pair<int, int> pos;

	this->mapSize.setX(MAP_WIDTH);
	this->mapSize.setY(MAP_HEIGHT);

	this->pos.first = 13;
	this->pos.second = 20;
	this->map = PACMAN_MAP;
	return true;
}

bool Arcade::LibPacman::stop()
{
	return true;
}

void Arcade::LibPacman::applyEvent(Keys key)
{
	this->curKey = key;
}

void Arcade::LibPacman::update()
{
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
		t2 - this->timer);
	if (time_span.count() <= this->timeSleep)
		return;
	if (curKey == Keys::NONE) {
		this->movePlayer(this->lastKey);
	} else {
		this->movePlayer(this->curKey);
		this->lastKey = this->curKey;
		this->curKey = Keys::NONE;
	}
	this->timer = t2;
}

void Arcade::LibPacman::refresh(IGraphicLib &graphicLib)
{
	Vect<size_t> size = graphicLib.getScreenSize();
	this->resize.setX(size.getX() / MAP_WIDTH);
	this->resize.setY(size.getY() / MAP_HEIGHT);
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

void Arcade::LibPacman::displaymap(IGraphicLib &graphicLib)
{
	char tmp;

	for (int j = 0 ; j < MAP_HEIGHT ; j++) {
		for (int i = 0 ; i < MAP_WIDTH ; i++) {
			tmp = PACMAN_MAP[j][i];
			if (tmp == 'X')
				this->drawRectangle(i, j, graphicLib,
					{30, 0, 255, 255}, false);
			else if (tmp == '.' || tmp == 'o')
				this->drawFood({i, j}, graphicLib,

					{255, 210, 0, 255}, tmp == '.');
		}
	}
}

void Arcade::LibPacman::display(IGraphicLib &graphicLib)
{
	this->drawRectangle(static_cast<size_t>(this->pos.first),
		static_cast<size_t>(this->pos.second),
		graphicLib, {255, 210, 0, 255},
		true);
}

void Arcade::LibPacman::drawRectangle(size_t x, size_t y,
	IGraphicLib &graphicLib,
	Color color, bool space)
{
	y = y * this->resize.getY();
	x = x * this->resize.getX();
	Arcade::PixelBox pixelBox({this->resize.getX(), this->resize.getY()},
		{x, y}, color);
	if (space && graphicLib.getName() != "Ncurses")
		pixelBox.setSize(
			{this->resize.getX() - 1, this->resize.getY() - 1});
	graphicLib.drawPixelBox(pixelBox);
}

void Arcade::LibPacman::drawFood(std::pair<size_t, size_t> pair,
	Arcade::IGraphicLib &graphicLib, Arcade::Color color, bool type)
{
	int size = type ? 4 : 2;
	int sizex = static_cast<int>(this->resize.getX() / size);
	int sizey = static_cast<int>(this->resize.getY() / size);

	pair.second = pair.second * this->resize.getY();
	pair.first = pair.first * this->resize.getX();
	if (graphicLib.getName() != "Ncurses") {
		pair.second += this->resize.getY() / 2 - sizey / 2;
		pair.first += this->resize.getX() / 2 - sizex / 2;
		Arcade::PixelBox pixelBox(
			{this->resize.getX() / size,
				this->resize.getY() / size},
			{pair.first, pair.second}, color);
		graphicLib.drawPixelBox(pixelBox);
	} else {
		TextBox food(type ? "." : "o", {pair.first, pair.second}, 1,
			{255, 210, 0, 255});
		graphicLib.drawText(food);
	}
}

void Arcade::LibPacman::movePlayer(Keys dir)
{
	std::pair<int, int> save = this->pos;
	char tmp;

	try {
		this->pos.first += FIRST_ACTION.at(dir);
		this->pos.second += SECOND_ACTION.at(dir);
	} catch (std::exception &e) {}
	tmp = PACMAN_MAP[this->pos.second][this->pos.first];
	if (tmp == 'X') {
		this->pos.first = save.first;
		this->pos.second = save.second;
	} else if (tmp == '.' || tmp == 'o') {
		if (tmp == '.')
			this->score++;
		else
			this->score += 10;
		PACMAN_MAP[this->pos.second][this->pos.first] = ' ';
		this->msgScore->setValue(
			"Score: " + std::to_string(this->score));
	}
	if (this->checkEnd())
		exit(0);
}

bool Arcade::LibPacman::checkEnd()
{
	bool ret = false;
	int count = 0;

	if (this->lifes == 0)
		return true;
	for (int j = 0 ; j < MAP_HEIGHT ; j++)
		for (int i = 0 ; i < MAP_WIDTH ; i++)
			if (PACMAN_MAP[j][i] == '.')
				count++;
	if (count == 0)
		ret = true;
	return ret;
}

size_t Arcade::LibPacman::getScore()
{
	return this->score;
}
