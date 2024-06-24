CC = g++
CFLAGS = -Wall -Wextra -g -Iinclude

DIR = ./bin
# SOURCES = src/main.cpp \
# 		  src/problem/problem.cpp
SOURCES = $(wildcard src/**/*.cpp) \
		  $(wildcard src/*.cpp)

OBJECTS = $(patsubst src/%.cpp, $(DIR)/%.o, $(SOURCES))

# OBJECTS = $(addprefix $(DIR)/, $(SOURCES:.cpp=.o))
OUT = $(DIR)/a.out

all: $(DIR) $(OUT)

$(DIR):
	mkdir -p $(DIR)

$(OUT): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

$(DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(OUT)
	$(OUT)

gdb: $(OUT)
	gdb $(OUT)

val: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(OUT)

clean:
	rm -rf $(DIR)/*

.PHONY: all clean run
