/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibNcurses.hpp
*/

#ifndef CPP_ARCADE_LIBNCURSES_HPP_
	#define CPP_ARCADE_LIBNCURSES_HPP_

	#include <queue>
	#include "../IGraphicLib.hpp"

namespace Arcade {
	class LibNcurses : public IGraphicLib {
	public:
		LibNcurses(Vect<size_t> screenSize);
		~LibNcurses() override;

		bool isOpen() const;
		void closeRenderer() override;
		void openRenderer(std::string const &title) override;
		void clearWindow() override;
		void refreshWindow() override;

		void drawPixelBox(PixelBox &);

		void drawText(TextBox &);

		bool pollEvents() override;
		Keys getLastEvent() override;
		void clearEvents() override;

		Vect<size_t> getScreenSize();

		size_t getMaxX() const override;
		size_t getMaxY() const override;

	private:
		std::queue<Arcade::Keys> events;
		Vect<size_t> screenSize;
		WINDOW *window;
	};
}


#endif //CPP_ARCADE_LIBNCURSES_HPP_
