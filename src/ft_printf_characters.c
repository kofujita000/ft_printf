/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:26:55 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/05 19:06:46 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static const char	*frm_next(const char *frm);

static int			write_percent(const char *next,
						t_printf_opt_flag_info *ofi);

const char	*__ft_printf_characters(const char *frm, int *ret,
				t_printf_opt_flag_info *ofi)
{
	int			res;
	const char	*next;

	while (frm)
	{
		next = frm_next (frm);
		if (frm == next && !*next)
			return (0x00);
		res = write (1, frm, next - frm);
		*ret += res;
		if (res == -1 || !*next)
			break ;
		next = __ft_printf_info (next, ofi);
		if (*next != '%')
			break ;
		res = write_percent (next, ofi);
		if (res == -1)
			break ;
		*ret += res;
		frm = next + 1;
	}
	if (res == -1)
		*ret = res;
	return (next);
}

const char	*frm_next(const char *frm)
{
	while (*frm && *frm != '%')
		frm++;
	return (frm);
}

static int	write_percent(const char *next, t_printf_opt_flag_info *ofi)
{
	int	res;

	res = 0;
	if (!ofi->minus_opt)
	{
		if (0 < ofi->width - 1)
			res = __ft_printf_loop_character (' ', ofi->width - 1);
		if (res == -1)
			return (res);
		res += write (1, next, 1);
	}
	else
	{
		res = write (1, next, 1);
		if (res == -1)
			return (res);
		if (0 < ofi->width - 1)
			res += __ft_printf_loop_character (' ', ofi->width - 1);
	}
	return (res);
}
