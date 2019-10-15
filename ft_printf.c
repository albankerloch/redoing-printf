/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:31:17 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/15 12:20:33 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t ft_count(const char *format)
{
	size_t i;
	size_t t;

	i = 0;
	t = 0;
	while ( i < ft_strlen(format))
	{
		if (format[i] == '%')
		{
			if (format[i + 1] != '%')
				t++;
			else
				i++;
		}
		i++;
	}
//	printf("\n --%zu-- \n", t);
	return (t);
}
/*
static size_t ft_size(va_list ap, const char *format, size_t t)
{
	size_t len;
	size_t i;
    char *var1;

	len = 0;
	i = 0;
	while (i < t)
	{
		(void)format;
		var1 = va_arg(ap, char*);
		len = len + ft_strlen(var1);
		i++;
	}
//	printf("\n --%zu-- \n", len);
	return (len);
}
*/
static size_t ft_checkflag1(const char *format, size_t *i)
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

static size_t ft_checktaille_min(va_list ap, const char *format, size_t *i)
{
    size_t var1;
	size_t j;

	if (format[*i + 1] == '*')
	{
		var1 = (size_t)va_arg(ap, int);
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

static size_t ft_checktaille_max(va_list ap, const char *format, size_t *i)
{
	size_t taille_max;

	taille_max = -1;
	if (format[*i + 1] == '.')
	{
		*i = *i + 1;
        taille_max = ft_checktaille_min(ap, format, i);
    }
    return (taille_max);
}

static void ft_write_s(char *s, va_list ap, size_t *t)
{
    char *var1;
	size_t k;
	size_t m;

	var1 = va_arg(ap, char*);
	k = 0;
	m = t[3] < ft_strlen(var1) ? t[3] : ft_strlen(var1);
	printf("\n -%s- %zu %zu %zu %zu\n", var1, t[4], t[2], t[3], t[2] - m);
	if (t[2] > m && t[4] != 1)
	{
		while (k < t[2] - m)
		{
			k++;
			s[t[1]] = (t[4] == 2 ? '0' : ' ');
			t[1]++;
		}
	}
	k = 0;
	while (k < ft_strlen(var1) && k < t[3])
	{
		s[t[1]] = var1[k];
		t[1]++;
		k++;
	}
	k = 0;
	if (t[2] > m && t[4] == 1)
	{
		while (k < t[2] - m)
		{
			k++;
			s[t[1]] = ' ';
			t[1]++;
		}
	}
}

static void ft_write_c(char *s, va_list ap, size_t *t)
{
    char var1;
	size_t k;

	var1 = (char)va_arg(ap, int);
	k = 1;
	if (t[2] > 0 && t[4] != 1)
	{
		while (k < t[2])
		{
			k++;
			s[t[1]] = (t[4] == 2 ? '0' : ' ');
			t[1]++;
		}
	}
	s[t[1]] = var1;
	t[1]++;
	if (t[2] > 0 && t[4] == 1)
    {
		while (k < t[2])
		{
			k++;
			s[t[1]] = ' ';
			t[1]++;
		}
	}
}


static void ft_write_p(char *s, va_list ap, size_t *t)
{
   void *var1;

	var1 = va_arg(ap, void*);
//	printf("\n -%p- %ld %zu %zu\n", var1, (long)var1, t[1], t[0]);
	s[t[1]] = '0';
	s[t[1] + 1] = 'x';
	t[1] = t[1] + 1;
	ft_putnbr_base(s, (long)var1, "0123456789abcdef", t);
}

static void ft_write_d(char *s, va_list ap, size_t *t, char conv)
{
	int var1;

	var1 = va_arg(ap, int);
//	printf("\n %d %zu %zu %zu %zu \n", var1, t[1], t[0], ft_count_yc_signe(var1, "0123456789"), ft_count_hors_signe(var1, "0123456789"));
//	printf("\n -%s- %zu %zu\n", var1, t[1], t[0]);
	if (conv == 'i' || conv == 'd' || conv == 'u')
		ft_putnbr_base(s, var1, "0123456789", t);
	if (conv == 'x')
		ft_putnbr_base(s, var1, "0123456789abcdef", t);
	if (conv == 'X')
		ft_putnbr_base(s, var1, "0123456789ABCDEF", t);
}

static void ft_parsing(char *s, va_list ap, const char *format, size_t *t)
{
	char conv;

	t[4] = ft_checkflag1(format, t);
//	printf("\n %c %zu\n", option, i);
	t[2] = ft_checktaille_min(ap, format, t);
//	printf("\n %zu | %zu\n", t[2], t[0]);
	t[3] = ft_checktaille_max(ap, format, t);
//	printf("\n %zu | %zu\n", t[3], t[0]);
	conv = format[t[0] + 1];
//	printf("\n %c %c %zu  %zu\n", option, conv, t[0], t[1]);
	t[0] = t[0] + 2;
	if (conv == 's')
		ft_write_s(s, ap, t);
	else if (conv == 'c')
		ft_write_c(s, ap, t);
	else if (conv == 'p')
		ft_write_p(s, ap, t);
	else
		ft_write_d(s, ap, t, conv);
}

static void ft_fill(char *s, va_list ap, const char *format)
{
	size_t t[4];

	t[0] = 0;
	t[1] = 0;
	while (t[0] < ft_strlen(format))
	{
		if (format[t[0]] != '%')
		{
			s[t[1]] = format[t[0]];
			t[0]++;
			t[1]++;
		}
		else
		{
			if (format[t[0] + 1] == '%')
			{
				s[t[1]] = '%';
				t[1]++;
				t[0] = t[0] + 2;
			}
			else
			{
				ft_parsing(s, ap, format, t);

			}
		}
	}
	s[t[1]] = '\0';
}

int ft_printf(const char *format, ...)
{
    char *s;
	size_t t;
	size_t len;
	va_list ap;

	t = ft_count(format);
	if (t != 0)
	{
		va_start(ap, format);
		//len = ft_size(ap, format, t);
		len = 1000;
		va_end(ap);
	}
	else
		len = -1;
    s = NULL;
    if (!(s = (char*)malloc(ft_strlen(format) + len + 1)))
        return (0);
	if (t != 0)
	{
		va_start(ap, format);
		ft_fill(s, ap, format);
		va_end(ap);
	}
	ft_putstr(s);
	free(s);
	return (0);
}
