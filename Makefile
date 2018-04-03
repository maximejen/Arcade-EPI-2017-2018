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
			core/PixelBox.cpp

CXXFLAGS	=	-I./ -I./core -I./libs -I./games -W -Wall -Wextra -g -std=c++11

LIBFLAGS	=	-ldl

OBJ		=	$(SRC:.cpp=.o)

NAME		=	arcade

all: $(NAME)

$(NAME): $(OBJ)
	make -sC ./libs
	g++ -o $(NAME) $(OBJ) $(LIBFLAGS)

core: $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LIBFLAGS)

graphicals:
	make -sC ./libs

games:
	echo "try to compile the games"

clean:
	make clean -sC ./libs
	rm -rf $(OBJ)

fclean: clean
	make fclean -sC ./libs
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re core graphicals games arcade
