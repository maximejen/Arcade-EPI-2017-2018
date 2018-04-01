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
		DlLoader();
		~DlLoader();

		// return the object created by the graphical lib when it has been loaded dlsym on the exntryPoint has been done.
		IGraphicLib *getLibInstance();
		// load the lib at the libPath given in argument. Then save the instance of the lib in the object. Need to call unloadLib before load a new one.
		bool loadLib(const std::string &libPath);
		// check the lib demanded exits and the file is an elf.
		bool isElfFile(const std::string &libPath) const;
		// this function call dlclose on the lib.
		bool unloadLib();

	private:
		std::string libPath;
		void *handleAddr;
		IGraphicLib *entryPointResult;
		bool isLibLoaded;
	};
}


#endif //CPP_ARCADE_DLLOADER_HPP
