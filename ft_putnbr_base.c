/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 08:49:04 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/16 16:39:21 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprint.h"

size_t			ft_max(size_t n1, size_t n2)
{
	size_t m;

	m = -1;
	if (n1 == m)
		return (n2);
	if (n2 == m)
		return (n1);
	if (n1 > n2)
		return (n1);
	return (n2);
}

size_t			ft_count_yc_signe(long nbr, char *base)
{
	if (nbr < 0)
		return (ft_count_hors_signe(nbr, base) + 1);
	return (ft_count_hors_signe(nbr, base));
}

size_t			ft_count_hors_signe(long nbr, char *base)
{
	size_t		j;
	size_t		t;

	j = 1;
	t = nbr;
	if (nbr < 0)
	{
		t = -t;
	}
	while (t > ft_strlen(base))
	{
		t = t / ft_strlen(base);
		j++;
	}
	return (j);
}

static void		ft_wbase(long n, char *base, char *s, size_t *t)
{
	long c;
	long d;
	char e;
	int b;

	b = ft_strlen(base);
	if (n >= b)
	{
		c = n / b;
		d = n % b;
		ft_wbase(c, base, s, t);
		e = base[d];
		s[t[1]] = e;
		t[1] = t[1] + 1;
	}
	else
	{
		e = base[n];
		s[t[1]] = e;
		t[1] = t[1] + 1;
	}
}

void			ft_putnbr_base(char *s, long nbr, char *base, size_t *t)
{
	long long	l;
	size_t		sign;

	l = nbr;
	sign = nbr < 0 ? 1 : 0;
//	printf("\noption : %zu    min : %zu    max : %zu\n", t[4], t[2], t[3]);
	if (t[2] > ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)) && t[4] == 0)
		ft_fill_caract(s, t[2] - ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)), t, ' ');
	if (t[2] > ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)) && t[4] == 2 && t[3] != (size_t)-1)
		ft_fill_caract(s, t[2] - ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)), t, ' ');
	if (nbr < 0)
	{
		l = -l;
		s[t[1]] = '-';
		t[1] = t[1] + 1;
	}
	if (t[2] > ft_count_yc_signe(nbr, base) && t[4] == 2 && t[3] == (size_t)-1)
		ft_fill_caract(s, t[2] - ft_count_yc_signe(nbr, base), t, '0');
	if (ft_max(t[3], 0) > ft_count_hors_signe(nbr, base))
		ft_fill_caract(s, t[3] - ft_count_hors_signe(nbr, base), t, '0');
	if (!(nbr == 0 && t[3] == 0))
		ft_wbase(l, base, s, t);
	else
	{
		if (t[2] > 0)
		{
			s[t[1]] = ' ';
			t[1] = t[1] + 1;
		}
	}
	if (t[2] > ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)) && t[4] == 1)
		ft_fill_caract(s, t[2] - ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)), t, ' ');
}

void			ft_countnbr_base(long nbr, char *base, size_t *t)
{
	size_t 		sign;

	sign = nbr < 0 ? 1 : 0;
	if (t[2] > ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)) && t[4] == 0)
		t[1] = t[1] + t[2] - ft_max(t[3] + sign, ft_count_yc_signe(nbr, base));
	if (t[2] > ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)) && t[4] == 2 && t[3] != (size_t)-1)
		t[1] = t[1] + t[2] - ft_max(t[3] + sign, ft_count_yc_signe(nbr, base));
	if (nbr < 0)
		t[1] = t[1] + 1;
	if (t[2] > ft_count_yc_signe(nbr, base) && t[4] == 2 && t[3] == (size_t)-1)
		t[1] = t[1] + t[2] - ft_count_yc_signe(nbr, base);
	if (ft_max(t[3], 0) > ft_count_hors_signe(nbr, base))
		t[1] = t[1] + t[3] - ft_count_hors_signe(nbr, base);
	t[1] = t[1] + ft_count_yc_signe(nbr, base);
	if (t[2] > ft_max(t[3] + sign, ft_count_yc_signe(nbr, base)) && t[4] == 1)
		t[1] = t[1] + t[2] - ft_max(t[3] + sign, ft_count_yc_signe(nbr, base));
}
