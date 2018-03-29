/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** DlLoader.hpp
*/

#ifndef CPP_ARCADE_DLLOADER_HPP
	#define CPP_ARCADE_DLLOADER_HPP

#include <string>
#include "../libs/src/IGraphicLib.hpp"

namespace Arcade {
	// The purpose of this function is to load a lib with dlopen etc ...
	// Then get the instance of the IGraphicLib returned by the entryPoint
	// Of the loaded lib.
	class DlLoader {
	public:
		DlLoader(std::string libPath);
		~DlLoader();

		// return the object created by the graphical lib when it has been loaded dlsym on the exntryPoint has been done.
		IGraphicLib *getLibInstance();

	private:
		std::string libPath;
		IGraphicLib *instance;
	};
}


#endif //CPP_ARCADE_DLLOADER_HPP
