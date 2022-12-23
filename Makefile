##
## Makefile for Equi Latte Chess
##
## Made by Kévin Laspougeas
## <kevin.laspougeas@gmail.com>
##
## Created 21/12/2022

CC = g++

RM = rm -f

NAME = equi_latte_chess

SRC =	srcs/main.cpp \
		srcs/Menu.cpp
	
OBJ = $(SRC:.cpp=.o)

CFLAGS = -W -Wall -Wextra

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) -I ./includes/ $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all