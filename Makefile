NAME		= minishell

CC			= cc

CFLAGS		= -Wextra -Werror -Wall -Iincludes -Ilibft -g3

READLFLAGS	= -lreadline

SRC_DIR		= src
LIBFT_DIR	= libft
OBJ_DIR		= obj

SRC_FILES	= main.c \
			builtins/blt_cd.c \
			builtins/blt_echo.c \
			builtins/blt_env.c \
			builtins/blt_exit.c \
			builtins/blt_exit_max.c \
			builtins/blt_export.c \
			builtins/blt_pwd.c \
			builtins/blt_unset.c \
			builtins/utils_blt_export.c \
			builtins/utils_error.c \
			exec/build_env.c \
			exec/exec_and_or.c \
			exec/exec_cmd.c \
			exec/exec_cmd_child.c \
			exec/exec_core.c \
			exec/exec_core_blt.c \
			exec/exec_group.c \
			exec/exec_pipe.c \
			exec/exec_pipe_child.c \
			exec/exec_redir.c \
			exec/exec_utils.c \
			exec/resolve_path.c \
			expand/exp_calc_if_need_new_var.c \
			expand/exp_cringe_dolars.c \
			expand/exp_env_var.c \
			expand/exp_none_var.c \
			expand/exp_set_exp_extract_var.c \
			expand/exp_utils.c \
			expand/exp_var_append_without_new_idx.c \
			expand/exp_verif_expand.c \
			expand/expand.c \
			lexer/lex_pars.c \
			lexer/lex_pars_elements.c \
			lexer/lex_pars_valid_word.c \
			lexer/lexer.c \
			lexer/lexer_debug.c \
			lexer/lexer_set_value.c \
			lexer/lexer_tokeniser.c \
			lexer/lexer_utils.c \
			parser/ast.c \
			parser/hd_resolve.c \
			parser/hd_utils.c \
			parser/parser.c \
			parser/parser_cmd.c \
			parser/parser_cmd_utils.c \
			parser/parser_error.c \
			parser/parser_redirect.c \
			utils/free.c \
			utils/init_env.c \
			utils/readline_utils.c \
			utils/signals.c \
			utils/verif_if_need_expand.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.d)

LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/builtins $(OBJ_DIR)/lexer $(OBJ_DIR)/exec $(OBJ_DIR)/utils $(OBJ_DIR)/expand $(OBJ_DIR)/parser
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
