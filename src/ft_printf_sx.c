/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:16:20 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 18:49:33 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	__sxtoa(unsigned int un, char *ret);

const char	*__ft_printf_sx(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	unsigned int	val_u;
	char			addr[0x20];

	if (*frm != 'x')
		return (frm);
	val_u = (unsigned int)(unsigned long)val;
	ofi->fp = __ft_printf_sx;
	__sxtoa (val_u, addr);
	__ft_printf_write_numeric(addr, ret, ofi);
	return (frm + 1);
}

void	__sxtoa(unsigned int un, char *ret)
{
	int				bit;
	unsigned char	md;
	unsigned int	nbr;
	char			flag;

	nbr = (unsigned int)un;
	bit = sizeof (nbr) * 8;
	flag = 0;
	while (bit)
	{
		md = ((nbr >> (bit - 4)) & 0x0F);
		flag |= !!md;
		if (flag)
			*(ret++) = md + (0x30 * (md < 0x0A) + 0x57 * !(md < 0x0A));
		md = ((nbr >> (bit - 8)) & 0x0F);
		flag |= !!md;
		if (flag)
			*(ret++) = md + (0x30 * (md < 0x0A) + 0x57 * !(md < 0x0A));
		bit -= 8;
	}
	if (!flag)
		*(ret++) = '0';
	*ret = 0x00;
}
