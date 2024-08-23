/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:10:50 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 18:48:14 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf2(const char *format, va_list args, void *arg);

int	ft_printf(const char *format, ...)
{
	va_list		args;
	void		*arg;
	int			ret;

	arg = (void *)format;
	va_start (args, format);
	ret = ft_printf2(format, args, arg);
	va_end (args);
	return (ret);
}

int	ft_printf2(const char *format, va_list args, void *arg)
{
	int						ret;
	const char				*(*fps[9])(const char *frm, void *val, int *ret,
			t_printf_opt_flag_info *ofi);
	const char				*(**fp)(const char *frm, void *val, int *ret,
			t_printf_opt_flag_info *ofi);
	const char				*fp_res;
	t_printf_opt_flag_info	ofi;

	ret = 0;
	__ft_printf_set_fps(fps);
	while (*format && ret != -1)
	{
		format = __ft_printf_characters (format, &ret, &ofi);
		if (!format || !*format || ret == -1)
			break ;
		fp = fps;
		fp_res = format;
		arg = va_arg (args, void *);
		while (*fp && fp_res == format)
			fp_res = (*(fp++))(format, arg, &ret, &ofi);
		format = fp_res;
	}
	return (ret);
}
