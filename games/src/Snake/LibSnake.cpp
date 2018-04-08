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
	this->score =0;
}

Arcade::LibSnake::~LibSnake()
{

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

	pos.first = rand() % MAP_WIDTH;
	pos.second = rand() % MAP_HEIGHT;
	pos.first = 10;
	pos.second = 10;
	this->playerPos.push_back(pos);
	this->setObjectPos();
	//this->resize.setX(0);
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
	this->curKey = key;
}

void Arcade::LibSnake::update()
{

	time_t curTime;
	time(&curTime);
	if (curTime == this->timer)
		return;
	if (curKey == Keys::NONE || !this->canGoBack(this->curKey)) {
		this->movePlayer(this->lastKey);
	} else {
		this->movePlayer(this->curKey);
		std::cout << "moved" << std::endl;
		this->lastKey = this->curKey;
		this->curKey = Keys::NONE;
	}
	if (this->playerPos[0].first == (int)this->objectPos.getY() &&
		this->playerPos[0].second == (int)this->objectPos.getX()) {
		std::cout << "Found" << std::endl;
		this->score++;
	}
	time(&this->timer);
}

void Arcade::LibSnake::refresh(IGraphicLib &graphicLib)
{
	Vect<size_t> size = graphicLib.getScreenSize();
	if (this->resize.getX() == 0) {
		this->resize.setX(size.getX() / MAP_WIDTH);
		this->resize.setY(size.getY() / MAP_HEIGHT);
	}
	graphicLib.clearWindow();

	this->display(graphicLib);

	graphicLib.refreshWindow();
}

void Arcade::LibSnake::display(IGraphicLib &graphicLib)
{
	this->drawPlayer(this->objectPos.getY(), this->objectPos.getX(), graphicLib, 200);
	for (int i = 0; i < (int)this->playerPos.size(); i++) {
		this->drawPlayer(this->playerPos[i].first, this->playerPos[i].second, graphicLib, 255);
	}
}

void Arcade::LibSnake::drawPlayer(size_t y, size_t x, IGraphicLib &graphicLib,
				  unsigned char color)
{
	y = y * this->resize.getY();
	x = x * this->resize.getX();
	Arcade::PixelBox pixelBox({this->resize.getX(), this->resize.getY()}, {y , x}, {color, color, color, 255});
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
	int pos = this->checkFood(dir);
	if (pos == 1)
		this->setObjectPos();
	this->moveSnake();
	if (dir == Keys::Z) {
		this->playerPos[0].first--;

	} else if (dir == Keys::S) {
		this->playerPos[0].first++;

	} else if (dir == Keys::Q) {
		this->playerPos[0].second--;

	} else if (dir == Keys::D) {
		this->playerPos[0].second++;
	}

	/*for (int i = 1; i < (int)this->playerPos.size(); i++) {
		if (this->playerPos[0] == this->playerPos[i]) {
			std::cout << "Exiting" << std::endl;
			exit(0);
		}
	}*/

}

bool Arcade::LibSnake::canGoBack(Keys key)
{
	bool ret = true;

	if (this->playerPos.size() == 1)
		ret =  true;
	else if (key == Keys::Z) {
		ret = false;
	} else if (key == Keys::S) {
		ret = false;

	} else if (key == Keys::Q) {
		ret = false;

	} else if (key == Keys::D) {
		ret = false;
	}
	return ret;
}

void Arcade::LibSnake::moveSnake()
{
	auto tmp = this->playerPos;
	if (this->playerPos.size() == 1)
		return;
	for (int i = 1; i < (int)this->playerPos.size(); i++) {
		this->playerPos[i].first = tmp[i -1].first;
		this->playerPos[i].second = tmp[i -1].second;
	}
}

size_t Arcade::LibSnake::getScore()
{
	return 0;
}