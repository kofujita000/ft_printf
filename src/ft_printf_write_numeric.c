/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_numeric.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:23:00 by kofujita          #+#    #+#             */
/*   Updated: 2024/06/11 19:19:33 by moco             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	opt(const char *addr, int *ret, t_printf_opt_flag_info *ofi);

static int	opt_len(const char *addr, t_printf_opt_flag_info *ofi);

static void	plus(const char *addr, int *ret, t_printf_opt_flag_info *ofi);

static void	minus(const char *addr, int *ret, t_printf_opt_flag_info *ofi);

void	__ft_printf_write_numeric(char *addr, int *ret,
			t_printf_opt_flag_info *ofi)
{
	if (*addr == '0' && !*(addr + 1) && ofi->dot_flag && !ofi->precision)
	{
		*addr = 0x00;
	}
	if (!ofi->minus_opt)
		plus (addr, ret, ofi);
	else
		minus (addr, ret, ofi);
}

int	opt(const char *addr, int *ret, t_printf_opt_flag_info *ofi)
{
	int	res;

	res = 0;
	if (ofi->sharp_flag && ofi->fp == __ft_printf_lx && *addr != 0x00
		&& (*addr != '0' && *addr != 0x00))
		res = write (1, "0X", 2);
	if (ofi->sharp_flag && ofi->fp == __ft_printf_sx && *addr != 0x00
		&& (*addr != '0' && *addr != 0x00))
		res = write (1, "0x", 2);
	if (ofi->plus_flag && *addr != '-'
		&& ofi->fp != __ft_printf_lx && ofi->fp != __ft_printf_sx)
		res = write (1, "+", 1);
	if (ofi->space_flag && *addr != '-'
		&& ofi->fp != __ft_printf_lx && ofi->fp != __ft_printf_sx)
		res = write (1, " ", 1);
	if (*addr == '-')
		res = write (1, "-", 1);
	*ret = -(res == -1) + (res != -1) * ((*ret) + res);
	return (res);
}

int	opt_len(const char *addr, t_printf_opt_flag_info *ofi)
{
	int	res;

	res = 0;
	if (ofi->sharp_flag && ofi->fp == __ft_printf_lx && *addr != 0x00
		&& (*addr != '0' && *addr != 0x00))
		res = 2;
	if (ofi->sharp_flag && ofi->fp == __ft_printf_sx && *addr != 0x00
		&& (*addr != '0' && *addr != 0x00))
		res = 2;
	if (ofi->plus_flag && *addr != '-'
		&& ofi->fp != __ft_printf_lx && ofi->fp != __ft_printf_sx)
		res = 1;
	if (ofi->space_flag && *addr != '-'
		&& ofi->fp != __ft_printf_lx && ofi->fp != __ft_printf_sx)
		res = 1;
	if (*addr == '-')
		res = 1;
	return (res);
}

static void	plus(const char *addr, int *ret, t_printf_opt_flag_info *ofi)
{
	int		res;
	int		fill_len;
	int		addr_len;
	int		sl;

	sl = opt_len (addr, ofi);
	res = 0;
	addr_len = __ft_printf_strlen (addr) + sl * (*addr != '-');
	fill_len = addr_len;
	if (!ofi->dot_flag && ofi->zero_opt && addr_len < ofi->width)
		fill_len = ofi->width;
	if (ofi->dot_flag && addr_len - sl * (*addr != '-') <= ofi->precision)
		fill_len = ofi->precision + sl;
	if (fill_len < ofi->width)
		res = __ft_printf_loop_character (' ', ofi->width - fill_len);
	*ret += res;
	if (res != -1 && opt (addr, ret, ofi) != -1 && addr_len < fill_len)
	{
		res = __ft_printf_loop_character ('0', fill_len - addr_len);
		*ret += res;
	}
	if (res != -1)
		res = write (1, addr + (*addr == '-'), addr_len - sl);
	*ret = -(res == -1) + (res != -1) * ((*ret) + res);
}

static void	minus(const char *addr, int *ret, t_printf_opt_flag_info *ofi)
{
	int		res;
	int		fill_len;
	int		addr_len;
	int		sl;

	sl = opt (addr, ret, ofi);
	addr_len = __ft_printf_strlen (addr) + sl * (*addr != '-');
	res = 0;
	fill_len = addr_len;
	if (ofi->zero_opt && addr_len - sl < ofi->width - sl)
		fill_len = ofi->width;
	if (ofi->dot_flag && addr_len - sl * (*addr != '-') <= ofi->precision)
		fill_len = ofi->precision + sl;
	if (res != -1 && addr_len < fill_len)
		res = __ft_printf_loop_character ('0', fill_len - addr_len);
	*ret += res;
	if (res != -1)
		res = write (1, addr + (*addr == '-'), addr_len - sl);
	*ret += res;
	if (res != -1 && fill_len < ofi->width)
	{
		res = __ft_printf_loop_character (' ', ofi->width - fill_len);
		*ret += res;
	}
	*ret = -(res == -1) + (res != -1) * (*ret);
}
