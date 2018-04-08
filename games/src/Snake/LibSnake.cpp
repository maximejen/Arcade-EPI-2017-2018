/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include <ios>
#include <iostream>
#include <cstdlib>
#include "LibSnake.hpp"

Arcade::LibSnake::LibSnake()
{
	srand (time(NULL));
	this->init();
	this->curKey = Keys::NONE;
	this->lastKey = Keys::Z;
	this->score = 0;
	this->msgScore = new TextBox("Score: " + std::to_string(this->score), {0, 0}, 25, {120, 120,120, 120}, {255, 255, 255, 255});
}

Arcade::LibSnake::~LibSnake()
{
	delete this->msgScore;
}

const std::string Arcade::LibSnake::getName() const
{
	return "Snake";
}

bool Arcade::LibSnake::init()
{
	std::pair<int, int> pos;

	this->mapSize.setX(MAP_WIDTH);
	this->mapSize.setY(MAP_HEIGHT);

	pos.first = rand() % MAP_WIDTH / 2 + 3;
	pos.second = rand() % MAP_HEIGHT / 2 + 3;
	this->playerPos.push_back(pos);
	pos.first = this->playerPos[0].first + 1;
	pos.second = this->playerPos[0].second;
	this->playerPos.push_back(pos);
	pos.first = this->playerPos[0].first + 2;
	pos.second = this->playerPos[0].second;
	this->playerPos.push_back(pos);

	this->setObjectPos();
	time(&this->timer);

	return true;
}

void Arcade::LibSnake::setObjectPos()
{
	this->objectPos.setY(rand() % MAP_HEIGHT);
	this->objectPos.setX(rand() % MAP_WIDTH);
}

bool Arcade::LibSnake::stop()
{
	return true;
}

void Arcade::LibSnake::applyEvent(Keys key)
{
	//if (key == Keys::Z || key == Keys::Q || key == Keys::S || key == Keys::D)
		this->curKey = key;
}

void Arcade::LibSnake::update()
{

	time_t curTime;
	time(&curTime);
	if (curTime == this->timer)
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
	time(&this->timer);
}

void Arcade::LibSnake::refresh(IGraphicLib &graphicLib)
{
	if (this->resize.getX() == 0) {
		Vect<size_t> size = graphicLib.getScreenSize();
		this->resize.setX(size.getX() / MAP_WIDTH);
		this->resize.setY(size.getY() / MAP_HEIGHT);
	}
	graphicLib.clearWindow();
	this->display(graphicLib);
	graphicLib.drawText(*this->msgScore);
	graphicLib.refreshWindow();
}

void Arcade::LibSnake::display(IGraphicLib &graphicLib)
{
	this->drawPlayer(this->objectPos.getY(), this->objectPos.getX(), graphicLib, {244, 65, 65, 255});
	for (int i = 0; i < (int)this->playerPos.size(); i++) {
		this->drawPlayer(this->playerPos[i].first, this->playerPos[i].second, graphicLib, {244, 255, 255, 255});
	}
}

void Arcade::LibSnake::drawPlayer(size_t y, size_t x, IGraphicLib &graphicLib,
				  Color color)
{
	y = y * this->resize.getY();
	x = x * this->resize.getX();
	Arcade::PixelBox pixelBox({this->resize.getX() - 1, this->resize.getY() - 1}, {y , x}, color);
	graphicLib.drawPixelBox(pixelBox);
}

int Arcade::LibSnake::checkFood(Keys dir)
{
	if (dir == Keys::Z) {
		if (this->playerPos[0].first -1 == (int)this->objectPos.getY() &&
		    this->playerPos[0].second == (int)this->objectPos.getX()) {
			this->playerPos.insert(this->playerPos.begin(), std::make_pair(this->playerPos[0].first - 1, this->playerPos[0].second));
			return (1);
		}
	}
	else if (dir == Keys::S) {
		if (this->playerPos[0].first + 1 == (int)this->objectPos.getY() &&
		    this->playerPos[0].second == (int)this->objectPos.getX()) {
			this->playerPos.insert(this->playerPos.begin(), std::make_pair(this->playerPos[0].first + 1, this->playerPos[0].second));
			return (1);
		}
	}
	else if (dir == Keys::Q) {
		if (this->playerPos[0].first == (int)this->objectPos.getY() &&
		    this->playerPos[0].second -1 == (int)this->objectPos.getX()) {
			this->playerPos.insert(this->playerPos.begin(), std::make_pair(this->playerPos[0].first, this->playerPos[0].second - 1));
			return (1);
		}
	}
	else if (dir == Keys::D) {
		if (this->playerPos[0].first == (int)this->objectPos.getY() &&
		    this->playerPos[0].second + 1 == (int)this->objectPos.getX()) {
			this->playerPos.insert(this->playerPos.begin(), std::make_pair(this->playerPos[0].first, this->playerPos[0].second +1));
			return (1);
		}
	}
	return (0);
}



void Arcade::LibSnake::movePlayer(Keys dir)
{
	std::cout << "key : " << dir << std::endl;
	if (this->checkFood(dir) == 1) {
		this->setObjectPos();
		this->score++;
		this->msgScore->setValue("Score: " + this->score);
	}
	this->moveSnake();
	switch ((int)dir) {
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

bool Arcade::LibSnake::checkEnd()
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
	return ret;
}

bool Arcade::LibSnake::canGoBack(Keys key)
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

	} else if (key == Keys::D && this->playerPos[1].second + 1 != this->playerPos[0].second) {
		ret = true;
	} else
		ret = false;
	return ret;
}

void Arcade::LibSnake::moveSnake()
{
	auto tmp = this->playerPos;
	for (int i = 1; i < (int)this->playerPos.size(); i++) {
		this->playerPos[i].first = tmp[i -1].first;
		this->playerPos[i].second = tmp[i -1].second;
	}
}

size_t Arcade::LibSnake::getScore()
{
	return this->score;
}