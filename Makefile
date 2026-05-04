NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I includes -I libft
READLINE = -lreadline
LIBFT = libft/libft.a

SRC = src/main.c \
	src/builtins/blt_cd.c \
	src/builtins/blt_echo.c \
	src/builtins/blt_env.c \
	src/builtins/blt_exit.c \
	src/builtins/blt_exit_max.c \
	src/builtins/blt_export.c \
	src/builtins/blt_pwd.c \
	src/builtins/blt_unset.c \
	src/builtins/utils_blt_export.c \
	src/builtins/utils_error.c \
	src/exec/build_env.c \
	src/exec/exec_and_or.c \
	src/exec/exec_cmd.c \
	src/exec/exec_cmd_child.c \
	src/exec/exec_core.c \
	src/exec/exec_core_blt.c \
	src/exec/exec_group.c \
	src/exec/exec_pipe.c \
	src/exec/exec_pipe_child.c \
	src/exec/exec_redir.c \
	src/exec/exec_utils.c \
	src/exec/resolve_path.c \
	src/expand/exp_calc_if_need_new_var.c \
	src/expand/exp_cringe_dolars.c \
	src/expand/exp_env_var.c \
	src/expand/exp_none_var.c \
	src/expand/exp_set_exp_extract_var.c \
	src/expand/exp_utils_1.c \
	src/expand/exp_utils_2.c \
	src/expand/exp_var_append_without_new_idx.c \
	src/expand/exp_verif_expand.c \
	src/expand/expand.c \
	src/lexer/lex_pars.c \
	src/lexer/lex_pars_elements.c \
	src/lexer/lex_pars_valid_word.c \
	src/lexer/lexer.c \
	src/lexer/lexer_debug.c \
	src/lexer/lexer_set_value.c \
	src/lexer/lexer_tokeniser.c \
	src/lexer/lexer_utils.c \
	src/heredoc/hd_resolve.c \
	src/heredoc/hd_resolve_token_error.c \
	src/heredoc/hd_utils.c \
	src/parser/ast.c \
	src/parser/parser.c \
	src/parser/parser_cmd.c \
	src/parser/parser_cmd_utils.c \
	src/parser/parser_error.c \
	src/parser/parser_redirect.c \
	src/utils/add_pwd_env.c \
	src/utils/add_shlvl_env.c \
	src/utils/clean_static_var.c \
	src/utils/free.c \
	src/utils/init_env.c \
	src/utils/readline_stash.c \
	src/utils/readline_utils.c \
	src/utils/signals.c \
	src/utils/verif_if_need_expand.c \
	src/wildcard/wildcard_compare.c \
	src/wildcard/wildcard_core.c \
	src/wildcard/wildcard_return.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
