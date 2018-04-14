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
#include <functional>
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

static const std::vector<std::function<short(
	const Arcade::Color &)>>
	NCURSES_COLOR = {
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getRed()) > 80 &&
		    PERCENT(color.getGreen()) > 80 &&
		    PERCENT(color.getBlue()) > 80)
			return COLOR_WHITE;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getGreen()) < 80 &&
		    PERCENT(color.getRed()) < 80 &&
		    PERCENT(color.getBlue()) < 80)
			return COLOR_BLACK;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getRed()) > 80 &&
			PERCENT(color.getGreen()) > 80)
			return COLOR_YELLOW;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getGreen()) < 80 &&
		    PERCENT(color.getRed()) > 80 &&
		    PERCENT(color.getBlue()) < 80)
			return COLOR_RED;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getGreen()) > 80 &&
		    PERCENT(color.getRed()) < 80 &&
		    PERCENT(color.getBlue()) < 80)
			return COLOR_GREEN;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getGreen()) < 80 &&
		    PERCENT(color.getRed()) < 80 &&
		    PERCENT(color.getBlue()) > 80)
			return COLOR_BLUE;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getRed()) > 80 &&
		    PERCENT(color.getBlue()) > 80)
			return COLOR_MAGENTA;
		return -1;
	}},
	{[](const Arcade::Color &color) {
		if (PERCENT(color.getGreen()) > 80 &&
		    PERCENT(color.getBlue()) > 80)
			return COLOR_CYAN;
		return -1;
	}}
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
	timeout(0);
	int event = getch();

	if (event != 0 && event != ERR) {
		if (NCURSES_KEYS.find(event) != NCURSES_KEYS.end())
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
	this->screenSize.setX(static_cast<size_t>(COLS));
	this->screenSize.setY(static_cast<size_t>(LINES));
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
	start_color();
	cbreak();
	noecho();
	keypad(this->window, true);
	this->screenSize.setX(static_cast<size_t>(COLS));
	this->screenSize.setY(static_cast<size_t>(LINES));

}

void Arcade::LibNcurses::drawPixelBox(Arcade::PixelBox &box)
{
	for (int i = 0; i < (int)box.getHeight(); i++) {
		for (int j = 0; j < (int)box.getWidth(); j++) {
			auto px = static_cast<int>(box.getX() + i);
			auto py = static_cast<int>(box.getY() + j);
			Color value = box.getPixel(j + i * box.getWidth());
			this->drawPixel(px, py, ' ', value);
		}
	}
}

void Arcade::LibNcurses::drawPixel(int x, int y, char c,
	const Arcade::Color &color)
{
	short pair = 0;

	this->init_ncurse_color(color, color, pair);
	mvprintw(y, x, "%c", c);
	this->resetColor(pair);
}

void Arcade::LibNcurses::init_ncurse_color(const Arcade::Color &c,
	const Arcade::Color &bc, short &pair)
{
	short i;

	i = this->findInColors(c, bc);
	if (i < 0) {
		this->colors.emplace_back(c, bc);
		pair = static_cast<short>(this->colors.size());
	}
	else
		pair = static_cast<short>(i + 1);
	init_pair(pair, this->translateColor(c), this->translateColor(bc));
	attron(COLOR_PAIR(pair));
}

void Arcade::LibNcurses::drawText(Arcade::TextBox &text)
{
	short pair = 0;

	this->init_ncurse_color(text.getColor(), text.getBackgroundColor(),
				pair);
	mvprintw(static_cast<int>(text.getY()), static_cast<int>(text.getX()),
		 "%s", text.getValue().c_str());
	this->resetColor(pair);
}

void Arcade::LibNcurses::resetColor(short pair)
{
	attroff(COLOR_PAIR(pair));
}

std::string Arcade::LibNcurses::getName() const
{
	return "Ncurses";
}

short Arcade::LibNcurses::translateColor(const Arcade::Color &color)
{
	short col;

	for (const auto &i : NCURSES_COLOR) {
		col = i(color);
		if (col != -1)
			return col;
	}
	return 0;
}

short
Arcade::LibNcurses::findInColors(const Arcade::Color &c,
	const Arcade::Color &bc)
{
	size_t i = 0;
	bool ctn = true;

	for (i = 0 ; i < this->colors.size() && ctn ; i++) {
		if (this->colors[i].first == c && this->colors[i].second == bc)
			ctn = false;
	}
	if (ctn)
		return -1;
	return static_cast<short>(i);
}
