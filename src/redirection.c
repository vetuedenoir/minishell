#include "../minishell.h"

void	ajout_infile(t_lexer *redir, int i, char *file)
{
	int	fd;

	dprintf(2, "ajout infile\n");
	if (i == 4)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd > 0 && dup2(fd, STDIN_FILENO) > -1)
			close(fd);
		return ;
	}
	fd = open(redir->next->str, O_RDONLY, 0644);
	if (fd < 0)
	{
		//error("Minishell: ", file, ": No such or directory");
		ft_putstr_fd("Minishel: infile: No such file or directory\n", 2);
		exit(1);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) > -1)
	{
		close(fd);
	}
}
void    ajout_outfile(t_lexer *redir, int i)
{
	int fd;
	dprintf(2, "ajout outfile\n");
	if (i == 1)
		fd = open(redir->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (i == 3)
		fd = open(redir->next->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishel: outfile error\n", 2);
		exit(1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) > -1)
	{
		close(fd);
	}
}
void     check_redir(t_cmds *cmd)
{
	t_lexer *start;

	//dprintf(2, "token redir = %d\n", cmd->redirection->token);
	start = cmd->redirection;
	while (cmd->redirection != NULL)
	{
		if (cmd->redirection->token == 1)
			ajout_outfile(cmd->redirection,1);
		else if (cmd->redirection->token == 3)
			ajout_outfile(cmd->redirection, 3);
		else if (cmd->redirection->token == 2)
			ajout_infile(cmd->redirection, 2, cmd->file_name);
		else if (cmd->redirection->token == 4)
			ajout_infile(cmd->redirection, 4, cmd->file_name);
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = start;
}