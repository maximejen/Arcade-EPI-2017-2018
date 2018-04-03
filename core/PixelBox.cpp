/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** PixelBox.cpp
*/

#include "PixelBox.hpp"

Arcade::PixelBox::PixelBox(Vect<size_t> size, Vect<size_t> pos, Color col) :
	_size(size), _pos(pos)
{
	for (int i = 0; i < (int)size.getX(); i++) {
		for (int j = 0; j < (int)size.getY(); j++) {
			this->_colorFrame.push_back(col);
		}
	}
}

size_t Arcade::PixelBox::getHeight() const
{
	return this->_size.getY();
}

size_t Arcade::PixelBox::getWidth() const
{
	return this->_size.getX();
}

size_t Arcade::PixelBox::getY() const
{
	return this->_pos.getY();
}

size_t Arcade::PixelBox::getX() const
{
	return this->_pos.getX();
}

void Arcade::PixelBox::setHeight(size_t height)
{
	this->_size.setY(height);
}

void Arcade::PixelBox::setWidth(size_t width)
{
	this->_size.setX(width);
}

void Arcade::PixelBox::setY(size_t y)
{
	this->_pos.setY(y);
}

void Arcade::PixelBox::setX(size_t x)
{
	this->_pos.setX(x);
}

Arcade::Vect<size_t> Arcade::PixelBox::getSize() const
{
	return this->_size;
}

void Arcade::PixelBox::setSize(Vect<size_t> size)
{
	this->_size = size;
}

Arcade::Vect<size_t> Arcade::PixelBox::getPos() const
{
	return this->_pos;
}

void Arcade::PixelBox::setPos(Vect<size_t> pos)
{
	this->_pos = pos;
}

void Arcade::PixelBox::putPixel(Vect<size_t> pos, Color col)
{
	this->_colorFrame[pos.getX() * pos.getY()] = col;
}

Arcade::Color Arcade::PixelBox::getPixel(Vect<size_t> pos) const
{
	return this->_colorFrame[pos.getX() * pos.getY()];
}

std::vector<Arcade::Color>& Arcade::PixelBox::getPixelArray()
{
	return this->_colorFrame;
}
