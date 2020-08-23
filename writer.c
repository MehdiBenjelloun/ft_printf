/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 02:18:44 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/18 09:57:13 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		annexe(t_save *s)
{
	if ((s->o).space)
		write_on(s, ' ', 1);
	else if ((s->o).plus)
		write_on(s, '+', 1);
	if (s->negative)
		write_on(s, '-', 1);
}

void		write_conversion(t_save *s)
{
	if (s->pf)
		(s->pf)(s);
	else
		write_on(s, *(s->s), 1);
}

ssize_t		left_space(t_save *s)
{
	size_t	less;

	if (ft_strchr(NUMBER, *(s->s)))
	{
		if (!s->data.ull && s->precision_on && !(s->o).preci)
			s->lg = 0;
		less = s->lg + s->zero_len + s->pfix_lg;
		less += ((s->o).plus ? 1 : 0) + ((s->o).space ? 1 : 0);
		if (ft_strchr("dDi", *(s->s)) && s->data.ll < 0)
		{
			less++;
			s->negative = 1;
		}
	}
	else if (ft_strchr(STR, *(s->s)))
		less = s->lg;
	else
		less = 1;
	return ((s->o).width > less ? (s->o).width - less : 0);
}

int			init_conversion(t_save *s, char *c)
{
	*c = ' ';
	prefix(s);
	if (s->precision_on && !ft_strchr("sS", *(s->s)))
		(s->o).zero = 0;
	if ((s->o).zero)
		*c = '0';
	s->zero_len = (s->o).preci > s->lg ? (s->o).preci - s->lg : 0;
	s->space_len = left_space(s);
	if ((s->o).sharp && ft_strchr("oOp", *(s->s)))
		(s->o).preci++;
	return ((s->o).sharp || (*(s->s) == 'p'));
}

void		conversion(t_save *s)
{
	char	c;

	s->pfix = init_conversion(s, &c);
	if ((s->o).minus)
	{
		annexe(s);
		s->pfix ? prefix_it(s) : 42;
		write_conversion(s);
		write_on(s, c, s->space_len);
	}
	else
	{
		c == '0' ? annexe(s) : 42;
		if ((s->o).sharp || (*(s->s) == 'p'))
		{
			c == ' ' ? write_on(s, c, s->space_len) : 42;
			s->pfix ? prefix_it(s) : 42;
			c == '0' ? write_on(s, c, s->space_len) : 42;
		}
		else
			write_on(s, c, s->space_len);
		c == ' ' ? annexe(s) : 42;
		write_conversion(s);
	}
}
