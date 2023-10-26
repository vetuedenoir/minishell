/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:42:25 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/26 15:24:43 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_var(char *str, int *index, t_tool data)
{
	int		i;
	char	*var;
	char	*content;

	i = 1;
	while (str[i] && str[i] != 34 && str[i] != 39 && \
		str[i] != '$' && expand_token(str[i], 0))
		i++;
	if (str[i] == '?')
		i++;
	*index = *index + i;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data.var_env);
	return (free(var), content);
}

int	zi(char *str, char **s, int *y, t_tool data)
{
	int		i;
	int		x;
	char	*var;

	i = 0;
	if (ft_isdigit(str[1]) || !expand_token(str[1], 1))
		return (2);
	if (!expand_token(str[1], 0) || ft_isdigit(str[1]))
		return (2);
	var = return_var(&str[i], &i, data);
	if (!var)
		return (i);
	x = 0;
	while (var[x])
	{
		s[0][*y] = var[x++];
		*y = *y + 1;
	}
	free(var);
	return (i);
}

int	verif_var(char *str)
{
	int	i;

	if (ft_isdigit(str[1]))
		return (0);
	if (str[1] == 34 || str[1] == 39)
		return (-1);
	if (str[1] == '=' || str[1] == '+')
		return (-2);
	if (!expand_token(str[1], 1))
		return (0);
	i = 1;
	if (str[i] == '?')
		return (2);
	while (str[i] && expand_token(str[i], 0))
		i++;
	return (i);
}

int	ft_copy_var(char *str, char **s, int *y, t_tool *data)
{
	int		i;
	int		t;
	char	*var;
	char	*content;

	i = verif_var(str);
	if (i == 0 || i == -1 || i == -2)
		return (i + 2);
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (i);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data->var_env);
	if (!content)
		return (free(var), i);
	t = -1;
	while (content[++t])
	{
		s[0][*y] = content[t];
		if (data->flag == 0 && s[0][*y] == ' ')
			data->flag = *y;
		*y = *y + 1;
	}
	return (free(var), free(content), i);
}

char	**divide(char **s, int flag, t_tool *data)
{
	char	**tab;
	char	*l1;
	char	*l2;
	char	*str;
	int		t;

	str = *s;
	tab = ft_calloc_g(sizeof(char *), 3, data);
	if (!tab)
		return (NULL);
	if (!flag)
		return (tab[0] = *s, tab[1] = NULL, tab);
	t = ft_strlen(*s);
	l1 = ft_malloc(sizeof(char) * (flag + 1), data);
	if (!l1)
		return (NULL);
	l2 = ft_malloc(sizeof(char) * (t - flag + 1), data);
	if (!l2)
		return (NULL);
	ft_strlcpy(l1, *s, flag + 1);
	ft_strlcpy(l2, &str[flag + 1], t - flag + 2);
	tab[0] = l1;
	tab[1] = l2;
	return (tab[2] = NULL, tab);
}
