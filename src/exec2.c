/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:42:32 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/26 12:39:36 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(int (*builtin)(char **arg, t_list **env, t_tool *data, \
int flag), t_cmds *cmd, t_tool *data, int flag)
{
	if (!ft_strncmp(cmd->str[0], "exit", 5))
	{
		close(data->base_fd[0]);
		close(data->base_fd[1]);
	}
	return (builtin(&cmd->str[1], &data->var_env, data, flag));
}

int	size_nb_com(t_tool *data)
{
	t_cmds	*start;
	int		j;

	j = 0;
	start = data->cmds;
	while (data->cmds != NULL)
	{
		data->cmds = data->cmds->next;
		j++;
	}
	data->pid = ft_calloc_g(sizeof(pid_t), j + 1, data);
	if (!data->pid)
		return (ft_perror("minishell", NULL), 1);
	data->cmds = start;
	return (0);
}

void	exec_com(t_tool *data, t_cmds *cmd)
{
	close(data->base_fd[0]);
	close(data->base_fd[1]);
	if (check_path(&cmd, data->var_env, data))
		free_all_and_exit(127, data);
	if (check_redir(cmd))
		free_all_and_exit(1, data);
	if (cmd->builtin)
		free_all_and_exit(exec_builtin(cmd->builtin, cmd, data, 1), data);
	if (execve(cmd->str[0], cmd->str, lst_to_tab(data->var_env, data)) == -1)
	{
		ft_perror("minishell: ", cmd->str[0]);
		free_all_and_exit(126, data);
	}
}

void	wait_processes(t_tool *data, int sig, int status)
{
	int		i;
	t_cmds	*node;

	i = -1;
	node = data->cmds;
	while (data->cmds && data->pid[++i])
	{
		waitpid(data->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exitcode = status % 255;
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == 2)
				g_exitcode = 130;
			if (sig == 3)
				g_exitcode = 131;
		}
		data->cmds = data->cmds->next;
	}
	if (sig == 2)
		printf("\n");
	if (sig == 3)
		printf("Quit (core dumped)\n");
	return (data->cmds = node, (void)0);
}
