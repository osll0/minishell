/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:00:41 by seokson           #+#    #+#             */
/*   Updated: 2025/04/20 22:52:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_format
{
	int		minus_flag;
	int		zero_flag;
	int		dot_flag;
	int		hash_flag;
	int		space_flag;
	int		plus_flag;
	int		width;
	int		precision;
	char	type;
}	t_format;

int			ft_printf(const char *format, ...);

int			handle_format(const char **format, va_list args);
int			handle_char(t_format info, int c);
int			handle_string(t_format info, char *s);
int			handle_pointer(t_format info, void *ptr);
int			handle_int(t_format info, int n);
int			handle_unsigned(t_format info, unsigned int n);
int			handle_hex(t_format info, unsigned int n, int uppercase);

t_format	parse_format(const char **format);
t_format	init_format(void);
void		normalize_flags(t_format *info);

int			ft_base_len(unsigned long n, int base);
void		ft_padding_len(t_format info, long n, int *pad, int *zpad);

int			ft_put_padding(char c, int count);
int			ft_put_absnbr(long n);
int			ft_put_hex(unsigned long n, int is_upper);
int			ft_put_prefix(int uppercase);

#endif
