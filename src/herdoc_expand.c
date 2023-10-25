/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:09:40 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 20:04:24 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_expand(char *str, t_tool *data)
{
	int		i;
	int		y;
	char	*s;

	i = -1;
	y = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			y += ft_dollarsize(&str[i], &i, *data);
	}
	s = ft_malloc(sizeof(char) * (y + i + 1), data);
	if (!s)
		return (perror("minishell: malloc"), NULL);
	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != 0)
			i += ft_copy_var(&str[i], &s, &y, data);
		if ((str[i] && str[i] != 39 && str[i] != 34 && str[i] != '$') || \
			(str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == 0)))
			s[y++] = str[i++];
	}
	return (s[y] = 0, s);
}
