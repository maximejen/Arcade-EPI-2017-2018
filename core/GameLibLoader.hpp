/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameLibLoader.hpp
*/

#ifndef CPP_ARCADE_GAMELIBLOADER_HPP_
	#define CPP_ARCADE_GAMELIBLOADER_HPP_

	#include <string>
	#include "../games/src/IGameLib.hpp"

namespace Arcade {
	class GameLibLoader {
	public:
		GameLibLoader();
		~GameLibLoader();

		// return the object created by the graphical lib when it has been loaded dlsym on the exntryPoint has been done.
		IGameLib *getLibInstance();
		// load the lib at the libPath given in argument. Then save the instance of the lib in the object. Need to call unloadLib before load a new one.
		bool loadLib(const std::string &libPath);
		// check the lib demanded exits and the file is an elf.
		bool isElfFile(const std::string &libPath) const;
		// this function call dlclose on the lib.
		bool unloadLib();

	private:
		std::string libPath;
		void *handleAddr;
		IGameLib *entryPointResult;
		bool isLibLoaded;
	};
}

#endif //CPP_ARCADE_GAMELIBLOADER_HPP_
