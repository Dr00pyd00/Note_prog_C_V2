
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -I$(INC_DIR) 
NAME = note

SRC_DIR = src 
INC_DIR = include 
OBJ_DIR = obj


SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lsqlite3

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 	
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re: clean all

.PHONY: clean all re

