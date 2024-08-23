/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:50:34 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/05 17:26:10 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	plus(char val_c, int *ret, t_printf_opt_flag_info *ofi);

static void	minus(char val_c, int *ret, t_printf_opt_flag_info *ofi);

const char	*__ft_printf_c(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	char	val_c;

	if (*frm != 'c')
		return (frm);
	val_c = (char)(unsigned long)val;
	if (!ofi->minus_opt)
		plus (val_c, ret, ofi);
	else
		minus (val_c, ret, ofi);
	return (frm + 1);
}

void	plus(char val_c, int *ret, t_printf_opt_flag_info *ofi)
{
	int	res;

	res = 0;
	if (ofi->width)
		res = __ft_printf_loop_character (' ', ofi->width - 1);
	*ret += res;
	if (res != -1)
		res = write (1, &val_c, 1);
	*ret = -(res == -1) + (res != -1) * ((*ret) + res);
}

void	minus(char val_c, int *ret, t_printf_opt_flag_info *ofi)
{
	int	res;

	res = write (1, &val_c, 1);
	*ret += res;
	if (res != -1 && ofi->width)
	{
		res = __ft_printf_loop_character (' ', ofi->width - 1);
		*ret += res;
	}
	*ret = -(res == -1) + (res != -1) * ((*ret));
}
