NAME = endgame

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR)
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

uninstall: clean
	rm -f $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
