/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSFML.hpp
*/

#ifndef CPP_ARCADE_LIBSFML_HPP
#define CPP_ARCADE_LIBSFML_HPP

#include <queue>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../IGraphicLib.hpp"

namespace Arcade {
	class LibSFML : public IGraphicLib {
	public:
		LibSFML(Vect<size_t> screenSize, const std::string &title);
		~LibSFML() override;

		std::string getName() const override;

		bool isOpen() const override;
		void closeRenderer() override;
		void openRenderer(std::string const &title) override;
		void clearWindow() override;
		void refreshWindow() override;

		void drawPixelBox(PixelBox &) override;

		void drawText(TextBox &) override;

		bool pollEvents() override;
		Keys getLastEvent() override;
		void clearEvents() override;

		Vect<size_t> getScreenSize() const override;

		size_t getMaxX() const override;
		size_t getMaxY() const override;

		sf::Color transformColor(const Color &color);

	private:
		std::queue<Arcade::Keys> events;
		Vect<size_t> screenSize;
		sf::RenderWindow window;
		sf::Texture texture;
		sf::Sprite sprite;
	};
};


#endif //CPP_ARCADE_LIBSFML_HPP
