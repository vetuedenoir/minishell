/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/13 14:34:55 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	export(pwd, &data->var_env, data);
	free(pwd[0]);
	return (data);
}

void	incrementelvl(t_tool *data)
{
	char	*shellvl[2];
	int		lvl;
	
	shellvl[1] = NULL;
	shellvl[0] = get_var("SHLVL", data->var_env);
	if (!shellvl[0])
		return ;
	lvl = ft_atoi(shellvl[0]);
	lvl++;
	free(shellvl[0]);
	shellvl[0] = ft_strjoin("SHLVL=", ft_itoa(lvl));
	export(shellvl, &data->var_env, data);
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

void	verif_set(int ac, char **av)
{
	//struct termios	term;

	if (ac != 1 || av[1] != NULL)
	{
		ft_putstr_fd("Minishell: doesn't take arguments\n", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Minishell: stdin is not a terminal\n", 2);
		exit(1);
	}
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("Minishell: stdout is not a terminal\n", 2);
		exit(1);
	}
	/*if (tcgetattr(STDIN_FILENO, &term) != 0)
		perror("tcgetattr() error");
	term.c_iflag = INLCR;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		perror("tcsetattr() error");*/
}

//void	boucleshell()

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer	*lex;
	t_tool	data;
//	struct sigaction	sa;

	verif_set(argc, argv);
	if (!init_shell(envp, &data))
		exit(1);
//	ft_memset(&sa, 0, sizeof(struct sigaction));

	data.base_fd[0] = dup(0);
	data.base_fd[1] = dup(1);
	while (1)
	{	
		free_garbage(&data);
		data.line = readline(PROMPT);
		if (!data.line)
			break ;
		memory_add(data.line, &data);
		add_history(data.line);
		lex = ft_lexer(&data);
		if (lex == NULL)
			continue ;
	//	printlex(lex);
		data.cmds = parser(lex, data.cmds, &data);
		if (data.cmds == NULL)
			continue ;
		expand(&data);
	
		check_path(&data.cmds, data.var_env, &data);
		if (data.garbage_collector == NULL)
			continue ;
		//print_cmd(data.cmds); // pour voir ce que c a sort
		ft_exec(&data);
		dup2(data.base_fd[0], 0);
		dup2(data.base_fd[1], 1);
	}
	close(data.base_fd[0]);
	close(data.base_fd[1]);
	printf("sorti de la boucle main\n");
	ft_lstclear(&data.var_env, free);
	rl_clear_history();
	exit(0);
}
