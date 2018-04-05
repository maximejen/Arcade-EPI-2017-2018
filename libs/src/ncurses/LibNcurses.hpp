/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibNcurses.hpp
*/

#ifndef CPP_ARCADE_LIBNCURSES_HPP_
	#define CPP_ARCADE_LIBNCURSES_HPP_

	#include <queue>
	#include <ncurses.h>
	#include <map>
	#include <list>
	#include <sys/ioctl.h>
	#include "../IGraphicLib.hpp"

namespace Arcade {
	#define T_VALUE(x) (x * 3.9)

	class LibNcurses : public IGraphicLib {
	public:
		LibNcurses(Vect<size_t> screenSize, const std::string &title);
		~LibNcurses() override;

		std::string getName() const override;

		bool isOpen() const override;
		void closeRenderer() override;
		void openRenderer(std::string const &title) override;
		void clearWindow() override;
		void refreshWindow() override;

		void drawPixelBox(PixelBox &) override;
		void drawPixel(int x, int y, char c, const Color &color);
		void init_ncurse_color(const Color &, const Color &);
		void resetColor();

		void drawText(TextBox &) override;

		bool pollEvents() override;
		Keys getLastEvent() override;
		void clearEvents() override;

		Vect<size_t> getScreenSize() const override;

		size_t getMaxX() const override;
		size_t getMaxY() const override;

	private:
		std::queue<Arcade::Keys> events;
		Vect<size_t> screenSize;
		WINDOW *window;
		std::vector<std::pair<Arcade::Color, Arcade::Color>> colors;
	};
}


#endif //CPP_ARCADE_LIBNCURSES_HPP_
