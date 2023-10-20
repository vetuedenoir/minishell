/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:54:08 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/20 22:24:22 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_com(t_tool *data, t_cmds *cmd)
{
	close(data->base_fd[0]);
	close(data->base_fd[1]);
	if (check_path(cmd))
		free_all_and_exit(127, data);	//utiliser ft_exit
	if (check_redir(cmd))
		free_all_and_exit(1, data);	//tout free
	if (cmd->builtin)
		free_all_and_exit(exec_builtin(cmd->builtin, cmd, data, 1), data);
	if (execve(cmd->str[0], cmd->str, lst_to_tab(data->var_env, data)) == -1)
	{
		perror("Minishell");
		free_all_and_exit(127, data); //tout free
	}
}

int	ft_fork(t_tool *data, int fd[2], int infile, t_cmds *cmd, int i)
{
  
	data->pid[i] = fork();
	if (data->pid[i] == -1)
	{
		perror("minishell")
		return (-1);
	}
	if (data->pid[i] == 0)
	{
		close(data->base_fd[0]);
		close(data->base_fd[1]);
		if (cmd->prev && cmd->file_name && dup2(infile, STDIN_FILENO) == -1)
		   ft_putstr_fd("ERREUR fonction dup2 stin\n", 2);
		close(fd[0]);
		if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
			ft_putstr_fd("ERREUR fonction dup2 stdout\n", 2);
		close(fd[1]);
		if (cmd->prev)
			close(infile);
		exec_com(data, data->cmds);
	}
	else
	{
		if (close(fd[1]) == -1 || dup2(fd[0], 0) == -1
			|| close(fd[0]) == -1)
			wait(NULL);
	}
}

int	child(t_tool *data, t_cmds *cmds, int i, int infile)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) == -1)
		return (perror("minishell: "), -1);
	if (ft_heredoc(cmds, data) == -1)
		return (-1); //fait un new pocesse
	ret = ft_fork(data, fd, infile, cmds, i);
	close(fd[1]);
	if (cmds->prev)
		close(infile);
	infile = fd[0];
	if (ret == -1)
		return (ret);
	return (infile);
}

void    nmulti_com(t_tool *data)
{
	t_cmds *cmd;
	int		infile;
	int		i;

	cmd = data->cmds;
	size_nb_com(data);
	while (data->cmds != NULL)
	{
        infile = child(data, data->cmds, i++, infile);
		if (infile == -1)
		{
			G_ExitCode = 1;
			break ;
		}
		data->cmds = data->cmds->next;
    }
	if (infile != -1)
		close(infile);
	i = 0;
	while (cmd && data->pid[i])
	{
		waitpid(data->pid[i], &status, 0);
		G_ExitCode = status;
		i++;
		cmd = cmd->next;
	}
	free(data->pid);
}

void	nsimp_com(t_tool *data, t_cmds *cmd)
{
	pid_t	pid;
	int		status;

	if (check_heredoc(cmd, data) == -1)
		return ;
	if (cmd->builtin)
	{
		check_redir(cmd);
		G_ExitCode = exec_builtin(cmd->builtin, cmd, data, 0);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		G_ExitCode = 1;
		return ;
	}
	if (pid == 0)
		exec_com(data, cmd);
	waitpid(pid, &status, 0);
	G_ExitCode = status;
}
