/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:54:08 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/16 20:53:14 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_com(t_tool *data, t_cmds *cmd)
{
	close(data->base_fd[0]);
	close(data->base_fd[1]);
	if (check_path(cmd))
		exit(127);	//utiliser ft_exit
	if (check_redir(cmd))
		exit(1);	//tout free
	if (cmd->builtin)
		exit(exec_builtin(cmd->builtin, cmd, data, 1));
	if (execve(cmd->str[0], cmd->str, lst_to_tab(data->var_env, data)) == -1)
	{
		perror("Minishell");
		exit(127); //tout free
	}
}

int	child(t_tool *data, t_cmds *cmds, int i, int infile)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("minishell: "), 0);
	ft_heredoc(cmds, data); //fait un new pocesse
	ft_fork(data, fd, infile, cmds, i);
	
}

void    ft_exec(t_tool *data)
{
	t_cmds *cmd;
	int		infile;
	int		i;

	cmd = data->cmds;
	size_nb_com(data);
	while (data->cmds != NULL)
	{
        infile = child(data, data->cmds, i++, infile);
		data->cmds = data->cmds->next;
    }
	if (infile != -1)
		close(infile);
	i = 0;
	while (cmd)
	{
		waitpid(data->pid[i], &status, 0);
		G_ExitCode = status;
		i++;
		cmd = cmd->next;
	}
	free(data->pid);
}