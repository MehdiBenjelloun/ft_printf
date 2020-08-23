/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:43:37 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:42 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		exception(t_save *s)
{
	if ((s->o).minus)
		(s->o).zero = 0;
	if ((s->o).plus)
		(s->o).space = 0;
	if (!ft_strchr("dDi", *(s->s)))
		(s->o).space = 0;
	if (ft_strchr("oOuUxXp", *(s->s)))
	{
		(s->o).plus = 0;
		(s->o).space = 0;
	}
	if (ft_strchr("DUO", *(s->s)))
	{
		(s->o).l = 1;
		s->modif = 1;
	}
	if (ft_strchr("X", *(s->s)))
		s->uppercase = 1;
	if (ft_strchr("cC%", *(s->s)) || !ft_strchr(FORMAT, *(s->s)))
		s->precision_on = 0;
	if ((s->o).sharp && *(s->s) == 'o')
		if ((s->o).preci > 0)
			(s->o).preci--;
}

void		conversion_number(t_save *s)
{
	write_on(s, '0', s->zero_len);
	if (!s->data.ull && s->precision_on && !(s->o).preci)
		return ;
	if (s->signe && ft_strchr("dDi", *(s->s)))
		ft_itob(s->data.ull, s);
	else
		ft_uitob(s->data.ull, s);
	check_buff(s);
}

void		conversion_str(t_save *s)
{
	if (s->precision_on && !(s->o).preci)
		return ;
	while (*(s->data.str))
	{
		if (s->precision_on)
			if ((s->o).preci-- == 0)
				break ;
		(s->buff)[s->cpt++] = *s->data.str++;
		check_buff(s);
	}
}

void		conversion_char(t_save *s)
{
	write_on(s, s->data.c, 1);
	check_buff(s);
}

void		conversion_str_null(t_save *s)
{
	char	text_null[6];
	int		n;

	n = 0;
	ft_memcpy(text_null, "(null)", 6);
	if (s->precision_on)
		while (n < 6 && (s->o).preci--)
			write_on(s, text_null[n++], 1);
	else
		while (n < 6)
			write_on(s, text_null[n++], 1);
}
