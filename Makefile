# ========================================================================== #
#                                   COLORS                                   #
# ========================================================================== #

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED	 = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# ========================================================================== #
#                                   PROGRAM                                  #
# ========================================================================== #

NAME = philo
ARGS = 5 800 200 200
HELGRIND = valgrind --tool=helgrind --history-level=approx -s

# ========================================================================== #
#                                   PATHS                                    #
# ========================================================================== #

SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include

# ========================================================================== #
#                                   FILES                                    #
# ========================================================================== #

SRC_FILES = args_init.c \
			args_utils.c \
			errors_free.c \
			main.c \
			routine.c \
			routine_utils.c \
			table.c \
			big_sister.c \


SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
HEADER = $(INC_DIR)/philo.h

# ========================================================================== #
#                                COMPILATION                                 #
# ========================================================================== #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) #-fsanitize=thread
PTHREAD = -pthread #-fsanitize=thread
RM = rm -rf
HELGRIND = valgrind --tool=helgrind --history-level=approx -s
# ========================================================================== #
#                                   RULES                                    #
# ========================================================================== #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Compiling: $(CYAN)$<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)✓ Object files cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)✓ Executable removed!$(DEF_COLOR)"

re: fclean all

# Rule to compile with fsanitize (Thread Sanitizer)
# Adds flags and runs 're' to recompile everything with the new options
debug: CFLAGS += -fsanitize=thread -g
debug: PTHREAD += -fsanitize=thread -g
debug: re
	@echo "$(MAGENTA)✓ Debug mode compiled (fsanitize=thread)!$(DEF_COLOR)"

# Rule to execute Helgrind
# Compiles with -g (symbols) for Valgrind precision
helgrind: CFLAGS += -g
helgrind: re
	@echo "$(MAGENTA)Running Helgrind verification...$(DEF_COLOR)"
	@$(HELGRIND) ./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug helgrind