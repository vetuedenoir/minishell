/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/19 17:29:20 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*g_garbage_collector = NULL;

t_tool	*init_shell(char **envp, t_tool *data)
{
	t_list	*node;
	char	**tab;
	int		i;

	i = 0;
	ft_bzero(data, sizeof(t_tool));
	if (!(*envp))
		return (NULL);
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
	free(tab);
	return (data);
}

void	verif_set(int ac, char **av)
{
	//struct termios	term;

	if (ac != 1 || av[1] != NULL)
	{
		ft_putstr_fd("Erreur : Ce programme ne prend pas d argument\n", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Erreur : stdin n est pas un terminal\n", 2);
		exit(1);
	}
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("Erreur : stdout n est pas un terminal\n", 2);
		exit(1);
	}
	/*if (tcgetattr(STDIN_FILENO, &term) != 0)
		perror("tcgetattr() error");
	term.c_iflag = INLCR;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		perror("tcsetattr() error");*/
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer	*lex;
	t_tool	data;
	int	base_fd[2];

	base_fd[0] = dup(0);
	base_fd[1] = dup(1);
	verif_set(argc, argv);
	if (!init_shell(envp, &data))
		exit(1);
	while (1)
	{	
		free_garbage();
	//	printf("biennnnnnnnnnnnn\n");
		data.line = readline(PROMPT);
		if (!data.line)
			break ;
		memory_add(data.line);
		add_history(data.line);
		lex = ft_lexer(&data);
		if (lex == NULL)
			continue ;
		printlex(lex);
		data.cmds = parser(lex, data.cmds);
		if (data.cmds == NULL)
			continue ;
		expand(&data);
		check_path(&data.cmds, data.var_env);
		print_cmd(data.cmds); // pour voir ce que c a sort
		ft_exec(&data, envp);
		dup2(base_fd[0], 0);
		dup2(base_fd[1], 1);
	//	printf("pk tu sort du programme\n");
	}
	close(base_fd[0]);
	close(base_fd[1]);
	printf("sorti de la boucle main\n");
	ft_lstclear(&data.var_env, free);
	rl_clear_history();
	exit(0);
}
