/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:58:10 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:20:02 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

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

#endif
