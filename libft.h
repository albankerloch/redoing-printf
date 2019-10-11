/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:49:01 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/11 16:26:35 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
#include <stdarg.h>

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_printf(const char *format, ...);
void    			ft_putstr(char *s);
char			   	*ft_strchr(const char *str, int c);

#endif