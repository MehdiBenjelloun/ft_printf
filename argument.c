/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 21:21:17 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/18 16:15:29 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			len_nb_integer(long long int n, int base)
{
	size_t		i;

	if (!n)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

size_t			len_nb(unsigned long long n, int base)
{
	size_t		i;

	if (!n)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

size_t			ft_strlen(char *s)
{
	size_t		size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

void			init_fields(t_save *s)
{
	s->pf = NULL;
	s->zero_len = 0;
	s->space_len = 0;
	s->lg = 0;
	s->pfix_lg = 0;
	ft_memset((void*)s->prefix, 0, sizeof(char) * 2);
	s->precision_on = 0;
	s->uppercase = 0;
	s->negative = 0;
	s->pfix = 0;
	s->modif = 0;
	(s->o).width = 0;
	(s->o).preci = 0;
	(s->o).sharp = 0;
	(s->o).zero = 0;
	(s->o).minus = 0;
	(s->o).plus = 0;
	(s->o).space = 0;
	(s->o).hh = 0;
	(s->o).h = 0;
	(s->o).l = 0;
	(s->o).ll = 0;
	(s->o).j = 0;
	(s->o).z = 0;
	s->error = 0;
}

void			formatting(t_save *s)
{
	exception(s);
	if (ft_strchr(STR, *(s->s)))
		format_str(s);
	else if (ft_strchr(NUMBER, *(s->s)))
	{
		format_number(s);
		if (s->data.ll < 0)
		{
			(s->o).plus = 0;
			(s->o).space = 0;
		}
	}
	else
	{
		if (*(s->s) == '%')
			(s->o).space = 0;
		(s->o).plus = 0;
	}
}
