/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 13:53:23 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/16 08:01:03 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char*)s;
	while (*p)
	{
		if (*(unsigned char*)p == (unsigned char)c)
			return (p);
		p++;
	}
	return (NULL);
}

void		ft_memset(void *s, int c, size_t n)
{
	while (n)
		((unsigned char*)s)[--n] = (unsigned char)c;
}

void		ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n--)
		*((unsigned char*)dest++) = *((unsigned char*)src++);
}

void		ft_itob(int64_t nb, t_save *s)
{
	if (nb < 0)
		nb = -nb;
	ft_uitob((uint64_t)nb, s);
}

void		ft_uitob(uint64_t nb, t_save *s)
{
	static const char l[16] = "0123456789abcdef";
	static const char lup[16] = "0123456789ABCDEF";

	if (nb > s->base - 1)
		ft_uitob(nb / s->base, s);
	(s->buff)[(s->cpt)++] = s->uppercase ? lup[nb % s->base] : l[nb % s->base];
}
