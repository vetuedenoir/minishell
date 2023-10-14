/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:33:53 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/14 20:20:03 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(int (*builtin)(char **arg, t_list **env, t_tool *data, int flag), t_cmds *cmd, t_tool *data, int flag)
{
	if (!ft_strncmp(cmd->str[0], "exit", 5))
	{
			//dprintf(2, "builin est egal a exit\n");
			close(data->base_fd[0]);
			close(data->base_fd[1]);
	}
	return (builtin(&cmd->str[1], &data->var_env, data, flag));
}

void	exec_com(t_tool *data, t_cmds *cmd)
{
	close(data->base_fd[0]);
	close(data->base_fd[1]);
	//dprintf(2, "EXEC_COM\n");
	check_redir(cmd);
	if (cmd->builtin)
		exit(exec_builtin(cmd->builtin, cmd, data, 1));
	else if (!cmd->str || cmd->str[0] == NULL)
		exit(1);
	else if (!access(cmd->str[0], X_OK | F_OK))
	{
		if (execve(cmd->str[0], cmd->str, lst_to_tab(data->var_env, data)) == -1)
			error("Minishell: ", cmd->str[0], ": Is a directory\n");
	}
	else
		error("Minishell : errore exec\n", NULL, NULL);	
}



void    ft_fork(t_tool *data, int fd[2], int infile, t_cmds *cmd, int i)
{
  
	data->pid[i] = fork();
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

void    size_nb_com(t_tool *data)
{
	t_cmds  *start;
	int j;

	j = 0;
	start= data->cmds;
	while(data->cmds != NULL)
	{
		data->cmds = data->cmds->next;
		j++;
	}
	data->pid = malloc(j * sizeof(pid_t));
	data->cmds = start;
}

int    child(t_tool *data, t_cmds *cmds, int i, int infile)
{   
	int     fd[2];

	if (pipe(fd) == -1)// mettre des perror
		exit(1);
	check_heredoc(cmds, data);
	ft_fork(data, fd, infile, cmds, i);
	close(fd[1]);
	if (cmds->prev)
		close(infile);
	if (cmds->file_name)
	{
		close(fd[0]);
		infile = open(cmds->file_name, O_RDONLY);
	}
	else
		infile = fd[0];
	return (infile);
}

void    multi_com(t_tool *data)
{
	int	infile;
	int i;
	int j;
	int	status;

	i = 0;
	size_nb_com(data);
	while(data->cmds != NULL)
	{
		infile = child(data, data->cmds, i++, infile);
		data->cmds = data->cmds->next;
	}
	close(infile);
	j = 0;
	while (j < i)
	{
		waitpid(data->pid[j], &status, 0);
		G_ExitCode = status;
		j++;
	}
	free(data->pid);
}

void	simp_com(t_tool *data, t_cmds *cmd)
{
	pid_t	pid;
	int		status;

	check_heredoc(cmd, data);
	if (cmd->builtin)
	{
		check_redir(cmd);
		G_ExitCode = exec_builtin(cmd->builtin, cmd, data, 0);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		exec_com(data, cmd);
	}
	waitpid(pid, &status, 0);
	G_ExitCode = status;
}

void    ft_exec(t_tool *data)
{
	t_cmds *cmd;

	cmd = data->cmds;
//	printf("debut de ft_exec\n");
	if (cmd->next == NULL)
		simp_com(data, cmd);
	else
		multi_com(data);
//	dprintf(2, "avant de free les file_name\n");
	while(cmd)
	{
		if (cmd->file_name)
		{
			unlink(cmd->file_name);
			free(cmd->file_name);
		}
		cmd= cmd->next;
	}
	// if (cmd->file_name)
	// {
	// 	unlink(cmd->file_name);
	// }
//	dprintf(2, "NORMALEMENT jsuis bien\n");
}