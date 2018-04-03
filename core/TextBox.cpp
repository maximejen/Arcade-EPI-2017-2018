/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** TextBox.cpp
*/

#include <cstddef>
#include "TextBox.hpp"

Arcade::TextBox::TextBox(const std::string &text, Arcade::Vect<size_t> pos,
	size_t fontSize, Arcade::Color color, Arcade::Color backgroundColor) :
	_value(text), _pos(pos), _size(fontSize), _color(color),
	_bgColor(backgroundColor)
{

}

const std::string &Arcade::TextBox::getValue() const
{
	return this->_value;
}

void Arcade::TextBox::setValue(std::string const &text)
{
	this->_value = text;
}

Arcade::Vect<size_t> Arcade::TextBox::getPos() const
{
	return this->_pos;
}

void Arcade::TextBox::setPos(Arcade::Vect<size_t> pos)
{
	this->_pos = pos;
}

size_t Arcade::TextBox::getX() const
{
	return this->_pos.getX();
}

size_t Arcade::TextBox::getY() const
{
	return this->_pos.getY();
}

void Arcade::TextBox::setX(size_t x)
{
	this->_pos.setX(x);
}

void Arcade::TextBox::setY(size_t y)
{
	this->_pos.setY(y);
}

size_t Arcade::TextBox::getFontSize() const
{
	return this->_size;
}

void Arcade::TextBox::setFontSize(size_t size)
{
	this->_size = size;
}

Arcade::Color Arcade::TextBox::getColor() const
{
	return this->_color;
}

void Arcade::TextBox::setColor(Arcade::Color color)
{
	this->_color = color;
}

Arcade::Color Arcade::TextBox::getBackgroundColor() const
{
	return this->_bgColor;
}

void Arcade::TextBox::setBackgroundColor(Arcade::Color color)
{
	this->_bgColor = color;
}
