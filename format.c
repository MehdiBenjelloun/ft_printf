/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 03:49:46 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/18 12:58:27 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		check_modifier_di(t_save *s)
{
	if ((s->o).j)
		s->data.ull = va_arg(s->va, intmax_t);
	else if ((s->o).z)
		s->data.ull = va_arg(s->va, size_t);
	else if ((s->o).ll)
		s->data.ull = va_arg(s->va, long long);
	else if ((s->o).l)
		s->data.ull = va_arg(s->va, long);
	else if ((s->o).h)
		s->data.ull = (short)va_arg(s->va, int);
	else if ((s->o).hh)
		s->data.ull = (signed char)va_arg(s->va, int);
}

void		check_modifier_ouxx(t_save *s)
{
	if ((s->o).j)
		s->data.ull = va_arg(s->va, uintmax_t);
	else if ((s->o).z)
		s->data.ull = va_arg(s->va, size_t);
	else if ((s->o).ll)
		s->data.ull = va_arg(s->va, unsigned long long);
	else if ((s->o).l)
		s->data.ull = va_arg(s->va, unsigned long);
	else if ((s->o).h)
		s->data.ull = (unsigned short)va_arg(s->va, int);
	else if ((s->o).hh)
		s->data.ull = (unsigned char)va_arg(s->va, int);
}

void		format_str(t_save *s)
{
	if (ft_strchr("CS", *(s->s)) || (ft_strchr("cs", *(s->s)) && (s->o).l))
		format_str_unicode(s);
	else if (*(s->s) == 'c' && !(s->o).l)
	{
		s->pf = conversion_char;
		s->data.c = (char)va_arg(s->va, int);
		s->lg = 1;
	}
	else if (*(s->s) == 's' && !(s->o).l)
	{
		s->pf = conversion_str;
		s->data.str = va_arg(s->va, char*);
		if (s->precision_on && !(s->o).preci)
			s->lg = 0;
		if (!s->data.str)
		{
			s->pf = conversion_str_null;
			s->lg = 6;
		}
		else
			s->lg = ft_strlen(s->data.str);
	}
	if (s->precision_on)
		s->lg = (s->lg > (s->o).preci ? (s->o).preci : s->lg);
	(s->o).plus = 0;
}

void		format_unsigned(t_save *s)
{
	(s->o).plus = 0;
	(s->o).space = 0;
	if (ft_strchr("oO", *(s->s)))
		s->base = 8;
	if (ft_strchr("uU", *(s->s)))
		s->base = 10;
	if (ft_strchr("xXp", *(s->s)))
		s->base = 16;
	if (!s->modif && *(s->s) != 'p')
		s->data.ull = va_arg(s->va, unsigned int);
	else if (*(s->s) == 'p')
		s->data.ull = va_arg(s->va, unsigned long long);
	else
		check_modifier_ouxx(s);
	s->lg = len_nb(s->data.ull, s->base);
}

void		format_number(t_save *s)
{
	s->pf = conversion_number;
	if (ft_strchr("dDi", *(s->s)))
	{
		s->signe = 1;
		s->base = 10;
		if (!s->modif)
			s->data.ull = va_arg(s->va, int);
		else
			check_modifier_di(s);
		s->lg = len_nb_integer(s->data.ull, s->base);
	}
	else if (ft_strchr("oOuUxXp", *(s->s)))
		format_unsigned(s);
}
