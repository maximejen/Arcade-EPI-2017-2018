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
	{sf::Keyboard::Unknown,   Arcade::Keys::NONE},
	{sf::Keyboard::A,         Arcade::Keys::A},
	{sf::Keyboard::B,         Arcade::Keys::B},
	{sf::Keyboard::C,         Arcade::Keys::C},
	{sf::Keyboard::D,         Arcade::Keys::D},
	{sf::Keyboard::E,         Arcade::Keys::E},
	{sf::Keyboard::F,         Arcade::Keys::F},
	{sf::Keyboard::G,         Arcade::Keys::G},
	{sf::Keyboard::H,         Arcade::Keys::H},
	{sf::Keyboard::I,         Arcade::Keys::I},
	{sf::Keyboard::J,         Arcade::Keys::J},
	{sf::Keyboard::K,         Arcade::Keys::K},
	{sf::Keyboard::L,         Arcade::Keys::L},
	{sf::Keyboard::M,         Arcade::Keys::M},
	{sf::Keyboard::N,         Arcade::Keys::N},
	{sf::Keyboard::O,         Arcade::Keys::O},
	{sf::Keyboard::P,         Arcade::Keys::P},
	{sf::Keyboard::Q,         Arcade::Keys::Q},
	{sf::Keyboard::R,         Arcade::Keys::R},
	{sf::Keyboard::S,         Arcade::Keys::S},
	{sf::Keyboard::T,         Arcade::Keys::T},
	{sf::Keyboard::U,         Arcade::Keys::U},
	{sf::Keyboard::V,         Arcade::Keys::V},
	{sf::Keyboard::W,         Arcade::Keys::W},
	{sf::Keyboard::X,         Arcade::Keys::X},
	{sf::Keyboard::Y,         Arcade::Keys::Y},
	{sf::Keyboard::Z,         Arcade::Keys::Z},
	{sf::Keyboard::Left,      Arcade::Keys::LEFT},
	{sf::Keyboard::Right,     Arcade::Keys::RIGHT},
	{sf::Keyboard::Up,        Arcade::Keys::UP},
	{sf::Keyboard::Down,      Arcade::Keys::DOWN},
	{sf::Keyboard::Return,    Arcade::Keys::ENTER},
	{sf::Keyboard::Space,     Arcade::Keys::SPACE},
	{sf::Keyboard::Delete,    Arcade::Keys::DELETE},
	{sf::Keyboard::BackSpace, Arcade::Keys::BACKSPACE},
	{sf::Keyboard::Tab,       Arcade::Keys::TAB},
	{sf::Keyboard::Escape,    Arcade::Keys::ESC},
	{sf::Keyboard::M,         Arcade::Keys::MOUSELEFT},
	{sf::Keyboard::M,         Arcade::Keys::MOUSERIGHT}
};

Arcade::LibSFML::LibSFML(Arcade::Vect<size_t> screenSize,
	const std::string &title)
	: events(), screenSize(screenSize),
	  window({static_cast<unsigned int>(screenSize.getX()),
		  static_cast<unsigned int>(screenSize.getY()), 32}, title),
	  texture(), sprite(this->texture)
{
	this->texture.create(static_cast<unsigned int>(screenSize.getX()),
			     static_cast<unsigned int>(screenSize.getY()));
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition({0, 0});

	this->text.setOrigin(0, 0);
	font.loadFromFile("libs/src/SFML/arial_narrow_7.ttf");
	this->text.setFont(font);
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
	sf::Sprite spr;

	if (this->isOpen()) {
		auto array = &b.getPixelArray()[0];
		this->texture.update((unsigned char *) array,
				     static_cast<unsigned int>(b.getWidth()),
				     static_cast<unsigned int>(b.getHeight()),
				     0, 0);
		spr.setTexture(this->texture);
		spr.setPosition(b.getX(), b.getY());
		spr.setTextureRect({0, 0, static_cast<int>(b.getWidth()),
				    static_cast<int>(b.getHeight())});
		this->window.draw(spr);
	}
}

void Arcade::LibSFML::drawText(Arcade::TextBox &t)
{
	auto col = t.getColor();

	if (this->isOpen()) {
		text.setCharacterSize(
			static_cast<unsigned int>(t.getFontSize()));
		text.setString(t.getValue());
		text.setPosition(t.getX(), t.getY());
		text.setColor({col.getRed(), col.getGreen(), col.getBlue(),
			       col.getAlpha()});
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
