CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_memcmp.c\
			ft_atoi.c\
			ft_atol.c\
			ft_atoi_hex.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memchr.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strclen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c\
			ft_printf.c\
			ft_printf_p.c\
			ft_printf_hex.c\
			ft_printf_utils.c\
			get_next_line.c\
			get_next_line_utils.c\
			read_from_stdin.c\
			ft_strjoin_from_2d.c\
			ft_swap.c\
			ft_qsort.c\
			ft_min.c\
			ft_med.c\
			ft_max.c\
			ft_strdupcat.c\
			ft_print_array.c\
			ft_str2dlen.c\
			ft_strccnt.c\
			ft_free2c.c\
			ft_cnt_words.c\
			ft_lstprintf.c

OBJ = $(SRC:.c=.o)

NAME = libft.a

$(NAME): $(OBJ)
	@$(AR) -rcs $(NAME) $(OBJ)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -f $(OBJ)

fclean: clean
	@$(RM) -f $(NAME)

re: fclean all
