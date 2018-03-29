/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core.hpp
*/

#ifndef CPP_ARCADE_CORE_HPP
#define CPP_ARCADE_CORE_HPP

namespace Arcade {
	// The core will be initialized by the main, then it will handle the program
	// The purpose of the Core is to handle the main loop for the program
	// Then load the actual lib chosen by the user and load the other libs when needed.
	// Then Core will call the function to render the game and then the lib function to do when the game "asks"
	class Core {
	public:
		Core();
		~Core();
	};
}


#endif //CPP_ARCADE_CORE_HPP
