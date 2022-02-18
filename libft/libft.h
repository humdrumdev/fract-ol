/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:57:40 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 20:22:31 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** global headers
*/
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>

# include "ft_printf/u_int.h"
# include "ft_printf/char.h"
# include "ft_printf/percent.h"
# include "ft_printf/decimal_di.h"
# include "ft_printf/lst.h"
# include "ft_printf/core.h"
# include "ft_printf/parser.h"
# include "ft_printf/conv_handler.h"
# include "ft_printf/str.h"
# include "ft_printf/utils.h"
# include "ft_printf/void_p.h"
# include "ft_printf/flags.h"
# include "ft_printf/hex.h"

void			init_conv_details(t_conv_details *det);
int				flag_handler(char type, char *flags, t_conv_details *det);
t_conv_details	*conv_handler(t_conv *conv, va_list ap);
int				print_type(va_list ap, t_conv_details *det, char type);
int				print_node(t_conv *conv, va_list ap);
int				ft_printf(const char *format, ...);

/*
** free_alloc
*/

typedef struct s_mem
{
	void			*content;
	struct s_mem	*last;
	struct s_mem	*next;
}				t_mem;

int				free_alloc(void **to_alloc, size_t size);
void			clean_exit(int c, const char *msg,
					void (*clnr)(void **), void **mem);

/*
** get_next_line
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_reader
{
	char	*buf;
	int		bytes;
}				*t_reader;

char			*get_next_line(int fd);

/*
******** first part *******
*/
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *src);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *hs, const char *needle, size_t len);
int				ft_strncmp(const char *lhs, const char *rhs, size_t count);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t count, size_t size);
/*
** memory funcs
*/
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t count);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *lhs, const void *rhs, size_t count);
/*
******** second part *******
**
** string manipulation
*/
typedef struct s_chunk
{
	char			*word;
	struct s_chunk	*next;
}				t_chunk;

void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s, char const *set);
char			**ft_split(char const *s, char c);
/*
** io funcs
*/
char			*ft_itoa(int n);
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putendl_fd(char *s, int fd);
int				ft_putnbr_fd(int n, int fd);
/*
******** bonus part *******
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef void	(*t_del)(void *);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *newl);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *head);
void			ft_lstadd_back(t_list **lst, t_list *newl);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **alst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), t_del del);
/*
** utilities
*/
int				ft_absolutev(int a);
int				ft_is_negative(int a);
int				ft_greater_than(int a, int b);
int				ft_is_equal(int a, int b);
int				ft_less_than(int a, int b);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
int				ft_is_successor(int a, int b);
int				ft_bounded(int lhs, int num, int rhs);

#endif
