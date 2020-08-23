/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 13:14:01 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/22 21:17:31 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		extract_number(t_save *s)
{
	int			select;
	size_t		nb;
	size_t		temp;

	nb = 0;
	select = 0;
	if (*(s->s) == '.' && (select = 1))
		(s->s)++;
	while (*(s->s) && *(s->s) >= '0' && *(s->s) <= '9')
	{
		temp = nb;
		nb = nb * 10 + *(s->s) - '0';
		if (nb < temp && !(nb = 0))
			while (*(s->s) && *(s->s) >= '0' && *(s->s) <= '9')
				(s->s)++;
		(s->s)++;
	}
	(s->s)--;
	if (select == 0)
		(s->o).width = nb;
	else
	{
		(s->o).preci = nb;
		s->precision_on = 1;
	}
}

static void		select_options(t_save *s)
{
	if (*(s->s) == '#')
		(s->o).sharp = 1;
	else if (*(s->s) == '0')
		(s->o).zero = 1;
	else if (*(s->s) == '-')
		(s->o).minus = 1;
	else if (*(s->s) == '+')
		(s->o).plus = 1;
	else if (*(s->s) == ' ')
		(s->o).space = 1;
	else if (*(s->s) == '.' || (*(s->s) > '0' && *(s->s) <= '9'))
		extract_number(s);
	else if (ft_strchr(MODIFIER, *(s->s)) && (s->modif = 1))
	{
		if (*(s->s) == 'h' && ((s->o).h = 1))
			if (*(s->s + 1) == 'h' && !((s->o).h = 0) && (s->s)++)
				(s->o).hh = 1;
		if (*(s->s) == 'l' && ((s->o).l = 1))
			if (*(s->s + 1) == 'l' && !((s->o).l = 0) && (s->s)++)
				(s->o).ll = 1;
		if (*(s->s) == 'j')
			(s->o).j = 1;
		if (*(s->s) == 'z')
			(s->o).z = 1;
	}
}

static void		update(t_save *s)
{
	ft_memset((void*)&(s->options), 0, sizeof(size_t) * 4);
	init_fields(s);
	while (*(s->s) && ft_strchr(OPTIONS, *(s->s)))
	{
		select_options(s);
		(s->s)++;
	}
	if (!*(s->s))
		return ;
	formatting(s);
	if (s->error)
		return ;
	conversion(s);
}

void			parsing(t_save *s)
{
	while (*s->s)
	{
		if (*s->s == PCT && s->s++)
		{
			if (!*s->s)
				break ;
			update(s);
			if (!*s->s || s->error)
				return ;
			s->s++;
			continue ;
		}
		if (!*s->s)
			return ;
		(s->buff)[s->cpt++] = *s->s;
		check_buff(s);
		s->s++;
	}
}

int				ft_printf(const char *s, ...)
{
	t_save		save;

	if (BUFF_SIZE == 0)
		return (-1);
	va_start(save.va, s);
	save.s = (char*)s;
	save.size = 0;
	save.cpt = 0;
	save.error = 0;
	parsing(&save);
	if (save.error)
	{
		write(1, save.buff, save.cpt);
		return (-1);
	}
	save.size += save.cpt;
	write(1, save.buff, save.cpt);
	return (save.size);
}
