##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Epitech project
##

SRC		=	main.cpp					\
			core/ArgParser.cpp				\
			core/GraphLibLoader.cpp				\
			core/Core.cpp					\
			core/GameLibLoader.cpp				\
			core/LogicException.cpp				\
			core/PixelBox.cpp				\
			core/TextBox.cpp				\
			core/Color.cpp					\
			core/PlayerScore.cpp				\
			core/MenuManager.cpp				\
			core/ScoreManager.cpp

CXXFLAGS	=	-I./ -I./core -I./libs -I./games -W -Wall -Wextra -g -std=c++11 -rdynamic

LIBFLAGS	=	-ldl

OBJ		=	$(SRC:.cpp=.o)

NAME		=	arcade

all: games graphicals core

core: $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LIBFLAGS)

graphicals:
	make -C ./libs

games:
	make -C ./games

clean:
	make clean -C ./libs
	make clean -C ./games
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libs
	make fclean -C ./games
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re core graphicals games arcade
