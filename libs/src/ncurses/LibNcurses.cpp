/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibNcurses.cpp
*/

#include <ncurses.h>
#include <unordered_map>
#include <sys/ioctl.h>
#include <iostream>
#include "LibNcurses.hpp"

static const std::unordered_map<int, Arcade::Keys> NCURSES_KEYS = {
	{0,             Arcade::NONE},
	{'a',           Arcade::A},
	{'b',           Arcade::B},
	{'c',           Arcade::C},
	{'d',           Arcade::D},
	{'e',           Arcade::E},
	{'f',           Arcade::F},
	{'g',           Arcade::G},
	{'h',           Arcade::H},
	{'i',           Arcade::I},
	{'j',           Arcade::J},
	{'k',           Arcade::K},
	{'l',           Arcade::L},
	{'m',           Arcade::M},
	{'n',           Arcade::N},
	{'o',           Arcade::O},
	{'p',           Arcade::P},
	{'q',           Arcade::Q},
	{'r',           Arcade::R},
	{'s',           Arcade::S},
	{'t',           Arcade::T},
	{'u',           Arcade::U},
	{'v',           Arcade::V},
	{'w',           Arcade::W},
	{'x',           Arcade::X},
	{'y',           Arcade::Y},
	{'z',           Arcade::Z},
	{KEY_LEFT,      Arcade::LEFT},
	{KEY_RIGHT,     Arcade::RIGHT},
	{KEY_UP,        Arcade::UP},
	{KEY_DOWN,      Arcade::DOWN},
	{KEY_ENTER,     Arcade::ENTER},
	{' ',           Arcade::SPACE},
	{KEY_DL,        Arcade::DELETE},
	{KEY_BACKSPACE, Arcade::BACKSPACE},
	{KEY_BTAB,      Arcade::TAB},
	{27,            Arcade::ESC},
	{KEY_MOUSE,     Arcade::MOUSELEFT},
	{KEY_MOUSE,     Arcade::MOUSERIGHT}
};

// the screen size given by the user is useless, the screen size is defined
// by the size of the terminal.
Arcade::LibNcurses::LibNcurses(Arcade::Vect<size_t> screenSize,
	const std::string &title)
{
	(void) screenSize;
	this->openRenderer(title);
}

Arcade::LibNcurses::~LibNcurses()
{
	this->closeRenderer();
}

bool Arcade::LibNcurses::pollEvents()
{
	int event = getch();

	if (event != 0) {
		this->events.push(NCURSES_KEYS.at(event));
	}
	return !this->events.empty();
}

Arcade::Keys Arcade::LibNcurses::getLastEvent()
{
	Arcade::Keys ret = this->events.back();
	this->events.pop();
	return ret;
}

void Arcade::LibNcurses::clearEvents()
{
	while (!this->events.empty())
		this->events.pop();
}

Arcade::Vect<size_t> Arcade::LibNcurses::getScreenSize() const
{
	return this->screenSize;
}

size_t Arcade::LibNcurses::getMaxX() const
{
	return this->screenSize.getX();
}

size_t Arcade::LibNcurses::getMaxY() const
{
	return this->screenSize.getY();
}

void Arcade::LibNcurses::refreshWindow()
{
	refresh();
}

void Arcade::LibNcurses::clearWindow()
{
	clear();
}

bool Arcade::LibNcurses::isOpen() const
{
	return this->window != nullptr;
}

void Arcade::LibNcurses::closeRenderer()
{
	endwin();
	this->window = nullptr;
}

void Arcade::LibNcurses::openRenderer(std::string const &title)
{
	(void) title;
	this->window = initscr();
	curs_set(0);
	keypad(this->window, true);
	struct winsize size{};
	ioctl(0, TIOCGWINSZ, &size);
	this->screenSize.setX(size.ws_col);
	this->screenSize.setY(size.ws_row);
}

void Arcade::LibNcurses::drawPixelBox(Arcade::PixelBox &box)
{
	for (size_t y = 0 ; y < box.getHeight() ; y++) {
		for (size_t x = 0 ; x < box.getWidth() ; x++) {
			auto px = static_cast<int>(box.getX() + x);
			auto py = static_cast<int>(box.getY() + y);
			Color value = box.getPixel(px + py * box.getWidth());
			this->drawChar(px, py, ' ', value);
		}
	}
}

void Arcade::LibNcurses::drawText(Arcade::TextBox &text)
{
	mvprintw(static_cast<int>(text.getX()), static_cast<int>(text.getY()),
		 "%s%s%s%s",
		 this->convertColor(text.getBackgroundColor()),
		 this->convertColor(text.getColor(), true), text.getValue(),
		 this->resetColor());
}

void Arcade::LibNcurses::drawChar(int x, int y, char c,
	const Arcade::Color &color)
{
	mvprintw(x, y, "%s%c%s", this->convertColor(color), c,
		 this->resetColor());
}

const char *Arcade::LibNcurses::convertColor(const Arcade::Color &color,
	bool front)
{
	std::string col;

	if (front)
		col += "\e[38;5";
	else
		col += "\e[48;5";
	col += color.getRed();
	col += ";";
	col += color.getGreen();
	col += ";";
	col += color.getBlue();
	col += "m";
	return col.c_str();
}

const char *Arcade::LibNcurses::resetColor()
{
	return "\e[0m";
}

std::string Arcade::LibNcurses::getName() const
{
	return "Ncurses";
}
