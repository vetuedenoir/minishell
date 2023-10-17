#include "../minishell.h"

t_tool	*noenv(t_tool *data)
{
	char	*str;
	char	*pwd[2];
	
	pwd[0] = NULL;
	pwd[1] = NULL;
	str = NULL;
	str = getcwd(str, 0);
	pwd[0] = ft_strjoin("PWD=", str);
	free(str);
	export(pwd, &data->var_env, data, 0);
	free(pwd[0]);
	return (data);
}

void	incrementelvl(t_tool *data)
{
	char	*shellvl[2];
	int		lvl;
	char	*str;
	
	shellvl[1] = NULL;
	shellvl[0] = get_var("SHLVL", data->var_env);
	if (!shellvl[0])
		return ;
	lvl = ft_atoi(shellvl[0]);
	lvl++;
	free(shellvl[0]);
	str = ft_itoa(lvl);
	shellvl[0] = ft_strjoin("SHLVL=", str);
	free(str);
	memory_add(shellvl[0], data);
	export(shellvl, &data->var_env, data, 0);
}

t_tool	*init_shell(char **envp, t_tool *data)
{
	t_list	*node;
	char	**tab;
	int		i;

	i = 0;
	ft_bzero(data, sizeof(t_tool));
	if (!(*envp))
		return (noenv(data));
	tab = dup_tab(envp);
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		node = ft_lstnew(tab[i]);
		if (!node)
			return (ft_lstclear(&data->var_env, free), cleartb(tab), NULL);
		ft_lstadd_back(&data->var_env, node);
		i++;
	}
	incrementelvl(data);
	free(tab);
	return (data);
}
