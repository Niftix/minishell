NAME		= minishell

CC			= cc

CFLAGS		= -Wextra -Werror -Wall -Iincludes -Ilibft -g3

READLFLAGS	= -lreadline

SRC_DIR		= src
LIBFT_DIR	= libft
OBJ_DIR		= obj

SRC_FILES   = main.c \
            builtins/builtins.c \
            builtins/builtin_export.c \
            builtins/builtins_cd_utils.c \
            builtins/builtin_unset.c \
            exec/exec_and_or.c \
            exec/exec_builtins.c \
            exec/exec.c \
            exec/exec_cmd.c \
            exec/exec_pipe.c \
            exec/exec_redir.c \
            exec/exec_subshell.c \
            exec/exec_utils.c \
            exec/path.c \
            lexer/lexer.c \
            lexer/lexer_utils.c \
            lexer/lexer_tokeniser.c \
            lexer/lexer_set_value.c \
            lexer/lex_pars.c \
			lexer/lexer_debug.c \
            lexer/lex_pars_elements.c \
            utils/free.c \
            utils/initializer.c \
            utils/readline_utils.c \
            utils/signal_utils.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.d)

LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/builtins $(OBJ_DIR)/lexer $(OBJ_DIR)/exec $(OBJ_DIR)/utils
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
