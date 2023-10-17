/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/17 19:42:22 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned char G_ExitCode = 0;

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
		add_history(data->line);
		lex = ft_lexer(data);
		if (lex == NULL)
			continue ;
	//	printlex(lex);
		data->cmds = parser(lex, data->cmds, data);
		if (data->cmds == NULL)
			continue ;
		expand(data);
		check_path(&data->cmds, data->var_env, data);
		if (data->garbage_collector == NULL)
			continue ;
		//print_cmd(data.cmds); // pour voir ce que c a sort
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
		exit(1);
	data.base_fd[0] = dup(0);
	data.base_fd[1] = dup(1);
	
	boucleshell(&data);
	
	close(data.base_fd[0]);
	close(data.base_fd[1]);
	printf("exit\n");
	ft_lstclear(&data.var_env, free);
	rl_clear_history();
	exit(0);
}
