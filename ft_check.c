/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:49:47 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/20 18:45:10 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprint.h"

size_t			ft_checkflag1(const char *format, size_t *i)
{
	size_t option;

	option = 0;
	if (format[*i + 1] == '0' | format[*i + 1] == '-')
	{
		option = (format[*i + 1] == '-' ? 1 : 2);
		*i = *i + 1;
		if (format[*i + 1] == '0' | format[*i + 1] == '-')
		{
			option = 1;
			*i = *i + 1;
		}
	}
	return (option);
}

size_t			ft_checktaille_min(va_list ap, const char *format, size_t *i)
{
	size_t	var1;
	size_t	j;
	int		t;

	if (format[*i + 1] == '*')
	{
		t = va_arg(ap, int);
		var1 = (size_t)t;
		var1 = t < 0 ? (size_t)(-t) : (size_t)(t); 
		if (t < 0)
			i[4] = 1;
		*i = *i + 1;
		return (var1);
	}
	else if (ft_isdigit(format[*i + 1]))
	{
		j = *i;
		while (ft_isdigit(format[*i + 1]))
			*i = *i + 1;
		return (ft_atoi(&format[j + 1]));
	}
	return (0);
}

size_t			ft_checktaille_max(va_list ap, const char *format, size_t *i)
{
	size_t taille_max;
	size_t	j;
	int		t;

	taille_max = -1;
	if (format[*i + 1] == '.')
	{
		*i = *i + 1;
		if (format[*i + 1] == '*')
		{
			t = va_arg(ap, int);
			taille_max = t < 0 ? (size_t)(-1) : (size_t)(t); 
			*i = *i + 1;
			return (taille_max);
		}
		else if (ft_isdigit(format[*i + 1]))
		{
			j = *i;
			while (ft_isdigit(format[*i + 1]))
				*i = *i + 1;
			return (ft_atoi(&format[j + 1]));
		}
		return (0);
	}
	return (taille_max);
}
