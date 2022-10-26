/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:05:26 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/21 13:15:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>	/* size_t */

void			ft_bzero(void *addr, size_t size);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			ft_putstr(char *str);
void			ft_putstr_fd(char const *str, int fd);
void			ft_putnbr_base_fd(long nb, const char *base_char, int fd);
void			ft_putnbr(long nb);
void			ft_putchar_fd(char c, int fd);
char			*ft_strdup(char *str);

/*
# include <string.h>
# include <stdarg.h>


# define BUFF_SIZE 4200

# define C_GREY		"\033[030m"
# define C_RED		"\033[031m"
# define C_GREEN	"\033[032m"
# define C_YELLOW	"\033[033m"
# define C_BLUE		"\033[034m"
# define C_MAGENTA	"\033[035m"
# define C_CYAN		"\033[036m"

# define B_GREY		"\033[040m"
# define B_RED		"\033[041m"
# define B_GREEN	"\033[042m"
# define B_YELLOW	"\033[043m"
# define B_BLUE		"\033[044m"
# define B_MAGENTA	"\033[045m"
# define B_CYAN		"\033[046m"

# define C_RESET	"\033[0m"

# define BA_BIN		"01"
# define BA_DEC		"0123456789"
# define BA_HEX		"0123456789abcdef"
# define BA_HEXC	"0123456789ABCDEF"

typedef struct	s_list
{
	void			*data;
	size_t			d_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *ptr, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
void			ft_putendl(char const *s);
void			ft_putchar(char c);
void			ft_putnbr(int n);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, int nb);
size_t			ft_strlcat(char *dest, const char *srcc, size_t size);
int				ft_atoi(const char *strc);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *str, const char *to_find);
int				ft_strncmp(const char *s1c, const char *s2c, size_t n);
char			*ft_strnstr(const char	*str, const char *to_find, size_t len);
int				ft_strcmp(const char *s1c, const char *s2c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int arg);
int				ft_toupper(int arg);
char			*ft_strnew(size_t size);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			ft_strdel(char **ass);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char			*ft_strndup(const char *s, size_t n);

void			ft_print_words_tables(char **tab);
int				ft_isspace(int c);
char			*ft_strncpy_bw(char *dest, const char *src, size_t n);
void			*ft_memdup(void **dest, const void *src, size_t n);
t_list			*ft_lstnew_empty(void);
char			*ft_strjoin_free(char *s1, char *s2);
int				get_next_line(const int fd, char **line);
int				gnlite(const int fd, char **line);
char			*ft_lltos_base(long long nb, const char *base_c);
char			*ft_ulltos_base(unsigned long long nb, const char *base_c);
char			*ft_strrev(char *s);
void			ft_lstrev(t_list **lst);
void			ft_swap(void **a, void **b);
void			ft_pr_err(char *prg_name, char *name);
void			ft_pr_errno(char *prg_name, char *name, int errrno);
void			ft_lstsort(t_list *lst, int (*cmp)(void *, void *));
char			ft_longlen(long nb);
void			ft_lst_free_data(t_list *lst);
void			ft_lst_free(t_list *lst);

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *restrict format, ...);
int				ft_asprintf(char **restrict str, const char *restrict format,
...);
int				ft_vasprintf(char **restrict str, char *restrict format,
va_list va);
*/

#endif
