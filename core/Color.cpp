/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Color.cpp
*/

#include "Color.hpp"

Arcade::Color::Color(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha) :
	_red(red), _green(green), _blue(blue), _alpha(alpha)
{

}

void Arcade::Color::setColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	this->_red = red;
	this->_green = green;
	this->_blue = blue;
	this->_alpha = alpha;
}

unsigned char Arcade::Color::getRed() const
{
	return this->_red;
}

unsigned char Arcade::Color::getGreen() const
{
	return this->_green;
}

unsigned char Arcade::Color::getBlue() const
{
	return this->_blue;
}

unsigned char Arcade::Color::getAlpha() const
{
	return this->_alpha;
}

void Arcade::Color::setRed(unsigned char red)
{
	this->_red = red;
}

void Arcade::Color::setGreen(unsigned char green)
{
	this->_green = green;
}

void Arcade::Color::setBlue(unsigned char blue)
{
	this->_blue = blue;
}

void Arcade::Color::setAlpha(unsigned char alpha)
{
	this->_alpha = alpha;
}

Arcade::Color::operator unsigned char *()
{
	return &this->_red;
}

bool Arcade::Color::operator!=(const Color &ocolor)
{
	bool ret = false;

	if (this->getRed() != ocolor.getRed())
		ret = true;
	else if (this->getGreen() != ocolor.getGreen())
		ret = true;
	else if (this->getBlue() != ocolor.getBlue())
		ret = true;
	return ret;
}
