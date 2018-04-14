/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/
#ifndef CPP_ARCADE_LIBSNAKE_HPP
#define CPP_ARCADE_LIBSNAKE_HPP

#include "../IGameLib.hpp"
#include <algorithm>
#include <vector>
#include "time.h"
#include <thread>
#include <pthread.h>
#include <chrono>
#include <ctime>
#define MAP_WIDTH 27
#define MAP_HEIGHT 27

namespace Arcade {
	class LibPacman : public IGameLib {
	public:
		LibPacman();
		~LibPacman() override;

		/* Get the name of the game */
		const std::string getName() const override ;


		/* Resources handling */
		// Initializes the library
		bool init() override ;

		// Unloads the library
		bool stop() override ;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		void applyEvent(Keys key) override ;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		void update() override ;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		void refresh(IGraphicLib &graphicLib) override ;

		// To call at the end of the execution of the game (after the player loose or win) for getting his score
		size_t getScore();

		static void displayMap(IGraphicLib *graphicLib);


	private:
		size_t score;
		std::vector<std::pair<int, int>> playerPos;
		Vect<size_t> objectPos;
		Vect<size_t> mapSize;
		void display(IGraphicLib &graphicLib);
		void drawRectangle(size_t y, size_t x, IGraphicLib &graphicLib,
			Color color, bool space);
		void movePlayer(Keys dir);
		bool checkEnd();
		void displaymap(IGraphicLib &graphicLib);
		void drawFood(std::pair<size_t, size_t >, IGraphicLib &graphicLib, Color color, bool type);
		TextBox *msgScore;
		Vect<size_t>resize;
		Keys curKey;
		Keys lastKey;
		std::chrono::steady_clock::time_point timer;
		std::chrono::steady_clock::time_point timeDisplay;
		double timeSleep;
		std::pair<int, int> pos;
		int playerDirection;
		int lifes;
		std::vector<std::string> map;
	};
};


#endif //CPP_ARCADE_LIBSNAKE_HPP
