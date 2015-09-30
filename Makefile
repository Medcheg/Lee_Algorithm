CXX = gcc
CXX_FLAGS = -g -Wall
BIN_NAME = "lee_algo"

PHONY: all
PHONY: clean

all: clean $(BIN_NAME)

$(BIN_NAME): *.c
#	@echo $?
#	@echo $@
	$(CXX) $(CXX_FLAGS) -lm -O3 -o $(BIN_NAME) $?
clean:
	@rm -rf *.o *~ *$(BIN_NAME)
