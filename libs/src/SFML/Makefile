##
## EPITECH PROJECT, 2018
## my_malloc
## File description:
## my_malloc.c
##

CC 		= 	g++
RM 		= 	rm -f
TARGET_LIB 	= 	lib_arcade_SFML.so

SRCS		= 	./entryPoint.cpp			\
			./LibSFML.cpp				\
			./TextBox.cpp				\
			./PixelBox.cpp				\
			./Color.cpp

OBJS 		= 	$(SRCS:.cpp=.o)

CXXFLAGS 	= 	-I. -I ../../../core
CXXFLAGS 	+= 	-W -Wall -Wextra -fPIC
LDFLAGS      	=	-shared -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	 $(CC) $(OBJS) -o ../../$(TARGET_LIB) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../../$(TARGET_LIB)

re: fclean all

.PHONY: all clean fclean re
