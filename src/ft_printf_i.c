/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:12:32 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 15:15:44 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	__itoa(int val, char *ret);

const char	*__ft_printf_i(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	int		val_i;
	char	addr[0x10];

	if (*frm != 'i')
		return (frm);
	val_i = (int)(unsigned long)val;
	__itoa (val_i, addr);
	__ft_printf_write_numeric(addr, ret, ofi);
	return (frm + 1);
}

void	__itoa(int n, char *ret)
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
