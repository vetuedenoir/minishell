
#include "../minishell.h"

int	extracte_node(t_lexer **lex, t_cmds **cmd)
{
	t_lexer	*tmp;
	t_lexer *node;

	tmp = (*lex)->prev;
	// erreur si il n y a pas de fichier apres un token ou qu il y a un autre token
	if ((*lex)->next == NULL)
	{
		printf("minishell: parse error near '\n'");
		return (0);
	}
	if ((*lex)->next->token != 0)
	{
		printf("minishell: parse error near %s\n", (*lex)->next->str);
		return (0);
	}
	// on ajoute le token et son fichier dans la structure cmds
	ft_add_back_lexer(&(*cmd)->redirection, (*lex));
	//(*cmd)->redirections = (*lex);
	(*lex) = (*lex)->next;
	// on suprime les 2 nodes ajouter a cmds du lexer
	if ((*lex)->next != NULL)
	{
		node = (*lex);
		(*lex) = (*lex)->next;
		node->next = NULL;
		(*lex)->prev = tmp;
	}
	if (tmp != NULL)
		tmp->next = (*lex);
	return (1);
}

t_cmds	*incertion(t_lexer **lex, t_cmds *cmd)
{
	t_lexer	*repere;
	int		i;

	repere = (*lex);
	// Des que l on rencontre un token on extrait le token et le fichier du lexer
	// pour les mettre dans la redirection de cmd
	while (*lex != NULL && (*lex)->token != Pipe)
	{
		if (lex->token != 0)
		{
			if (!extracte_node(&lex, &cmd))
				return (NULL);
		}
		lex = lex->next;
	}
	lex = repere;
	// calcule la taille de la liste actualiser jusqu au pipe
	i = 0;
	while (lex != NULL && lex->token != Pipe)
	{
		lex = lex->next;
		i++;
	}
	cmd->str = malloc(sizeof(char *) * i);
	if (cmd->str == NULL)
	{
		printf("malloc error");
	}
	lex = repere;
	// on copy les maillons restant qui sont la commande et ses argument
	// pour les mettre dans **str de cmd
	i = 0;
	while (lex != NULL && lex->token != Pipe)
	{
		cmd->str[i++] = lex->str;
		lex = lex->next;
	}
	clear_lex(lex, i);
	return (cmd);
	// peut etre suprime les nodes dont je n ai plus besoins
}


t_cmds	*parser(t_lexer *lex, char **envp)
{
	t_cmds	*commande_node;
	t_cmds	*commande;

	(void)envp;
	commande = NULL;
	if (lex->token == Pipe)
	{
		printf("minishell: parse error near '\n'");
		return (NULL); // faire fonction garbage
	}
	while (lex != NULL)
	{
		commande_node = ft_calloc(1, sizeof(t_cmds));
		if (commande_node == NULL)
		{

		}
		commande_node = incertion(&lex, commande_node);
		// peut etre envoyer un ** pour actualiser la liste
		
		if (commande_node == NULL)
			printf("erreur");
		add_back_cmds(&commande, commande_node);
		if (lex == NULL)
			break ;
		lex = lex->next;
	}
	if (lex->prev->token == Pipe)
	{
		printf("minishell: parse error near '\n'");
		return (NULL);
	}
	return (commande);
}
