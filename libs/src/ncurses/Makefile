##
## EPITECH PROJECT, 2018
## my_malloc
## File description:
## my_malloc.c
##

CC 		= 	g++
RM 		= 	rm -f
TARGET_LIB 	= 	lib_arcade_ncurses.so

SRCS		= 	./entryPoint.cpp			\
			./LibNcurses.cpp			\
			../../../core/TextBox.cpp		\
			../../../core/PixelBox.cpp		\
			../../../core/Color.cpp

OBJS 		= 	$(SRCS:.cpp=.o)

CXXFLAGS 	= 	-I. -I ../../../core
CXXFLAGS 	+= 	-W -Wall -Wextra -fPIC -rdynamic -std=c++11
LDFLAGS      	=	-shared -lncurses

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	 $(CC) $(OBJS) -o ../../$(TARGET_LIB) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../../$(TARGET_LIB)

re: fclean all

.PHONY: all clean fclean re
