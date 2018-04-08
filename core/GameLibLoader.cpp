/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameLibLoader.cpp
*/

#include <fstream>
#include <dlfcn.h>
#include <iostream>
#include "GameLibLoader.hpp"

static const char MAGIC[4] = {0x7f, 'E', 'L', 'F'};

Arcade::GameLibLoader::GameLibLoader() : libPath(""), handleAddr(),
					   entryPointResult(), isLibLoaded(false)
{
	this->handleAddr = nullptr;
	this->entryPointResult = nullptr;
}

Arcade::GameLibLoader::~GameLibLoader()
{
	this->unloadLib();
}

Arcade::IGameLib *Arcade::GameLibLoader::getLibInstance()
{
	return this->entryPointResult;
}

bool Arcade::GameLibLoader::loadLib(const std::string &libPath)
{
	std::string tmp;
	Arcade::IGameLib *(*ret)() = nullptr;
	bool returnValue = false;

 	if (!this->isElfFile(libPath))
		return false;
	if ((this->handleAddr = dlopen(libPath.c_str(), RTLD_LAZY))) {
		returnValue = true;
		*(void **) (&ret) = dlsym(this->handleAddr, "entryPoint");
		if (ret)
			this->entryPointResult = ret();
		else
			returnValue = false;
	}
	return returnValue;
}

bool Arcade::GameLibLoader::isElfFile(const std::string &libPath) const
{
	std::ifstream lib(libPath);
	char magic[5] = {0, 0, 0, 0, 0};
	std::string tmp;

	if (lib.fail())
		return false;
	lib.read(magic, 4);
	tmp = magic;
	return tmp == MAGIC;
}

bool Arcade::GameLibLoader::unloadLib()
{
	if (this->handleAddr != nullptr)
		dlclose(this->handleAddr);
	this->handleAddr = nullptr;
	this->isLibLoaded = false;
	this->entryPointResult = nullptr;
	return true;
}
