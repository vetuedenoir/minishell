/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:45:38 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/05 20:01:57 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *dvar, t_list *env, t_list *var_env)
{
	char	*str;
	int		t;
	
	// reverifier les tailles
	t = ft_strlen(dvar);
	while (var_env)
	{
		if (ft_strncmp(var_env->content, dvar, t) && var_env->content[t] == '=')
		{
			str = malloc(sizeof(char) * ft_strlen(&var_env->content[t]))
			if (!str)
				return (NULL);
			ft_strlcpy(str, &var_env->content[t + 1], ft_strlen(&var_env->content[t]));
			return (str);
		}
		var_env = var_env->next;
	}
	while (env)
	{
		if (ft_strncmp(env->content, dvar, t) && env->content[t] == '=')
		{
			str = malloc(sizeof(char) * ft_strlen(&env->content[t]))
			if (!str)
				return (NULL);
			ft_strlcpy(str, &env->content[t + 1], ft_strlen(&env->content[t]));
			return (str);
		}
		env = env->next;
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
	*index = *index + 1;
	while (str[i] && str[i] != 34 && str[i] != 39  && str[i] != '$')
	{
		i++;
		*index = *index + 1;
	}
	*index = *index - 1;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	ft_strlcpy(var, &str[1], i - 1);
	content = get_var(var, data->env, data->var_env)
	if (!content)
		return (free(var), (i * -1))
	size = ft_strlen(content);
	// reverifier le calcule
	size -= i;
	free(content);
	free(var);
	return (size);
}


char	**handle_dollar(char *str, t_tool data)
{
	int	i;
	int	y;
	int f;
	char	*s;
	char	**tab;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == 39)
		{
			while (str[++i] != 39)
				;
			y -= 2;
		}
		else if (str[i] == '$')
			y += ft_dollarsize(&str[i], &i, data); //recupere la taille de la chaine variable et on soustrait $var
	}
	s = malloc(sizeof(char) * (y + i + 1));
	if (!s)
		return (NULL);
	i = -1;
	y = 0;
	f = 0;
	while (str[++i])
	{
		if (str[i] == 39)
			handle_singlequote(&str[i], &s[y]);
		if (str[i] == 34)
			handle_doublequote(&str[i], &s[y], data)
		if (str[i] == '$')
		{
			y += ft_copy_var(&str[i], &s[y], &f, data); //recupere la taille de la chaine variable et on soustrait $var
			while (str[i] != 39 && str[i] != 34 && str[i] != '$' && str[i])
				i++;
		}		
		if (str[i] != 39 && str[i] != 34 && str[i] != '$')
			s[y++] = str[i++];
		y++;
	}
	if (f)
		tab = divide(s, f);
	else
	{
		tab = malloc(sizeof(char *) * 2);
		tab[0] = s;
		tab[1] = NULL;
	}
	return (tab);
}


char	**handle_arg(char **arg, t_tool data, int size, int nbd)
{
	int	i;
	int	y;
	t_list	*tmp;
	t_list	*new;
	char	**new_arg;
	
	i = 0;
	// simplifier cette fonction en apelant juste dollar_check;
	while (arg[i])
	{
		y = 0;
		if (dollar_check(arg[i]))
		{
			new_arg = handle_dollar(arg[i], data);
			while (new_arg[y])
			{
				new = ft_lstnew(new_arg[y++]);
				if (!new)
					return (ft_lstfree(tmp), NULL);
				ft_lstadd_back(&tmp, new);
			}
			cleartb(new_arg);
		}
		else if (ft_strchr(arg[i], 39) || ft_strchr(arg[i], 34))
		{
			new = ft_lstnew(handle_quote(arg[i]));
			if (!new)
				return (ft_lstfree(tmp), NULL);
			ft_lstadd_back(&tmp, new);
		}
		else
		{
			new = ft_lstnew(arg[i]);
			if (!new)
				return (ft_lstfree(tmp), NULL);
			ft_lstadd_back(&tmp, new);
		}
		i++;
	}
	new_arg = lst_to_tab(tmp);
	ft_lstclear(&tmp, free);
	return (new_arg);
}

void	expand(t_tool *data)
{
	int	i;
	int	t;
	int	c;
	
	i = 0;
	while (data->cmds)
	{
		if (data->cmds->next)
			i++;
		t = -1;
		c = 0;
		while (data->cmds->str[++t])
			c += dollar_check(str[t]) // renvoie le nombre de $ hors ""

		data->cmds->str = handle_arg(data->cmds->str, *data, t, c);

		handle_redirection(&data->cmds->redirections);

		handle_var(data->cmds->str, i); // atention a export

		data->cmds = data->cmds->next;	
	}
}*/
