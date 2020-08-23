/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 01:05:40 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/18 09:33:02 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		prefix(t_save *s)
{
	if (((s->o).sharp || ft_strchr("p", *(s->s))))
	{
		if (s->data.ull && ft_strchr("oO", *(s->s)))
		{
			s->pfix_lg = 1;
			s->prefix[0] = '0';
		}
		else if (s->data.ull && ft_strchr("xXp", *(s->s)))
		{
			s->pfix_lg = 2;
			s->prefix[0] = '0';
			s->prefix[1] = s->uppercase ? 'X' : 'x';
		}
		else if (ft_strchr("p", *(s->s)))
		{
			s->pfix_lg = 2;
			s->prefix[0] = '0';
			s->prefix[1] = s->uppercase ? 'X' : 'x';
		}
	}
}

void		prefix_it(t_save *s)
{
	int		len;
	int		i;

	len = s->pfix_lg;
	i = 0;
	while (len--)
		write_on(s, s->prefix[i++], 1);
}

void		write_on(t_save *s, char c, ssize_t i)
{
	while (i--)
	{
		s->buff[s->cpt++] = c;
		check_buff(s);
	}
}

void		check_buff(t_save *s)
{
	if (s->cpt >= BUFF_SIZE)
	{
		write(1, s->buff, s->cpt);
		s->size += s->cpt;
		s->cpt = 0;
	}
}
