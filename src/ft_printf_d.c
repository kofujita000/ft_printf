/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:12:32 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 15:16:36 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	__dtoa(int val, char *ret);

const char	*__ft_printf_d(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	int		val_d;
	char	addr[0x10];

	if (*frm != 'd')
		return (frm);
	val_d = (int)(unsigned long)val;
	__dtoa (val_d, addr);
	__ft_printf_write_numeric(addr, ret, ofi);
	return (frm + 1);
}

void	__dtoa(int n, char *ret)
{
	char			*rp;
	char			stks[0x10];
	char			*stkp;
	unsigned int	un;

	stkp = stks;
	stks[0x0f] = (n < 0);
	un = (n + (n < 0)) * (-(n < 0) + !(n < 0)) + (n < 0);
	while (1)
	{
		*(stkp++) = (un % 10) + 0x30;
		un /= 10;
		if (!un)
			break ;
	}
	if (stks[0x0f])
		*(stkp++) = '-';
	rp = ret;
	while (stks <= --stkp)
		*(rp++) = *stkp;
	*rp = 0x00;
}
