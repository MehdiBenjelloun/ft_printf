/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:22:52 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/18 16:51:28 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				init_unicode(t_unicode *u)
{
	u->d_new = 0;
	u->nb_codets = 0;
	u->cpt = 0;
	u->i = 0;
	(u->pattern)[0] = 0;
	(u->pattern)[1] = 0xc080;
	(u->pattern)[2] = 0xe08080;
	(u->pattern)[3] = 0xf0808080;
}

void				set_pattern(t_unicode *u, int data)
{
	int nb_codets;

	nb_codets = unicode_char_len(data);
	u->nb_codets = nb_codets;
	u->d_new = (u->pattern)[u->nb_codets - 1];
}

void				write_unicode(t_save *s, t_unicode *u)
{
	unsigned char	temp[u->i];

	while (u->nb_codets--)
	{
		u->d_new |= (u->data & 0x3f) << (8 * u->i++);
		u->data = u->data >> 6;
	}
	u->nb_codets = u->i;
	while (u->i--)
	{
		if (u->i >= 0)
			temp[u->i] = (unsigned char)u->d_new;
		u->d_new >>= 8;
	}
	ft_memcpy(&(s->buff)[s->cpt], temp, u->nb_codets);
	s->cpt += u->nb_codets;
	check_buff(s);
}

void				unicode_str(t_save *s, t_unicode *u, int *str)
{
	size_t			len;

	while (*str)
	{
		len = unicode_char_len(*str);
		init_unicode(u);
		u->data = *str;
		if (s->precision_on)
			if ((s->o).preci < len)
				break ;
		if (u->data <= 0x7F)
			write_on(s, (char)u->data, 1);
		else if (u->data <= 0x1FFFFF)
		{
			set_pattern(u, u->data);
			write_unicode(s, u);
		}
		str++;
		(s->o).preci -= len;
	}
}

void				format_unicode(t_save *s)
{
	t_unicode		u;

	if (s->precision_on && !(s->o).preci)
		return ;
	if (ft_strchr("cC", *(s->s)))
	{
		init_unicode(&u);
		u.data = s->data.e;
		if (u.data <= 0x7F)
			write_on(s, (char)u.data, 1);
		else if (u.data <= 0x1FFFFF)
		{
			set_pattern(&u, u.data);
			write_unicode(s, &u);
		}
	}
	else if (ft_strchr("sS", *(s->s)))
		unicode_str(s, &u, s->data.eu);
}
