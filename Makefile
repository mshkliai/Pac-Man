NAME = pacman

SRC =	main.cpp \
		Character.cpp \
		Ghost.cpp \
		Game.cpp \
		Pacman.cpp \
		Parser.cpp \
		Reader.cpp \
		SFMLCore.cpp \
		Solver.cpp \

S_SRC = $(addprefix ./src/, $(SRC))

OBJ = $(S_SRC:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror

CC = g++ -std=c++11

SFML = -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -rpath ~/.brew/lib

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(SFML)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -I ~/.brew/include -o $@ $<

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
