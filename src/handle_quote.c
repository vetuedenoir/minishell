/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:42:25 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/22 16:25:38 by kscordel         ###   ########.fr       */
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
		i++;
	}
	*s = l;
	return (i + 1);
}

char	*return_var(char *str, int *index, t_tool data)
{
	int		i;
	char	*var;
	char	*content;

	i = 1;
	
	while (str[i] && str[i] != 34 && str[i] != 39  && str[i] != '$' && str[i] != ' ')
		i++;
	*index = *index + i;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data.var_env);
	return (free(var), content);
}

int	handle_doublequote(char *str, char **s, int *y, t_tool data)
{
	int		i;
	int		x;
	char	*var;

	i = 0;
	while (str[++i] && str[i] != 34)
	{
		if (str[i] == '$' && str[i + 1] != 0 && str[i + 1] != ' ')
		{	
			var = return_var(&str[i], &i, data);
			x = 0;
			if (!var)
				continue ;
			while (var[x])	
			{
				s[0][*y] = var[x++];
				*y = *y + 1;
			}
			free(var);
		if (str[i] == 34)
			return (i + 1);
		}
		if ((str[i] != 34 && str[i] != '$') ||\
		 (str[i] == '$' && (str[i + 1] == ' ' || str[i] == 0)))
		{
			s[0][*y] = str[i];
			*y = *y + 1;
		}
	}
	return (i + 1);
}

int	ft_copy_var(char *str, char **s, int *y, t_tool *data)
{
	int		i;
	int		t;
	char	*var;
	char	*content;

	i = 1;
	while (str[i] && str[i] != 34 && str[i] != 39  && str[i] != '$')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (i + 1);
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

char	**divide(char **s, int flag)
{
	char	**tab;
	char	*l1;
	char	*l2;
	char	*str;
	int		t;

	str = *s;
	tab = ft_calloc_g(sizeof(char *) , 3);
	if (!tab)
		return (NULL);
	if (!flag)
		return (tab[0] = *s, tab[1] = NULL, tab);
	t = ft_strlen(*s);
	l1 = ft_malloc(sizeof(char) * (flag + 1));
	if (!l1)
		return (free(tab), free(*s), NULL);
	l2 = ft_malloc(sizeof(char) * (t - flag + 1));
	if (!l2)
		return (free(tab), free(l1), NULL);
	ft_strlcpy(l1, *s, flag + 1);
	ft_strlcpy(l2, &str[flag], t - flag + 1);
	tab[0] = l1;
	tab[1] = l2;
	return (tab[2] = NULL, tab);
}
