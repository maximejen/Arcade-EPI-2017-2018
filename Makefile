##
## EPITECH PROJECT, 2018
## Nanoteksice
## File description:
## Epitech project
##

SRC		=	main.cpp					\
			core/ArgParser.cpp

CXXFLAGS	=	-I./ -I./core -I./libs -I./games

OBJ		=	$(SRC:.cpp=.o)

NAME		=	arcade

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)

core:
	echo "try to compile the core of the arcade"

graphicals:
	echo "try to compile the graphical libs"

games:
	echo "try to compile the games"

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re core graphicals games
