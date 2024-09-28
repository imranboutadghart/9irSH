# GOOFY AHH COMMENT
CC:=cc
CFLAGS:= -Wextra -Wall -Werror
NAME:= minishell
INCLUDE_DIR:=include
BIN_DIR:=bin

LK_DIR:=src/leak_killer
PARSE_DIR:=src/parser
EXEC_DIR:=src/exec src/builtins
UTILS_DIR=src/utils
PROMPT_DIR=src/prompt
ERROR_DIR=src/error
SIGNALS_DIR=src/signals
ENV_DIR=src/env

SRC_DIRS:= $(ENV_DIR) $(LK_DIR) $(PARSE_DIR) $(EXEC_DIR) $(UTILS_DIR) $(PROMPT_DIR) $(ERROR_DIR) $(SIGNALS_DIR) src

SRC:= $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c)) 
OBJ:=$(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(SRC)))

.DEFAULT_GOAL := $(NAME)

vpath %.c $(SRC_DIRS)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(OBJ) -lreadline

$(BIN_DIR)/%.o : %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

clean :
	rm -rf $(BIN_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

.PHONY : all clean fclean re gdb sanitize
.SECONDARY: