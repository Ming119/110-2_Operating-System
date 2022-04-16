CC = gcc
CCFLAGS = -std=c11 -g
LIBFLAGS = -lpthread
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
BIN_FILES := $(BIN_DIR)/*

all: dirs clean $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJ_FILES)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $< $(LIBFLAGS)

dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY:
	dirs clean