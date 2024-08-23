/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:48:31 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 15:51:23 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void			__ofi_init(t_printf_opt_flag_info *ofi);

static const char	*__set_flag(const char *frmp,
						t_printf_opt_flag_info *ofi);

static const char	*__set_width(const char *frmp,
						t_printf_opt_flag_info *ofi);

static const char	*__set_precision(const char *frmp,
						t_printf_opt_flag_info *ofi);

const char	*__ft_printf_info(const char *frm, t_printf_opt_flag_info *ofi)
{
	const char	*frmp;

	frmp = frm + 1;
	__ofi_init (ofi);
	frmp = __set_flag (frmp, ofi);
	frmp = __set_width (frmp, ofi);
	frmp = __set_precision (frmp, ofi);
	if (!*frmp)
		return (frmp);
	return (frmp);
}

void	__ofi_init(t_printf_opt_flag_info *ofi)
{
	char	*data;
	size_t	size;

	data = (char *)ofi;
	size = sizeof (t_printf_opt_flag_info);
	while (size--)
		data[size] = 0x00;
}

const char	*__set_flag(const char *frmp, t_printf_opt_flag_info *ofi)
{
	while (*frmp == '+' || *frmp == '-' || *frmp == '#'
		|| *frmp == ' ' || *frmp == '0')
	{
		if (*frmp == '+')
			ofi->plus_flag = 1;
		if (*frmp == '-')
			ofi->minus_opt = 1;
		if (*frmp == '#')
			ofi->sharp_flag = 1;
		if (*frmp == ' ')
			ofi->space_flag = 1;
		if (*frmp == '0')
			ofi->zero_opt = 1;
		frmp++;
	}
	return (frmp);
}

const char	*__set_width(const char *frmp, t_printf_opt_flag_info *ofi)
{
	while ('0' <= *frmp && *frmp <= '9')
	{
		ofi->width += *frmp - 0x30;
		if ('0' <= *(++frmp) && *frmp <= '9')
			ofi->width *= 10;
	}
	return (frmp);
}

const char	*__set_precision(const char *frmp, t_printf_opt_flag_info *ofi)
{
	if (*frmp != '.')
		return (frmp);
	ofi->dot_flag = 1;
	frmp++;
	while ('0' <= *frmp && *frmp <= '9')
	{
		ofi->precision += *frmp - 0x30;
		if ('0' <= *(++frmp) && *frmp <= '9')
			ofi->precision *= 10;
	}
	return (frmp);
}
