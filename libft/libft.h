/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:01:06 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/31 13:46:21 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
//----ft_libc/ft_printf/gnl_include----//
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
//--end_ft_libc/ft_printf/gnl_include--//
//-------------------------------//
//----ft_printf_include----//
# include <stdarg.h>
//--end_ft_printf_include--//
//----------------------------//
//-----get_next_line_include-----//
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
//---end_get_next_line_include---//
//-------------------------//
//-----libc_ft-----//
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t e_cnt, size_t e_size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memchr(const void *mem, int chr, size_t size);
int		ft_memcmp(const void *p1, const void *p2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *ptr, int val, size_t cnt);
char	*ft_strchr(const char *string, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *tab);
size_t	ft_strclen(const char *tab, const char c);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
char	*ft_strnstr(const char *tab, const char *chr, size_t n);
char	*ft_strrchr(const char *string, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_min(int *arr, int size);
int		ft_max(int *arr, int size);
int		ft_med(int *arr, int size);
void	ft_swap(int *a, int *b);
void	ft_qsort(int *arr, int low, int high);

typedef struct s_splitvar
{
	int		i;
	int		j;
	int		start;
	char	**tab;
}			t_splitvar;
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
//----end_libc_ft---//
//-----------------//
//-----lst_ft-----//
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
//---end_lst_ft---//
//------------------//
//-----ft_printf-----//
int		ft_printf(const char *str, ...);
int		ft_printf_c(int c);
int		ft_printf_s(char *str);
int		ft_printf_d_i(int n);
int		ft_printf_u(unsigned int n);
int		ft_printf_p(unsigned long hex);
int		ft_printf_hex(unsigned int hex, char c);

typedef struct ft_printf_val
{
	va_list	arg;
	int		i;
	int		size;
}		t_var_printf_val;

typedef struct s_printf_u
{
	char				*tab;
	unsigned int		len;
	long unsigned int	nb;
	int					size;
}					t_var_printf_u;

typedef struct printf_hex
{
	char			*res;
	char			*tab;
	unsigned long	temp;
	int				len;
	int				size;
}				t_var_printf_hex;
//---end_ft_printf---//
//---------------------//
//-----get_next_line-----//
typedef struct s_get_next_line
{
	char	*buf;
	char	*temp;
	char	*res;
	ssize_t	c_buf;
	ssize_t	t_size;
	ssize_t	t_read;
}			t_var_gnl;
/*get_next_line.c*/
char	*get_next_line(int fd);
/*get_next_line.c-end*/
/*get_next_line_utils.c*/
void	ft_set_gnl_to_default(t_var_gnl *val, char **stash, int status);
size_t	ft_strlen(const char *tab);
int		ft_gnl_check_break(t_var_gnl *val, int state);
/*get_next_line_utils.c-end*/
//---end_get_next_line---//
//-------------------//
//-----My_ft-----//
char	*read_from_stdin(void);
char	*ft_strjoin_from_2d(char *s1, char **s2, size_t start);
char	*ft_strdupcat(char *dest, char *src, ssize_t *size, ssize_t add_size);
void	ft_print_array(int *arr, int size);
int		ft_str2dlen(char **str);
int		ft_atoi_hex(char *str);
int		ft_strccnt(char *str, char c);
void	ft_free2c(char **ptr);
int		ft_cnt_words(const char *str);
void	ft_lstprintf(t_list *lst, char format);
//---end_My_ft---//

#endif
