/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include <unordered_map>
#include <iostream>
#include <ios>
#include "LibSDL.hpp"

static const std::unordered_map<int, Arcade::Keys> SDL_KEYS_List = {
	{0, Arcade::NONE},
	{SDLK_a, Arcade::A},
	{SDLK_b, Arcade::B},
	{SDLK_c, Arcade::C},
	{SDLK_d, Arcade::D},
	{SDLK_e, Arcade::E},
	{SDLK_f, Arcade::F},
	{SDLK_g, Arcade::G},
	{SDLK_h, Arcade::H},
	{SDLK_i, Arcade::I},
	{SDLK_j, Arcade::J},
	{SDLK_k, Arcade::K},
	{SDLK_l, Arcade::L},
	{SDLK_m, Arcade::M},
	{SDLK_n, Arcade::N},
	{SDLK_o, Arcade::O},
	{SDLK_p, Arcade::P},
	{SDLK_q, Arcade::Q},
	{SDLK_r, Arcade::R},
	{SDLK_s, Arcade::S},
	{SDLK_t, Arcade::T},
	{SDLK_u, Arcade::U},
	{SDLK_v, Arcade::V},
	{SDLK_w, Arcade::W},
	{SDLK_x, Arcade::X},
	{SDLK_y, Arcade::Y},
	{SDLK_z, Arcade::Z},
	{SDLK_LEFT, Arcade::LEFT},
	{SDLK_RIGHT, Arcade::RIGHT},
	{SDLK_UP, Arcade::UP},
	{SDLK_DOWN, Arcade::DOWN},
	{SDLK_KP_ENTER, Arcade::ENTER},
	{SDLK_SPACE, Arcade::SPACE},
	{SDLK_DELETE, Arcade::DELETE},
	{SDLK_BACKSPACE, Arcade::BACKSPACE},
	{SDLK_TAB, Arcade::TAB},
	{SDLK_ESCAPE, Arcade::ESC},
	{SDLK_a, Arcade::MOUSELEFT},
	{SDLK_a, Arcade::MOUSERIGHT}
};

Arcade::LibSDL::LibSDL(Vect<size_t> screenSize, const std::string &name)
{
	SDL_Init(SDL_INIT_VIDEO);

	this->screenSize = screenSize;
	this->window = NULL;

	this->window  = SDL_CreateWindow(name.c_str(),
					 SDL_WINDOWPOS_UNDEFINED,
					 SDL_WINDOWPOS_UNDEFINED,
					 screenSize.getX(), screenSize.getY(),
					 SDL_WINDOW_SHOWN);


	this->renderer = SDL_CreateRenderer(this->window,
					    -1, SDL_RENDERER_ACCELERATED);
	if (!this->window)
	{
		std::cout << "Cant create WIndow" << std::endl;
		exit(0);
	}
}

Arcade::LibSDL::~LibSDL()
{
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool Arcade::LibSDL::isOpen() const
{
	if (this->renderer)
		return true;
	return false;
}

void Arcade::LibSDL::closeRenderer()
{
	SDL_DestroyWindow(this->window);
}

void Arcade::LibSDL::openRenderer(std::string const &title)
{
	this->window = SDL_CreateWindow(title.c_str(),
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					(int)screenSize.getY(),
					(int)screenSize.getX(), SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window,
					    -1, SDL_RENDERER_ACCELERATED);
}

void Arcade::LibSDL::clearWindow()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);

	SDL_RenderClear(this->renderer);
}

void Arcade::LibSDL::refreshWindow()
{
	SDL_RenderPresent(this->renderer);
}

void Arcade::LibSDL::drawPixelBox(PixelBox &box)
{
	std::vector<Color> col= box.getPixelArray();


	for (int i = 0; i < (int)box.getHeight(); i++) {
		for (int j = 0; j < (int)box.getWidth(); j++) {
			SDL_SetRenderDrawColor(this->renderer,
					       col.at(i * box.getWidth() + j).getRed(),
					       col.at(i * box.getWidth() + j).getGreen()
				,  col.at(i * box.getWidth() + j).getBlue(),
					       col.at(i * box.getWidth() + j).getAlpha());
			SDL_RenderDrawPoint(this->renderer,box.getY() + i, box.getX() + j);
		}
	}
}

void Arcade::LibSDL::drawText(TextBox &text)
{
	int texW = (int)text.getX();
	int texH = (int)text.getY();

	TTF_Init();
	TTF_Font * font = TTF_OpenFont("/home/dams/repo/PSU/PSU_lemipc_2017/displaying/OpenSans-Bold.ttf", 25);
	SDL_Color color = { text.getColor().getRed(), text.getColor().getGreen(),
			    text.getColor().getBlue(), text.getColor().getAlpha()};
	SDL_Surface * surface = TTF_RenderText_Solid(font,
						     text.getValue().c_str(),
						     color);

	SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer,
							     surface);
	SDL_QueryTexture(texture, NULL, NULL, &texH, &texW);
	SDL_Rect dstrect = {(int)text.getPos().getY() , (int)text.getPos().getX(),
			    texH, texW };
	SDL_RenderCopy(this->renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(this->renderer);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_Quit();
}

void Arcade::LibSDL::drawPixel(int x, int y, const Color &color)
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, color.getRed(), color.getGreen(),
			       color.getBlue(), color.getAlpha());
	SDL_RenderDrawPoint(this->renderer,y,x);

}


Arcade::Vect<size_t> Arcade::LibSDL::getScreenSize() const
{
	return this->screenSize;
}

bool Arcade::LibSDL::pollEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type != 0 && event.key.keysym.sym != 0) {
		if (SDL_KEYS_List.find(event.key.keysym.sym) != SDL_KEYS_List.end()) {
			std::cout << "Enter :" << event.key.keysym.sym << std::endl;
			this->events.push(SDL_KEYS_List.at(event.key.keysym.sym));
		}
	}
	return !this->events.empty();
}

Arcade::Keys Arcade::LibSDL::getLastEvent()
{
	Arcade::Keys ret = this->events.back();
	this->events.pop();
	return ret;
}

void Arcade::LibSDL::clearEvents()
{
	while (!this->events.empty())
		this->events.pop();
}

size_t Arcade::LibSDL::getMaxX() const
{
	return this->screenSize.getX();
}

size_t Arcade::LibSDL::getMaxY() const
{
	return this->screenSize.getY();
}

std::string Arcade::LibSDL::getName() const
{
	return "SDL";
}
