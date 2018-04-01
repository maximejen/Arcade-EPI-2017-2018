/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** DlLoader.cpp
*/

#include <fstream>
#include <dlfcn.h>
#include <iostream>
#include "DlLoader.hpp"

static const char MAGIC[4] = {0x7f, 'E', 'L', 'F'};

Arcade::DlLoader::DlLoader() : libPath(""), handleAddr(),
			       entryPointResult(), isLibLoaded(false)
{
	this->handleAddr = nullptr;
	this->entryPointResult = nullptr;
}

Arcade::DlLoader::~DlLoader()
{
	this->unloadLib();
}

Arcade::IGraphicLib *Arcade::DlLoader::getLibInstance()
{
	return this->entryPointResult;
}

bool Arcade::DlLoader::loadLib(const std::string &libPath)
{
	std::string tmp;
	Arcade::IGraphicLib *(*ret)() = nullptr;
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

bool Arcade::DlLoader::isElfFile(const std::string &libPath) const
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

bool Arcade::DlLoader::unloadLib()
{
	if (this->handleAddr != nullptr)
		dlclose(this->handleAddr);
	this->handleAddr = nullptr;
	this->isLibLoaded = false;
	this->entryPointResult = nullptr;
}
