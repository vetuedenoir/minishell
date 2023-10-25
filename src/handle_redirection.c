/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:59:11 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 13:59:54 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dl(char	*str, t_tool *data)
{
	int		i;
	int		y;
	char	*s;

	s = resize_arg(str, data);
	if (!s)
		return (NULL);
	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == 39)
			i += handle_singlequote(&str[i], &s, &y);
		if (str[i] == 34)
			i += handle_doublequote(&str[i], &s, &y, *data);
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != 0)
			i += ft_copy_var(&str[i], &s, &y, data);
		if ((str[i] && str[i] != 39 && str[i] != 34 && str[i] != '$') || \
			(str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == 0)))
			s[y++] = str[i++];
	}
	s[y] = 0;
	return (s);
}

t_lexer	*handle_redirection(t_lexer *redirection, t_tool *data)
{
	char		*new;
	t_lexer		*lst;
	int			i;

	i = 1;
	lst = redirection;
	while (redirection)
	{
		if (i % 2 == 0)
		{
			new = handle_dl(redirection->str, data);
			if (!new)
				return (NULL);
			redirection->str = new;
		}
		redirection = redirection->next;
		i++;
	}
	return (lst);
}

int	expand_token(char c, bool flag)
{
	if (flag && c == '?')
		return (1);
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}
