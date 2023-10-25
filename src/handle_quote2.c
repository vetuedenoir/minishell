/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:03:40 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 16:03:42 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_singlequote(char *str, char **s, int *y)
{
	int		i;
	char	*l;

	l = *s;
	i = 1;
	while (str[i] != 39)
	{
		l[*y] = str[i];
		*y = *y + 1;
		i++;
	}
	*s = l;
	return (i + 1);
}

int	handle_doublequote(char *str, char **s, int *y, t_tool data)
{
	int		i;

	i = 0;
	while (str[++i] && str[i] != 34)
	{		
		if (str[i] == '$' && str[i + 1] != 0 && str[i + 1] != 34)
		{
			i += zi(&str[i], s, y, data);
			if (str[i] == 34)
				return (i + 1);
		}
		if ((str[i] != 34 && str[i] != '$') || \
			(str[i] == '$' && (expand_token(str[i + 1], 1) || \
			str[i] == 0 || str[i + 1] == 34)))
		{
			s[0][*y] = str[i];
			*y = *y + 1;
		}
	}
	return (i + 1);
}
