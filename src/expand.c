/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:45:38 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/22 13:09:12 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *dvar, t_list *var_env)
{
	char	*str;
	char	*s;
	int		t;

	t = ft_strlen(dvar);
	while (var_env)
	{
		s = (char *)var_env->content;
		if (!ft_strncmp(s, dvar, t) && s[t] == '=')
		{
			str = malloc(sizeof(char) * ft_strlen(&s[t]));
			if (!str)
				return (NULL);
			ft_strlcpy(str, &s[t + 1], ft_strlen(&s[t]));
			return (str);
		}
		var_env = var_env->next;
	}
	return (NULL);
}

int	ft_dollarsize(char *str, int *index, t_tool data)
{
	int		i;
	int		size;
	char	*var;
	char	*content;

	i = 1;
	if (!expand_token(str[i]) || str[i] == 0)
		return (i);
	while (expand_token(str[i]))
		i++;
	*index = *index + i - 1;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data.var_env);
	if (!content)
		return (free(var), (i * -1));
	size = ft_strlen(content);
	size -= i;
	free(content);
	free(var);
	return (size);
}

char	*resize_arg(char *str, t_tool data)
{
	int		i;
	int		y;
	char	*s;

	i = -1;
	y = 0;
	while (str[++i])
	{
		if (str[i] == 39) // single quote
		{
			while (str[++i] != 39)
				;
			y -= 2;
		}
		else if (str[i] == '$')
			y += ft_dollarsize(&str[i], &i, data);//recupere la taille de la chaine variable et on soustrait $var
	}
	s = ft_malloc(sizeof(char) * (y + i + 1));
	return (s);
}

char	**handle_dollar(char *str, t_tool data)
{
	int		i;
	int		y;
	char	*s;

	s = resize_arg(str, data);
	if (!s)
		return (NULL);
	i = 0;
	y = 0;
	data.flag = 0;
	while (str[i])
	{
		if (str[i] == 39)
			i += handle_singlequote(&str[i], &s, &y);
		if (str[i] == 34)
			i += handle_doublequote(&str[i], &s, &y, data);
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != 0)
			i += ft_copy_var(&str[i], &s, &y, &data);
		if ((str[i] && str[i] != 39 && str[i] != 34 && str[i] != '$') || \
			(str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == 0)))
			s[y++] = str[i++];
	}
	s[y] = 0;
	return (divide(&s, data.flag));
}

char	**handle_arg(char **arg, t_tool data)
{
	int		i;
	int		y;
	t_list	*tmp;
	t_list	*new;
	char	**new_arg;

	i = 0;
	tmp = NULL;
	while (arg[i])
	{
		y = 0;
		new_arg = handle_dollar(arg[i], data);
		while (new_arg[y])
		{
			new = ft_lstnew(new_arg[y++]);
			if (!new)
				return (ft_lstclear(&tmp, NULL), NULL);
			ft_lstadd_back(&tmp, new);
		}
		i++;
	}
	new_arg = lst_to_tab(tmp);
	ft_lstclear(&tmp, NULL);
	return (new_arg);
}

void	expand(t_tool *data)
{
	t_cmds	*tmp;

	tmp = data->cmds;
	while (data->cmds)
	{
		if (data->cmds->str)
			data->cmds->str = handle_arg(data->cmds->str, *data);
		if (data->cmds->redirection)
			data->cmds->redirection = \
			handle_redirection(data->cmds->redirection, *data);
		data->cmds = data->cmds->next;
	}
	data->cmds = tmp;
}
