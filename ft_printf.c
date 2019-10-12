/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:31:17 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/12 17:01:06 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_printf(const char *format, ...)
{
    char *s;
    char *var1;
	size_t i;
	size_t k;
	size_t t;
	size_t len;
	size_t	j;
	va_list ap;

	i = 0;
	t = 0;
	while ( i < ft_strlen(format))
	{
		if (format[i] == '%')
			t++;
		i++;
	}

	va_start(ap, format);
	printf("\n -%zu- \n", t);
	i = 0;
	len = 0;
	while ( i < t)
	{
		var1 = va_arg(ap, char*);
		len = len + ft_strlen(var1);
		i++;
	}
	va_end(ap);
	printf("\n --%zu-- \n", len);

    s = NULL;
    if (!(s = (char*)malloc(ft_strlen(format) + len + 1)))
        return (0);
	j = 0;
	i = 0;
	va_start(ap, format);
	while (j < ft_strlen(format) + ft_strlen(var1))
	{
		if (format[i] != '%')
		{
			s[j] = format[i];
			i++;
			j++;
		}
		else
		{
			var1 = va_arg(ap, char*);
			printf("\n -%s- %zu %zu %zu\n", var1, j, i, j - i);
			k = 0;
			while (k < ft_strlen(var1))
			{
				s[j] = var1[k];
				j++;
				k++;
			}
			i++;
		}
	}
	s[j] = '\0';
	va_end(ap);
	ft_putstr(s);
	return (0);
}
