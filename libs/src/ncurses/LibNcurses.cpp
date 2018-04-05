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
#include <algorithm>
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
	{36,            Arcade::ESC},
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
	timeout(10);
	int event = getch();

	if (event != 0 && event != ERR) {
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
	start_color();
	cbreak();
	noecho();
}

void Arcade::LibNcurses::drawPixelBox(Arcade::PixelBox &box)
{
	for (size_t y = 0 ; y < box.getHeight() ; y++) {
		for (size_t x = 0 ; x < box.getWidth() ; x++) {
			auto px = static_cast<int>(box.getX() + x);
			auto py = static_cast<int>(box.getY() + y);
			Color value = box.getPixel(px + py * box.getWidth());
			this->drawPixel(px, py, ' ', value);
		}
	}
}

void Arcade::LibNcurses::drawText(Arcade::TextBox &text)
{
	this->init_ncurse_color(text.getColor(), text.getBackgroundColor());
	mvprintw(static_cast<int>(text.getY()), static_cast<int>(text.getX()),
		 "%s", text.getValue().c_str());
	this->resetColor();
}

void Arcade::LibNcurses::drawPixel(int x, int y, char c,
	const Arcade::Color &color)
{
	this->init_ncurse_color(color, color);
	mvprintw(y, x, "%c", c);
	this->resetColor();
}

void Arcade::LibNcurses::init_ncurse_color(const Arcade::Color &c,
	const Arcade::Color &bc)
{
	std::pair<Arcade::Color, Arcade::Color> pair(c, bc);
	size_t i;

	for (i = 0 ; i < this->colors.size() &&
		pair.first != this->colors[i].first &&
		pair.second != this->colors[i].second; i++);
	if (i == this->colors.size()) {
		this->colors.emplace_back(c, bc);
	}
	init_color(COLOR_RED, static_cast<short>(T_VALUE(c.getRed())),
		   static_cast<short>(T_VALUE(c.getGreen())),
		   static_cast<short>(T_VALUE(c.getBlue())));
	init_color(COLOR_BLUE, static_cast<short>(T_VALUE(bc.getRed())),
		   static_cast<short>(T_VALUE(bc.getGreen())),
		   static_cast<short>(T_VALUE(bc.getBlue())));
	init_pair(static_cast<short>(i), COLOR_RED, COLOR_BLUE);
	attron(COLOR_PAIR(1));
}

void Arcade::LibNcurses::resetColor()
{
	attroff(COLOR_PAIR(1));
}

std::string Arcade::LibNcurses::getName() const
{
	return "Ncurses";
}
