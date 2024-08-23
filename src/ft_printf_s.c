/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:03:55 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/05 19:07:05 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	plus(const char *val_s, int *ret, t_printf_opt_flag_info *ofi);

static void	minus(const char *val_s, int *ret, t_printf_opt_flag_info *ofi);

const char	*__ft_printf_s(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	const char	*val_s;

	if (*frm != 's')
		return (frm);
	val_s = (const char *)val;
	if (!val_s)
	{
		val_s = "(null)";
	}
	if (!ofi->minus_opt)
		plus (val_s, ret, ofi);
	else
		minus (val_s, ret, ofi);
	return (frm + 1);
}

void	plus(const char *val_s, int *ret, t_printf_opt_flag_info *ofi)
{
	int	res;
	int	val_s_len;

	res = 0;
	val_s_len = (int)__ft_printf_strlen (val_s);
	if (ofi->dot_flag && ofi->precision < val_s_len)
		val_s_len = ofi->precision;
	if (val_s_len < ofi->width)
		res = __ft_printf_loop_character (' ', ofi->width - val_s_len);
	*ret += res;
	if (res != -1)
		res = write (1, val_s, val_s_len);
	*ret = -(res == -1) + (res != -1) * ((*ret) + res);
}

void	minus(const char *val_s, int *ret, t_printf_opt_flag_info *ofi)
{
	int	res;
	int	val_s_len;

	res = 0;
	val_s_len = (int)__ft_printf_strlen (val_s);
	if (ofi->dot_flag && ofi->precision < val_s_len)
		val_s_len = ofi->precision;
	res = write (1, val_s, val_s_len);
	*ret += res;
	if (res != -1 && val_s_len < ofi->width)
	{
		res = __ft_printf_loop_character (' ', ofi->width - val_s_len);
		*ret += res;
	}
	*ret = -(res == -1) + (res != -1) * (*ret);
}
