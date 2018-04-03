/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LogicException.cpp
*/

#include "LogicException.hpp"

Arcade::LogicException::LogicException(const std::string &message) :
	exception(), message(message)
{

}

Arcade::LogicException::~LogicException()
{
}

const std::string &Arcade::LogicException::what()
{
	return this->message;
}