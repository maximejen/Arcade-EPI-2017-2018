/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** DlLoader.cpp
*/

#include <fstream>
#include <dlfcn.h>
#include <iostream>
#include "GraphLibLoader.hpp"

static const char MAGIC[4] = {0x7f, 'E', 'L', 'F'};

Arcade::GraphLibLoader::GraphLibLoader() : libPath(""), handleAddr(),
			       entryPointResult(), isLibLoaded(false)
{
	this->handleAddr = nullptr;
	this->entryPointResult = nullptr;
}

Arcade::GraphLibLoader::~GraphLibLoader()
{
	this->unloadLib();
}

Arcade::IGraphicLib *Arcade::GraphLibLoader::getLibInstance()
{
	return this->entryPointResult;
}

bool Arcade::GraphLibLoader::loadLib(const std::string &libPath)
{
	std::string tmp;
	Arcade::IGraphicLib *(*ret)() = nullptr;
	bool returnValue = false;

	if (!this->isElfFile(libPath))
		return returnValue;
	if ((this->handleAddr = dlopen(libPath.c_str(), RTLD_LAZY))) {
		returnValue = true;
		*(void **) (&ret) = dlsym(this->handleAddr, "entryPoint");
		if (ret)
			this->entryPointResult = ret();
		else
			returnValue = false;
	}
	else
		std::cout << dlerror() << std::endl;
	return returnValue;
}

bool Arcade::GraphLibLoader::isElfFile(const std::string &libPath) const
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

bool Arcade::GraphLibLoader::unloadLib()
{
	if (this->handleAddr != nullptr)
		dlclose(this->handleAddr);
	this->handleAddr = nullptr;
	this->isLibLoaded = false;
	this->entryPointResult = nullptr;
	return true;
}
