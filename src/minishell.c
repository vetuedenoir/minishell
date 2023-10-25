/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 14:25:28 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int	g_exitcode = 0;

void	verif_set(int ac, char **av)
{
	if (ac != 1 || av[1] != NULL)
	{
		error("minishell: doesn't take arguments", NULL, NULL);
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
	{
		error("minishell: stdin is not a terminal", NULL, NULL);
		exit(1);
	}
	if (!isatty(STDOUT_FILENO))
	{
		error("minishell: stdout is not a terminal", NULL, NULL);
		exit(1);
	}
}

void	boucleshell(t_tool *data)
{
	t_lexer	*lex;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_handler);
	while (1)
	{
		free_garbage(data);
		data->line = readline(PROMPT);
		if (!data->line)
			break ;
		memory_add(data->line, data);
		lex = ft_lexer(data);
		if (lex == NULL)
			continue ;
		add_history(data->line);
		data->cmds = parser(lex, data->cmds, data);
		if (data->cmds == NULL)
			continue ;
		expand(data);
		ft_exec(data);
		dup2(data->base_fd[0], 0);
		dup2(data->base_fd[1], 1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_tool	data;

	verif_set(argc, argv);
	if (!init_shell(envp, &data))
	{
		ft_perror("minishell", NULL);
		exit(1);
	}
	data.base_fd[0] = dup(0);
	data.base_fd[1] = dup(1);
	boucleshell(&data);
	close(data.base_fd[0]);
	close(data.base_fd[1]);
	ft_lstclear(&data.var_env, free);
	rl_clear_history();
	printf("exit\n");
	exit(0);
}
