TARGET = prob2.out
CC = g++
CFLAGS = -std=c++14
SRCS = main.cpp inf_int.cpp calculator.cpp
OBJS = $(SRCS:.cpp=.o)
SRC_DIR = ./
INCLUDE = -Iinclude/
HEADERS = inf_int.h calculator.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
