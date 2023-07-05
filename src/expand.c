#include "../minishell.h"

char	**handle_dollar(char *str)
{
	int	i;
	int	y;
	char	*s;
	char	**tab;
	
	while (str[i])
	{
		if (str[i] == 39)
		{
			while (str[++i] != 39)
				;
		}
		if (str[i] == '$')
			y = 0; //recupere la taille de la chaine variable et on soustrait $var
		i++;
	}
	s = malloc(sizeof(char) * );
	//on copie str dans s en fusionent les chaines;
	
}


char	**handle_arg(char **arg, t_list *var_env, int size, int nbd)
{
	int	i;
	int	y;
	t_list	*tmp;
	t_list	*new;
	char	**new_arg;
	
	i = 0;
	
	while (arg[i])
	{
		y = 0;
		if (dollar_check(arg[i]))
		{
			new_arg = handle_dollar(arg[i]);
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
		t = -1
		c = 0;
		while (data->cmds->str[++t])
			c += dollar_check(str[t]) // renvoie le nombre de $ hors ""

		data->cmds->str = handle_arg(data->cmds->str, data->var_env, t, c);

		handle_redirection(&data->cmds->redirections);

		handle_var(data->cmds->str, i); // atention a export

		data->cmds = data->cmds->next;	
	}
}*/
