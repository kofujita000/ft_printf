/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_loop_character.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:56:56 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 15:17:30 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	__ft_printf_loop_character(const char chr, unsigned int count)
{
	char			buf[0x10];
	unsigned int	j;
	unsigned int	cnt_div;
	int				res;
	int				ret;

	j = 0;
	while (j < 0x10)
		buf[j++] = chr;
	j = -1;
	ret = 0;
	cnt_div = count / 0x10;
	while (++j < cnt_div)
	{
		res = write (1, buf, 0x10);
		if (res == -1)
			return (res);
		ret += res;
	}
	res = write (1, buf, count % 0x10);
	if (res == -1)
		return (res);
	ret += res;
	return (ret);
}
