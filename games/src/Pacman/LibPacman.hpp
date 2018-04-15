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
#include <ctime>
#include <thread>
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
		enum GHOSTSTATE {
			CHASING,
			RUNNING,
			SLEEPING
		};
		void display(IGraphicLib &graphicLib);
		void drawRectangle(size_t y, size_t x, IGraphicLib &graphicLib,
			Color color, bool space);
		void movePlayer(Keys dir);
		bool checkEnd();
		void displaymap(IGraphicLib &graphicLib);
		void drawFood(std::pair<size_t, size_t >, IGraphicLib &graphicLib, Color color, bool type);
		void moveGhosts();
		void updateGhost(int id);
		std::pair<int, int> determineDirection(int x, int y);
		void showSmellValues();
		void resetDoubleVector(std::vector<std::vector<int>> &vector);
		void spreadSmell(int x, int y, int sv);
		void afterMovePlayer();
		int pacGum();
		size_t score;
		Vect<size_t> mapSize;
		TextBox *msgScore;
		Vect<size_t>resize;
		Keys curKey;
		Keys lastKey;
		std::chrono::steady_clock::time_point timer;
		std::chrono::steady_clock::time_point timeDisplay;
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point startMoment;
		double timeSleep;
		std::pair<int, int> pos;
		int lifes;
		bool shouldStop;
		std::vector<std::pair<int, int>> gCoords;
		std::vector<GHOSTSTATE> gStates;
		std::vector<std::vector<int>> smellValues;
		std::vector<std::vector<int>> smellPassage;
	};
};


#endif //CPP_ARCADE_LIBSNAKE_HPP
