
#include "../minishell.h"

t_lexer	*cut_lex(t_lexer **lex, t_cmds **cmd)
{
	t_lexer *first;
	t_lexer	*token_node;
	t_lexer	*last;
	
	first = (*lex)->prev;
	token_node = (*lex);
	last = (*lex)->next->next;
	if (first == NULL)
	{
		if (last)
			last->prev = first;
		(*lex) = last;
	}
	else
	{
		first->next = last;
		(*lex) = first;
		if (last)
			(*lex)->next->prev = first;
	}
	token_node->prev = NULL;
	token_node->next->next = NULL;
	ft_add_back_lexer(&(*cmd)->redirection, token_node);
	return (last);
}


int	extracte_node(t_lexer **lex, t_cmds **cmd)
{
	// erreur si il n y a pas de fichier apres un token ou qu il y a un autre token
	if ((*lex)->next == NULL)
	{
		free_garbage();
		return (printf("minishell: parse error near '\\n'\n"), 0);
	}
	if ((*lex)->next->token != 0)
	{
		printf("minishell: parse error near %s\n", (*lex)->next->str);
		return (free_garbage(), 0);
	}
	// on ajoute le token et son fichier dans la structure cmds
	*lex = cut_lex(lex, cmd);
	return (1);
}

t_cmds	*incertion(t_lexer **lex, t_cmds *cmd)
{
	int		i;
	t_lexer	*tmp;

	// Des que l on rencontre un token on extrait le token et le fichier du lexer
	// pour les mettre dans la redirection de cmd

	tmp = NULL;
	i = 0;
	if ((*lex)->token == Pipe)
	{
		printf( "minishell: parse error near '\\n'");
		return (free_garbage(), NULL);
	}
	while (*lex != NULL && (*lex)->token != Pipe)
	{
		if ((*lex)->token != 0)
		{
			if (!extracte_node(lex, &cmd))
				return (free_garbage(), NULL);
			cmd->num_redirections += 1;
		}
		if (!(*lex))
			break ;
		if (tmp == NULL && ((*lex)->token == 5 || (*lex)->token == 0))
			tmp = *lex;
		if ((*lex)->token == 0)
		{
			i++;
			*lex = (*lex)->next;
		}
	}
	// calcule la taille de la liste actualiser jusqu au pipe
	cmd->str = ft_malloc(sizeof(char *) * (i + 1));
	if (cmd->str == NULL)
	{
		printf("malloc error");
		return (free_garbage(), NULL);
	}
	(*lex) = tmp;
	// on copy les maillons restant qui sont la commande et ses argument
	// pour les mettre dans **str de cmd
	i = 0;
	while (*lex != NULL && (*lex)->token != Pipe)
	{
		cmd->str[i] = (*lex)->str;
		*lex = (*lex)->next;
		i++;
	}
	cmd->str[i] = NULL;
	(*lex) = tmp;
	clear_lex(lex, (i));  // changer la fonction pour qu elle ne free pas
	return (cmd);
}

/*Parsing grossier la fonction erreur bin ne marche pas tres bien
bcp de leaks , peut etre revoir le decoupage ...*/

t_cmds	*parser(t_lexer *lex)
{
	t_cmds	*commande_node;
	t_cmds	*commande;

	commande = NULL;
	while (lex != NULL)
	{
		commande_node = ft_calloc_g(1, sizeof(t_cmds));
		if (commande_node == NULL)
			return (free_garbage(), NULL);
		commande_node = incertion(&lex, commande_node);
		if (commande_node == NULL)
			return (free_garbage(), NULL);
		add_back_cmds(&commande, commande_node);
		if (lex == NULL)
			break ;
		lex = lex->next;
		if (lex == NULL || lex->token == Pipe)
		{
			if (lex == NULL)
				printf("minishell: parse error near '\\n'\n");
			if (lex->token == Pipe)
				printf("minishell: parse error near '%s'\n", lex->str);
			return (free_garbage(), NULL);
		}
	}
	return (commande);
}
