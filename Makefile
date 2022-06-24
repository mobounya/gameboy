NAME = gameboy

OBJ = main.o Z80_CPU.o

SOURCE = main.cpp Z80_CPU.cpp

HEADERS = Z80_CPU.h

FLAGS = -std=c++11

all : $(NAME)

$(NAME) : $(OBJ) $(HEADERS)
	g++ -std=c++11 $(OBJ) -o $(NAME)

%.o : %.cpp $(HEADERS)
	g++ $(FLAGS) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean re
