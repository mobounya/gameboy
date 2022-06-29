NAME = gameboy_test

OBJ = cpu_tests.o ../Z80_CPU.o

SOURCE = cpu_tests.cpp ../Z80_CPU.cpp

LINKER_FLAGS = -I $(HOME)/shared/ -L $(HOME)/shared/gtest/ -lgtest_main -lgtest -std=c++11

COMPILER_FLAGS = -I $(HOME)/shared/ -std=c++11

all : $(NAME)

$(NAME) : $(OBJ) $(HEADERS)
	g++ $(LINKER_FLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp $(HEADERS)
	g++ $(COMPILER_FLAGS) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean re
