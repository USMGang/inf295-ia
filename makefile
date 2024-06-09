CC = g++
CFLAGS = -Wall -Wextra -Werror -g

DIR = ./bin
SOURCES = instance.cpp main.cpp
OBJECTS = $(addprefix $(DIR)/, $(SOURCES:.cpp=.o))
OUT = $(DIR)/a.out

all: $(DIR) $(OUT)

$(DIR):
	mkdir -p $(DIR)

$(OUT): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

$(DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(OUT)
	$(OUT)

clean:
	rm -f $(OBJECTS) $(OUT)

.PHONY: all clean run
