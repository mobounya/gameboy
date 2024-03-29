NAME = gameboy

OBJ = main.o Z80_CPU.o

SOURCE = main.cpp Z80_CPU.cpp

HEADERS = Z80_CPU.h

FLAGS = -std=c++11

all : $(NAME)

$(NAME) : $(OBJ) $(HEADERS)
	g++ $(FLAGS) $(OBJ) -o $(NAME)

test:
	make -C ./tests

%.o : %.cpp $(HEADERS)
	g++ $(FLAGS) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJ)
	make clean -C ./tests

fclean: clean
	rm -f $(NAME)
	make fclean -C ./tests

.PHONY: all clean fclean re
