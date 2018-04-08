##
## EPITECH PROJECT, 2018
## Aracde
## File description:
## Epitech project
##

all: $(OBJ)
	make -C ./src/ncurses
	make -C ./src/SDL
	make -C ./src/SFML

clean:
	make clean -C ./src/ncurses
	make clean -C ./src/SDL
	make clean -C ./src/SFML

fclean: clean
	make fclean -C ./src/ncurses
	make fclean -C ./src/SDL
	make fclean -C ./src/SFML

re: fclean all

.PHONY: all clean fclean re
