/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include <ios>
#include <iostream>
#include <cstdlib>
#include "LibPacman.hpp"

static const std::vector<std::string> PACMAN_MAP = {
	"XXXXXXXXXXXXXXXXXXXXX",
	"X.........X.........X",
	"X.XXX.XXX.X.XXX.XXX.X",
	"X°X X.X X.X.X X.X X°X",
	"X.XXX.XXX.X.XXX.XXX.X",
	"X...................X",
	"X.XXX.X.XXXXX.X.XXX.X",
	"X.XXX.X.XXXXX.X.XXX.X",
	"X.....X...X...X.....X",
	"XXXXX.XXX X XXX.XXXXX",
	"    X.X       X.X    ",
	"    X.X XX XX X.X    ",
	"XXXXX.X X   X X.XXXXX",
	"X    .  X   X  .    X",
	"XXXXX.X XXXXX X.XXXXX",
	"    X.X       X.X    ",
	"    X.X XXXXX X.X    ",
	"XXXXX.X XXXXX X.XXXXX",
	"X.........X.........X",
	"X.XXX.XXX.X.XXX.XXX.X",
	"X°..X..... .....X..°X",
	"XXX.X.X.XXXXX.X.X.XXX",
	"XXX.X.X.XXXXX.X.X.XXX",
	"X ....X...X...X.... X",
	"X.XXXXXXX.X.XXXXXXX.X",
	"X...................X",
	"XXXXXXXXXXXXXXXXXXXXX"
};

Arcade::LibPacman::LibPacman()
{
	srand(time(NULL));
	this->init();
	this->curKey = Keys::NONE;
	this->lastKey = Keys::Z;
	this->score = 0;
	this->msgScore = new TextBox("Score: " + std::to_string(this->score), {0, 0}, 25, {120, 120,120, 120}, {255, 255, 255, 255});
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	this->timeDisplay = t1;
	this->timer = t1;
	this->timeSleep = 0.6;

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

	this->pos.first = 10;
	this->pos.second = 20;
	return true;
}

bool Arcade::LibPacman::checkSpawnPos()
{
	for (int i = 0; i < (int)this->playerPos.size(); i++) {
		if (((int)this->objectPos.getY() == (int)this->playerPos[i].first &&
		     (int)this->objectPos.getX() == (int)this->playerPos[i].second) ||
		    (PACMAN_MAP[this->objectPos.getY()][this->objectPos.getX()] == 'X')) {
			std::cout << "Reload Object pos" << std::endl;
			this->setObjectPos();
		}
	}
	return true;
}

void Arcade::LibPacman::setObjectPos()
{
	this->objectPos.setY(rand() % MAP_HEIGHT);
	this->objectPos.setX(rand() % MAP_WIDTH);
	std::cout << " Pos :" << this->objectPos.getY() << this->objectPos.getX() << std::endl;

	this->checkSpawnPos();
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
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - this->timer);
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

void Arcade::LibPacman::refresh(IGraphicLib &graphicLib)
{
	Vect<size_t> size = graphicLib.getScreenSize();
	this->resize.setY(size.getX() / MAP_WIDTH);
	this->resize.setX(size.getY() / MAP_HEIGHT);
	this->msgScore->setPos({size.getY() / 40, size.getX() / 70});
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - this->timeDisplay);
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
	for (int i = 0; i < (int)PACMAN_MAP.size(); i++) {
		for (int j = 0; j < (int)PACMAN_MAP[i].size(); j++) {
			if (PACMAN_MAP[i][j] == 'X')
				this->drawPlayer(i,j,  graphicLib, {0, 255, 50, 255}, false);
		}
	}
}

void Arcade::LibPacman::display(IGraphicLib &graphicLib)
{
	this->drawPlayer(this->objectPos.getY(), this->objectPos.getX(), graphicLib, {244, 65, 65, 255},
			 true);
	for (int i = 0; i < (int)this->playerPos.size(); i++) {
		if (i == 0) {
			this->drawPlayer(this->playerPos[i].first, this->playerPos[i].second, graphicLib, {0, 255, 255, 255},
					 true);

		} else
			this->drawPlayer(this->playerPos[i].first, this->playerPos[i].second, graphicLib, {244, 255, 255, 255},
					 true);
	}
}

void Arcade::LibPacman::drawPlayer(size_t x, size_t y, IGraphicLib &graphicLib,
	Color color, bool space)
{
	y = y * this->resize.getY();
	x = x * this->resize.getX();
	Arcade::PixelBox pixelBox({this->resize.getX(), this->resize.getY()}, {y , x}, color);
	if (space && graphicLib.getName() != "Ncurses")
		pixelBox.setSize({this->resize.getX() - 1, this->resize.getY() - 1});
	graphicLib.drawPixelBox(pixelBox);
}

void Arcade::LibPacman::movePlayer(Keys dir)
{
	switch ((int)dir) {
		case Keys::Z:
			this->pos.first++;
			break;
		case Keys::S :
			this->pos.first++;
			break;
		case Keys::Q :
			this->pos.second--;
			break;
		case Keys::D :
			this->pos.second++;
			break;
		default:
			break;
	}
	if (this->checkEnd())
		exit(0);
}

bool Arcade::LibPacman::checkEnd()
{
	bool ret = false;

	for (int i = 1; i < (int)this->playerPos.size(); i++) {
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
	if (PACMAN_MAP[this->playerPos[0].first][this->playerPos[0].second] == 'X')
		return true;
	return ret;
}

bool Arcade::LibPacman::canGoBack(Keys key)
{
	bool ret = true;

	if (this->playerPos.size() == 1)
		ret =  true;
	else if (key == Keys::Z && this->playerPos[1].first + 1 != this->playerPos[0].first) {
		ret = true;
	} else if (key == Keys::S && this->playerPos[1].first - 1 != this->playerPos[0].first) {
		ret = true;

	} else if (key == Keys::Q && this->playerPos[1].second + 1 != this->playerPos[0].second) {
		ret = true;

	} else if (key == Keys::D && this->playerPos[1].second - 1 != this->playerPos[0].second) {
		ret = true;
	} else
		ret = false;
	return ret;
}

size_t Arcade::LibPacman::getScore()
{
	return this->score;
}