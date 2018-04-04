/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibNcurses.cpp
*/

#include <ncurses.h>
#include <sys/ioctl.h>
#include "LibNcurses.hpp"

// the screen size given by the user is useless, the screen size is defined
// by the size of the terminal.
Arcade::LibNcurses::LibNcurses(Arcade::Vect<size_t> screenSize)
{
	(void)screenSize;
	this->window = initscr();
	curs_set(0);
	keypad(this->window, 1);
	// Todo : Here init the ncurses, define all the private variables.
}

Arcade::LibNcurses::~LibNcurses()
{
	endwin();
}

bool Arcade::LibNcurses::pollEvents()
{
//	int event = getch();
	// Todo : Get the events using getch and then add them to the event queue.
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

Arcade::Vect<size_t> Arcade::LibNcurses::getScreenSize()
{
	struct winsize size{};

	ioctl(0, TIOCGWINSZ, &size);
	this->screenSize.setX(size.ws_col);
	this->screenSize.setY(size.ws_row);
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
