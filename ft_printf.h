/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:41:29 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/05 17:37:30 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

typedef struct s_printf_opt_flag_info
{
	int				width;
	int				precision;
	char			dot_flag;
	char			minus_opt;
	char			zero_opt;
	char			sharp_flag;
	char			space_flag;
	char			plus_flag;
	char			numeric_flag;
	const char		*(*fp)(const char *frm, void *val, int *ret,
			struct s_printf_opt_flag_info *ofi);
}	t_printf_opt_flag_info;

int			ft_printf(const char *format, ...);

const char	*__ft_printf_c(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_s(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_p(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_d(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_i(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_u(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_sx(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_lx(const char *frm, void *val, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_characters(const char *frm, int *ret,
				t_printf_opt_flag_info *ofi);

const char	*__ft_printf_info(const char *frm, t_printf_opt_flag_info *ofi);

int			__ft_printf_loop_character(const char chr, unsigned int count);

size_t		__ft_printf_strlen(const char *s);

void		__ft_printf_set_fps(
				const char *(**fps)(const char *frm, void *val, int *ret,
					t_printf_opt_flag_info *ofi));

void		__ft_printf_write_numeric(char *addr, int *ret,
				t_printf_opt_flag_info *ofi);

#endif // FT_PRINTF_H
