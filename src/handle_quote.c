/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:42:25 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/17 20:33:01 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_singlequote(char *str, char **s, int *y)
{
	int i;
	char	*l;

	l = *s;
	i = 1;
	while (str[i] != 39)
	{
		l[*y] = str[i];
		*y = *y + 1;
	}
	*s = l;
	return (i);
}

int	copy_var(char *str, char **s, int *index, t_tool data)
{
	int		i;
	int		y;
	int		t;
	char	*var;
	char	*content;

	i = 1;
	
	while (str[i] && str[i] != 34 && str[i] != 39  && str[i] != '$')
		i++;
	*index = *index + i;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data.env, data.var_env);
	if (!content)
		return (free(var), 0);
	t = ft_strlen(content);
	y = -1;
	while (y++ < t)
		*s[y] = content[y];
	return (free(var), free(content), y);
}

int	handle_doublequote(char *str, char **s, int *y, t_tool data)
{
	int	i;
	
	i = 1;
	while (str[i] != 34)
	{
		if (str[i] == '$')
			*y = *y + copy_var(&str[i], &s[*y], &i, data);
		if (str[i] != 34 && str[i] != '$')
		{
			*s[*y] = str[i];
			*y = *y + 1;
		} 
	}
	return (i);
}

int	ft_copy_var(char *str, char **s, int *y, t_tool *data)
{
	int		i;
	int		t;
	int		x;
	char	*var;
	char	*content;

	i = 1;
	while (str[i] && str[i] != 34 && str[i] != 39  && str[i] != '$')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (i + 1);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data->env, data->var_env);
	if (!content)
		return (free(var), i + 1);
	t = ft_strlen(content);
	x = 0;
	while (x < t)
	{
		s[0][*y] = content[x++];
		if (data->flag == 0 && s[0][*y] == ' ')
			data->flag = *y;
		*y = *y + 1;
	}
	return (i);
}

char	**divide(char **s, int flag)
{
	char	**tab;
	char	*l1;
	char	*l2;
	int		t;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (free(*s), NULL);
	if (!flag)
		return (tab[0] = *s, tab[1] = NULL, tab);
	t = ft_strlen(*s);
	l1 = malloc(sizeof(char) * flag + 1);
	if (!l1)
		return (free(tab), free(*s), NULL);
	l2 = malloc(sizeof(char) * (t - flag + 1));
	if (!l2)
		return (free(tab), free(*s), free(l1), NULL);
	ft_strlcpy(l1, *s, flag);
	ft_strlcpy(l2, &*s[flag], t - flag);
	return (tab);
}