/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ArgParser.hpp
*/

#ifndef CPP_ARCADE_ARGPARSER_HPP_
	#define CPP_ARCADE_ARGPARSER_HPP_

	#include <string>
	#include <vector>

namespace Arcade {
	// This class provide a static method to parse the arg sent by the user
	class ArgParser {
	public:
		ArgParser();
		~ArgParser() = default;

		static int parseArgs(int argc, char **argv);
	};
}


#endif //CPP_ARCADE_ARGPARSER_HPP_
