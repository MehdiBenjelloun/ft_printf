/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 13:25:00 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/23 00:39:29 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFF_SIZE		4096
# define RESERVED		64

# define PCT			'%'
# define OPTIONS		"#0-+ .123456789hljz"
# define FORMAT			"sSpdDioOuUxXcC"
# define NUMBER			"pdDioOuUxX"
# define STR 			"sScC"
# define FLAGS 			"#0-+ "
# define MODIFIER		"hljz"

typedef union			u_typage
{
	char				c;
	char				*str;
	int					*eu;
	short				sh;
	int					e;
	long				l;
	long long			ll;
	size_t				s;
	unsigned char		uc;
	unsigned short		ush;
	unsigned long		ul;
	unsigned long long	ull;
	intmax_t			it;
	uintmax_t			uit;
	uint64_t			ubint;
	signed char			sc;
}						t_typage;

typedef struct			s_options
{
	size_t				width;
	size_t				preci;
	int					sharp;
	int					zero;
	int					minus;
	int					plus;
	int					space;
	int					hh;
	int					h;
	int					l;
	int					ll;
	int					j;
	int					z;
}						t_options;

typedef struct			s_save
{
	va_list				va;
	union u_typage		data;
	void				(*pf)(struct s_save*);
	char				buff[BUFF_SIZE + RESERVED];
	char				*s;
	ssize_t				size;
	int					cpt;
	size_t				options[4];
	int					signe;
	uint64_t			base;
	int					precision_on;
	size_t				zero_len;
	size_t				space_len;
	size_t				lg;
	int					pfix_lg;
	char				prefix[2];
	int					uppercase;
	int					negative;
	int					pfix;
	struct s_options	o;
	int					modif;
	int					error;
}						t_save;

typedef struct			s_unicode
{
	unsigned int		data;
	unsigned int		d_new;
	unsigned int		pattern[4];
	int					nb_codets;
	int					cpt;
	int					i;
}						t_unicode;

size_t					ft_strlen(char *s);
size_t					len_nb_integer(long long int n, int base);
size_t					len_nb(unsigned long long n, int base);
char					*ft_strchr(const char *s, int c);
void					ft_memset(void *s, int c, size_t n);
void					ft_memcpy(void *dest, const void *src, size_t n);
void					ft_itob(int64_t nb, t_save *s);
void					ft_uitob(uint64_t nb, t_save *s);
void					check_buff(t_save *s);
void					parsing(t_save *s);
void					prefix(t_save *s);
void					prefix_it(t_save *s);
void					write_on(t_save *s, char c, ssize_t i);
void					exception(t_save *s);
void					formatting(t_save *s);
void					format_str(t_save *s);
void					format_unicode(t_save *s);
void					format_str_unicode(t_save *s);
void					format_unsigned(t_save *s);
void					format_number(t_save *s);
void					conversion_char(t_save *s);
void					conversion_str(t_save *s);
void					conversion_str_null(t_save *s);
void					conversion_number(t_save *s);
void					conversion(t_save *s);
void					init_fields(t_save *s);
void					init_unicode(t_unicode *u);
void					set_pattern(t_unicode *u, int data);
void					write_unicode(t_save *s, t_unicode *u);
void					unicode_str(t_save *s, t_unicode *u, int *data);
size_t					unicode_char_len(int c);
size_t					unicode_strlen(int *str, size_t preci, int preci_on);
int						check_unicode_char(int c);
int						check_unicode_str(int *str);
int						ft_printf(const char *s, ...);

#endif
