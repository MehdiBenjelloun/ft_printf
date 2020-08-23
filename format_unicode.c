/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unicode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 05:40:49 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/20 00:33:47 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		format_str_unicode(t_save *s)
{
	s->pf = format_unicode;
	if (ft_strchr("cC", *(s->s)))
	{
		s->data.e = va_arg(s->va, int);
		s->lg = unicode_char_len(s->data.e);
		if ((s->error = check_unicode_char(s->data.e)))
			return ;
	}
	else if (ft_strchr("sS", *(s->s)))
	{
		s->data.eu = va_arg(s->va, int*);
		if (!s->data.eu)
		{
			s->pf = conversion_str_null;
			s->lg = 6;
		}
		else
		{
			s->lg = unicode_strlen(s->data.eu, (s->o).preci, s->precision_on);
			if ((s->error = check_unicode_str(s->data.eu)))
				return ;
		}
	}
}
