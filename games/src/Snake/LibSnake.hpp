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

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

namespace Arcade {
	class LibSnake : public IGameLib {
	public:
		LibSnake();
		~LibSnake() override;

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

	private:
		size_t score;
		std::vector<std::pair<int, int>> playerPos;
		Vect<size_t> objectPos;
		Vect<size_t> mapSize;
		void setObjectPos();
		void display(IGraphicLib &graphicLib);
		void drawPlayer(size_t y, size_t x, IGraphicLib &graphicLib,  Color color);
		void movePlayer(Keys dir);
		int checkFood(Keys dir);
		void moveSnake();
		bool canGoBack(Keys key);
		bool checkEnd();
		TextBox *msgScore;
		Vect<size_t>resize;
		Keys curKey;
		Keys lastKey;
		time_t timer;
		bool canRefresh;
	};
};


#endif //CPP_ARCADE_LIBSNAKE_HPP