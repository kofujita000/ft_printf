/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:04:56 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 15:12:13 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	__utoa(unsigned int un, char *ret);

const char	*__ft_printf_u(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	unsigned int	val_u;
	char			addr[0x10];

	if (*frm != 'u')
		return (frm);
	val_u = (unsigned int)(unsigned long)val;
	__utoa (val_u, addr);
	__ft_printf_write_numeric(addr, ret, ofi);
	return (frm + 1);
}

void	__utoa(unsigned int un, char *ret)
{
	char			*rp;
	char			stks[0x10];
	char			*stkp;

	stkp = stks;
	while (1)
	{
		*(stkp++) = (un % 10) + 0x30;
		un /= 10;
		if (!un)
			break ;
	}
	rp = ret;
	while (stks <= --stkp)
		*(rp++) = *stkp;
	*rp = 0x00;
}
