/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:33:53 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/18 21:12:28 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	exec_builtin(t_tool *data, t_cmds *cmd, char **envp)
{
	cmd->builtin(cmd->str[1], envp);	
}*/

void    exec_com(t_tool *data, t_cmds *cmd, char **envp)
{
    dprintf(2, "debut exec_com\n");
    if (cmd->num_redirections != 0)
    {
        check_redir(cmd);
    }
    (void)data;
    if (cmd->builtin)
    {
       // exec_builtin(data, cmd, envp);
        exit(1);
    }
    else if (access(cmd->str[0], F_OK) != -1)
		execve(cmd->str[0], cmd->str, envp);
        
}
void    simp_com(t_tool *data, t_cmds *cmd, char **envp)
{
    pid_t pid;
    int status;

    check_heredoc(cmd);
	pid = fork();
	if (pid == 0)
	{
        exec_com(data, cmd, envp);
    }
    waitpid(pid, &status, 0);
}
void    ft_fork(t_tool *data, int fd[2], int infile, t_cmds *cmd, char **envp, int i)
{
  
    data->pid[i] = fork();
    if (data->pid[i] == 0)
    {
        if (cmd->prev && cmd->next && dup2(infile, STDIN_FILENO) == -1)
		   ft_putstr_fd("ERREUR fonction dup2 stin\n", 2);
	    close(fd[0]);
	    if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
		    ft_putstr_fd("ERREUR fonction dup2 stdout\n", 2);
	    close(fd[1]);
	    if (cmd->prev)
		    close(infile);
        exec_com(data, data->cmds, envp);
    }
    else
	{
        dprintf(2, "pas de pid == 0\n");
		if (close(fd[1]) == -1 || dup2(fd[0], 0) == -1
			|| close(fd[0]) == -1)
			exit(1);
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
    printf("size malloc pid = %d\n", j);
}
int    child(t_tool *data, t_cmds *cmds, char **envp, int i, int infile)
{   
    int     fd[2];

    dprintf(2, "i = %d et cmd = %s\n", i, cmds->str[0]);
    if (pipe(fd) == -1)
        exit(1);
    check_heredoc(cmds);
    dprintf(2, " apres check_heredoc\n");
    ft_fork(data, fd, infile, cmds, envp, i);
    dprintf(2, "juste apres fork\n");
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
    data->cmds = data->cmds->next;
    return (infile);
}

void    multi_com(t_tool *data, char **envp)
{
    //int     fd[2];
    int     infile;
    t_cmds  *start;
    t_cmds  *tmp;
    int i;

    i = 0;
    start = data->cmds;
    tmp = data->cmds;
    infile = STDIN_FILENO;
    size_nb_com(data);
    while(data->cmds != NULL)
    {
        infile = child(data, tmp, envp, i++, infile);
        tmp= tmp->next;
    }
    int j;
    j = 0;
    while (j < i)
    {
        waitpid(data->pid[j], NULL, 0);
        j++;
    }
    data->cmds = start;
    //free(data->pid);
    printf("normalllllllll\n");
}
void    ft_exec(t_tool *data, char **envp)
{
    t_cmds *cmd;

    cmd = data->cmds;
    printf("debut exec\n");
    if (cmd->next == NULL)
        simp_com(data, cmd, envp);
    else
        multi_com(data, envp);
    if (cmd->file_name)
    {
        unlink(cmd->file_name);
    }
    dprintf(2, "normalement jsuis bien\n");
}