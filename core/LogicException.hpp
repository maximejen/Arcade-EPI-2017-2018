/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LogicException.hpp
*/

#ifndef CPP_ARCADE_LOGICEXCEPTION_HPP_
#define CPP_ARCADE_LOGICEXCEPTION_HPP_

#include <exception>
#include <string>

namespace Arcade {
	class LogicException : public std::exception {
	public:
		explicit LogicException(const std::string &message);
		~LogicException();
		const std::string &what();

	private:
		std::string message;
	};
}


#endif //CPP_ARCADE_LOGICEXCEPTION_HPP
