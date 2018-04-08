/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSFML.cpp
*/

#include <unordered_map>
#include <iostream>
#include "LibSFML.hpp"

static const std::unordered_map<sf::Keyboard::Key, Arcade::Keys> SFML_KEYS = {
	{sf::Keyboard::Unknown,   Arcade::NONE},
	{sf::Keyboard::A,         Arcade::A},
	{sf::Keyboard::B,         Arcade::B},
	{sf::Keyboard::C,         Arcade::C},
	{sf::Keyboard::D,         Arcade::D},
	{sf::Keyboard::E,         Arcade::E},
	{sf::Keyboard::F,         Arcade::F},
	{sf::Keyboard::G,         Arcade::G},
	{sf::Keyboard::H,         Arcade::H},
	{sf::Keyboard::I,         Arcade::I},
	{sf::Keyboard::J,         Arcade::J},
	{sf::Keyboard::K,         Arcade::K},
	{sf::Keyboard::L,         Arcade::L},
	{sf::Keyboard::M,         Arcade::M},
	{sf::Keyboard::N,         Arcade::N},
	{sf::Keyboard::O,         Arcade::O},
	{sf::Keyboard::P,         Arcade::P},
	{sf::Keyboard::Q,         Arcade::Q},
	{sf::Keyboard::R,         Arcade::R},
	{sf::Keyboard::S,         Arcade::S},
	{sf::Keyboard::T,         Arcade::T},
	{sf::Keyboard::U,         Arcade::U},
	{sf::Keyboard::V,         Arcade::V},
	{sf::Keyboard::W,         Arcade::W},
	{sf::Keyboard::X,         Arcade::X},
	{sf::Keyboard::Y,         Arcade::Y},
	{sf::Keyboard::Z,         Arcade::Z},
	{sf::Keyboard::Left,      Arcade::LEFT},
	{sf::Keyboard::Right,     Arcade::RIGHT},
	{sf::Keyboard::Up,        Arcade::UP},
	{sf::Keyboard::Down,      Arcade::DOWN},
	{sf::Keyboard::Return,    Arcade::ENTER},
	{sf::Keyboard::Space,     Arcade::SPACE},
	{sf::Keyboard::Delete,    Arcade::DELETE},
	{sf::Keyboard::BackSpace, Arcade::BACKSPACE},
	{sf::Keyboard::Tab,       Arcade::TAB},
	{sf::Keyboard::Escape,    Arcade::ESC},
	{sf::Keyboard::M,         Arcade::MOUSELEFT},
	{sf::Keyboard::M,         Arcade::MOUSERIGHT}
};

Arcade::LibSFML::LibSFML(Arcade::Vect<size_t> screenSize,
	const std::string &title) : screenSize(screenSize),
				    sprite(this->texture)
{
	this->texture.create(800, 800);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition({0, 0});
	this->screenSize.setX(800);
	this->screenSize.setY(800);
	this->window.create({800, 800, 32}, title);
}

Arcade::LibSFML::~LibSFML()
{
	this->closeRenderer();
}

std::string Arcade::LibSFML::getName() const
{
	return "SFML";
}

bool Arcade::LibSFML::isOpen() const
{
	return this->window.isOpen();
}

void Arcade::LibSFML::closeRenderer()
{
	this->window.close();
}

void Arcade::LibSFML::openRenderer(std::string const &title)
{
	this->texture.create(800, 800);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition({0, 0});
	this->window.create({800, 800, 32}, title);
}

void Arcade::LibSFML::clearWindow()
{
	if (this->isOpen())
		this->window.clear({0, 0, 0, 255});
}

void Arcade::LibSFML::refreshWindow()
{
	if (this->isOpen())
		this->window.display();
}

bool Arcade::LibSFML::pollEvents()
{
	sf::Event event{};

	while (this->window.pollEvent(event)) {
		try {
			this->events.push(SFML_KEYS.at(event.key.code));
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return !this->events.empty();
}

Arcade::Keys Arcade::LibSFML::getLastEvent()
{
	Arcade::Keys event = this->events.front();
	this->events.pop();
	return event;
}

size_t Arcade::LibSFML::getMaxX() const
{
	return this->screenSize.getX();
}

size_t Arcade::LibSFML::getMaxY() const
{
	return this->screenSize.getY();
}

Arcade::Vect<size_t> Arcade::LibSFML::getScreenSize() const
{
	return this->screenSize;
}

void Arcade::LibSFML::clearEvents()
{
	while (!this->events.empty())
		this->events.pop();
}

void Arcade::LibSFML::drawPixelBox(Arcade::PixelBox &b)
{
	if (this->isOpen()) {
		auto array = &b.getPixelArray()[0];
		this->texture.update((unsigned char *) array,
				     static_cast<unsigned int>(b.getWidth()),
				     static_cast<unsigned int>(b.getHeight()),
				     static_cast<unsigned int>(0),
				     static_cast<unsigned int>(0));
		this->sprite.setPosition(b.getX(), b.getY());
		this->sprite.setTextureRect({static_cast<int>(0),
					     static_cast<int>(0),
					     static_cast<int>(800),
					     static_cast<int>(800)});
		this->window.draw(this->sprite);
	}
}

void Arcade::LibSFML::drawText(Arcade::TextBox &t)
{
	sf::Font font;
	sf::Text text;

	if (!font.loadFromFile("./libs/src/SFML/OpenSans-Bold.ttf")) {
		text.setFont(font);
		text.setString(t.getValue());
		text.setCharacterSize(
			static_cast<unsigned int>(t.getFontSize()));
		text.setColor(this->transformColor(t.getColor()));
		this->window.draw(text);
	}
}

sf::Color Arcade::LibSFML::transformColor(const Arcade::Color &color)
{
	sf::Color col;

	col.r = color.getRed();
	col.g = color.getGreen();
	col.b = color.getBlue();
	col.a = color.getAlpha();
	return col;
}
