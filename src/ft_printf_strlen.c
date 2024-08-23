/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strlen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:20:24 by kofujita          #+#    #+#             */
/*   Updated: 2024/05/04 15:03:25 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	__ft_printf_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		ret++;
		s++;
	}
	return (ret);
}
