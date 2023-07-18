/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:45:38 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/18 18:52:46 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *dvar, t_list *env, t_list *var_env)
{
	char	*str;
	char	*s;
	int		t;
	
	// reverifier les tailles
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
	while (env)
	{
		s = (char *)env->content;
		if (!ft_strncmp(s, dvar, t) && s[t] == '=')
		{
			str = malloc(sizeof(char) * ft_strlen(&s[t]));
			if (!str)
				return (NULL);
			ft_strlcpy(str, &s[t + 1], ft_strlen(&s[t]));
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
	if (str[i] == ' ' || str[i] == 0)
		return (i);
	while (str[i] && str[i] != 34 && str[i] != 39  && str[i] != '$' && str[i] != ' ')
		i++;
	*index = *index + i - 1;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (0);
	ft_strlcpy(var, &str[1], i);
	content = get_var(var, data.env, data.var_env);
	if (!content)
		return (free(var), (i * -1));
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
	char	*s;
	
	i = -1;
	y = 0;
	while (str[++i])
	{
		if (str[i] == 39) // sigle quote
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
		{
			i += ft_copy_var(&str[i], &s, &y, &data); //recupere la taille de la chaine variable et on soustrait $var
			/*while (str[i] != 39 && str[i] != 34 && str[i] != '$' && str[i])
				i++;*/
		}		
		if ((str[i] && str[i] != 39 && str[i] != 34 && str[i] != '$') ||\
		 (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == 0)))
			s[y++] = str[i++];
	}
	s[y] = 0;
	printf("i = %d\n", i);
	return (divide(&s, data.flag));
}


char	**handle_arg(char **arg, t_tool data)
{
	int	i;
	int	y;
	t_list	*tmp;
	t_list	*new;
	char	**new_arg;
	
	i = 0;
	// simplifier cette fonction en apelant juste dollar_check;
	tmp = NULL;
	while (arg[i])
	{
		y = 0;
		new_arg = handle_dollar(arg[i], data);
		while (new_arg[y])
		{
			printf("new_arg[%d] > %s\n", y, new_arg[y]);
			new = ft_lstnew(new_arg[y++]);
			if (!new)
				return (ft_lstclear(&tmp, free), NULL);
			ft_lstadd_back(&tmp, new);
		}
		free(new_arg);
		i++;
	}
	new_arg = lst_to_tab(tmp);
	ft_lstclear(&tmp, NULL);
	return (new_arg);
}

void	expand(t_tool *data)
{
	int	i;
	
	i = 0;
	while (data->cmds)
	{
		if (data->cmds->next)
			i++;

		data->cmds->str = handle_arg(data->cmds->str, *data);
		printf("expand > str %s\n", data->cmds->str[0]);
		printf("expand > str %s\n", data->cmds->str[1]);
	
		//handle_redirection(&data->cmds->redirection);

		//handle_var(data->cmds->str, i); // atention a export
		// atention a l ordre
		data->cmds = data->cmds->next;	
	}
	print_cmd(data->cmds);
}
