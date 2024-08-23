/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_fps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:19:50 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 13:40:28 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	__ft_printf_set_fps(
			const char *(**fps)(const char *frm, void *val, int *ret,
			t_printf_opt_flag_info *ofi))
{
	fps[0] = __ft_printf_c;
	fps[1] = __ft_printf_s;
	fps[2] = __ft_printf_p;
	fps[3] = __ft_printf_d;
	fps[4] = __ft_printf_i;
	fps[5] = __ft_printf_u;
	fps[6] = __ft_printf_sx;
	fps[7] = __ft_printf_lx;
	fps[8] = 0x00;
}
