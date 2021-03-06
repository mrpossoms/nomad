#                           _   _         _ _    _ 
#    _ _  ___ _ __  __ _ __| | | |__ _  _(_) |__| |
#   | ' \/ _ \ '  \/ _` / _` | | '_ \ || | | / _` |
#   |_||_\___/_|_|_\__,_\__,_| |_.__/\_,_|_|_\__,_|
#                                                  
#   --- Template Build File ---

CMP = g++

INC = -I./ -I./../
LIB =
LINK=-lm
FLAGS=

SRCS = $(wildcard ./*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)

.cpp.o: 
	$(CMP) $(INC) $(FLAGS) -c $< -o $@

clean:
	find . -type f -name '*.o' -exec rm {} +
