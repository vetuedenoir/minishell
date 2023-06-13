
#include "../minishell.h"

void	extracte_node(t_lexer **lex, *t_cmds **cmd)
{
	t_lexer	*tmp;
	t_lexer *node;

	tmp = (*lex)->prev;
	// erreur si il n y a pas de fichier apres un token ou qu il y a un autre token
	if ((*lex)->next == NULL)
	{
		printf("minishell: parse error near '\n'");

	}
	if ((*lex)->next->token != 0)
	{
		printf("minishell: parse error near %s\n", (*lex)->next->str);

	}
	// on ajoute le token et son fichier dans la structure cmds
	ft_add_back_lexer((*cmd)->&redirections, (*lex));
	//(*cmd)->redirections = (*lex);
	(*lex) = (*lex)->next;
	// on suprime les 2 node ajoute a cmds du lexer
	if ((*lex)->next != NULL)
	{
		node = (*lex);
		(*lex) = (*lex)->next;
		node->next = NULL;
		(*lex)->prev = tmp;
	}
	if (tmp != NULL)
		tmp->next = (*lex)
}

t_cmds	*incertion(t_lexer *lex, t_cmds *cmd)
{
	t_lexer	*repere;
	int		i;

	repere = lex
	while (lex->token != 5 && lex != NULL)
	{
		if (lex->token != 0)
		{
			extracte_node(&lex, &cmd);
		}
	lex = lex->next;
	}
	lex = repere;
	// reste a compter le nombre de noueud jusqu au pipe
	cmds->str = malloc(sizeof(char *));
	if (cmds->str == NULL)
	{
		
	}
	i = 0;
	while (lex != NULL)
	{
		cmds->str[i++] = lex->str;
		lex = lex->next;
	}
	return (cmd);
}

t_cmds	*parser(t_lexer *lex, char **envp)
{
	t_cmds	*commande;
	t_lexer	*repere;

	while (lex != NULL)
	{
		commande = ft_calloc(1, sizeof(t_cmds));
		repere = lex;
		incertion(lex, commande);

	}

}
