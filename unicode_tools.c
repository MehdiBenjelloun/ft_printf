/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 05:06:57 by mbenjell          #+#    #+#             */
/*   Updated: 2017/09/19 23:58:16 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		unicode_char_len(int c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x1FFFFF)
		return (4);
	return (0);
}

size_t		unicode_strlen(int *str, size_t preci, int precision_on)
{
	size_t	size;
	size_t	len;

	size = 0;
	len = 0;
	if (!precision_on)
	{
		while (*str)
			size += unicode_char_len(*str++);
	}
	else
	{
		while (*str)
		{
			len = unicode_char_len(*str);
			if (preci < len)
				return (size);
			size += len;
			preci -= len;
			str++;
		}
	}
	return (size);
}

int			check_unicode_char(int c)
{
	if (unicode_char_len(c) > (size_t)MB_CUR_MAX)
		return (1);
	return (0);
}

int			check_unicode_str(int *str)
{
	while (*str)
		if (unicode_char_len(*str++) > (size_t)MB_CUR_MAX)
			return (1);
	return (0);
}
