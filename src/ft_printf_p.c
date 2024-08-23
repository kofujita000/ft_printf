/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:23:00 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/05 17:20:37 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	btoa(void *val, char *addr);

static void	nil(char flag, char **addr);

static void	plus(const char *addr, int *ret, t_printf_opt_flag_info *ofi);

static void	minus(const char *addr, int *ret, t_printf_opt_flag_info *ofi);

const char	*__ft_printf_p(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi)
{
	char	addr[0x20];

	if (*frm != 'p')
		return (frm);
	btoa (val, addr);
	ofi->fp = __ft_printf_p;
	if (!ofi->minus_opt)
		plus (addr, ret, ofi);
	else
		minus (addr, ret, ofi);
	return (frm + 1);
}

void	btoa(void *val, char *addr)
{
	int				bit;
	unsigned char	md;
	unsigned long	nbr;
	char			flag;

	nbr = (unsigned long)val;
	bit = sizeof (long) * 8;
	flag = 0;
	*(addr++) = '0';
	*(addr++) = 'x';
	while (bit)
	{
		md = ((nbr >> (bit - 4)) & 0x0F);
		flag |= !!md;
		if (flag)
			*(addr++) = md + (0x30 * (md < 0x0A) + 0x57 * !(md < 0x0A));
		md = ((nbr >> (bit - 8)) & 0x0F);
		flag |= !!md;
		if (flag)
			*(addr++) = md + (0x30 * (md < 0x0A) + 0x57 * !(md < 0x0A));
		bit -= 8;
	}
	nil (flag, &addr);
	*addr = 0x00;
}

void	nil(char flag, char **addr)
{
	if (flag)
		return ;
	*(*addr)++ = '0';
}

static void	plus(const char *addr, int *ret, t_printf_opt_flag_info *ofi)
{
	int		res;
	int		fill_len;
	int		addr_len;

	res = 0;
	addr_len = __ft_printf_strlen (addr);
	fill_len = addr_len - 2;
	if (ofi->zero_opt)
		fill_len = ofi->width - 2;
	if (ofi->dot_flag && addr_len <= ofi->precision)
		fill_len = ofi->precision - 2;
	if (!ofi->zero_opt && fill_len < ofi->width - 2)
		res = __ft_printf_loop_character (' ', ofi->width - 2 - fill_len);
	*ret += res;
	if (res != -1)
		res = write (1, addr, 2);
	*ret += res;
	addr += 2;
	if (res != -1 && addr_len - 2 < fill_len)
		res = __ft_printf_loop_character ('0', fill_len - addr_len - 2);
	*ret += res * (addr_len - 2 < fill_len);
	if (res != -1)
		res = write (1, addr, addr_len - 2);
	*ret = -(res == -1) + (res != -1) * ((*ret) + res);
}

static void	minus(const char *addr, int *ret, t_printf_opt_flag_info *ofi)
{
	int		res;
	int		fill_len;
	int		addr_len;

	addr_len = __ft_printf_strlen (addr);
	res = write (1, addr, 2);
	*ret += res;
	addr += 2;
	fill_len = addr_len - 2;
	if (ofi->zero_opt)
		fill_len = ofi->width - 2;
	if (ofi->dot_flag && addr_len <= ofi->precision)
		fill_len = ofi->precision - 2;
	if (res != -1 && addr_len - 2 < fill_len)
		res = __ft_printf_loop_character ('0', fill_len - addr_len - 2);
	*ret += res * (addr_len - 2 < fill_len);
	if (res != -1)
		res = write (1, addr, addr_len - 2);
	*ret += res;
	if (res != -1 && fill_len < ofi->width - 2)
	{
		res = __ft_printf_loop_character (' ', ofi->width - 2 - fill_len);
		*ret = -(res == -1) + (res != -1) * ((*ret) + res);
	}
	*ret = -(res == -1) + (res != -1) * ((*ret));
}
