/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:43:04 by shayeo            #+#    #+#             */
/*   Updated: 2024/08/08 16:00:10 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

//list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstsearchprev(t_list *first, t_list *node);
int		ft_lstsize(t_list *lst);

//normal functions
int		ft_atoi(const char *nptr);
int		ft_atoi_check(const char *nptr, int *valid);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int a);
int		ft_isalpha(int a);
int		ft_isascii(int a);
int		ft_isdigit(int a);
int		ft_isprint(int a);
int		ft_intlen(int n);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *d, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *a);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

//printf

typedef struct printf_format
{
	int		left;
	int		zero;
	int		precision;
	int		precision_no;
	int		alternate;
	int		blank;
	int		sign;
	int		min_width;
	char	specifier;
}	t_format;

char	*ft_char(t_format *specifier, int input);
char	*ft_combine(char *a, char *b, int left, int prefix);
int		ft_flagcheck(int a);
char	*ft_format(t_format *specifier, va_list *ptr);
int		ft_formatspec(const char *c, t_format *f, va_list *ptr, int i);
char	*ft_hex(t_format *s, unsigned int input);
int		ft_hexlen(unsigned int input);
char	*ft_hwidth(int len, int alternate, int zero);
char	*ft_hprecision(int p, unsigned int input, int p_s);
char	*ft_int(t_format *s, int input);
t_list	*ft_iterateinput(t_list *first, const char *input);
void	ft_lowerhex(char *s);
int		ft_printf(const char *input, ...);
char	*ft_percentage(void);
char	*ft_pointer(t_format *s, void *ptr);
int		ft_speccheck(int a);
char	*ft_str(t_format *s, const char *input);
void	ft_structinit(t_format *s);
char	*ft_uint(t_format *s, unsigned int input);
char	*ft_width(int len, int zero, int prefix);

//get_next_line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	assignstr(char *dest, char *str, ssize_t stop);
int		bufflen(char *str);
char	*concatbuffer(char *exist, char *new, ssize_t stop);
char	*extractstr(char *str, int n);
char	*endoffile(char **remaining);
char	*get_next_line(int fd);
int		parsebuffer(char *buffer);
char	*rebuffer(char *buffer, int start);
char	*rdbuffer(int fd, char *buffer, ssize_t *bread, char *remaining);
char	*setparams(ssize_t *bread);

#endif
