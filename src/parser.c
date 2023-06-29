
#include "../minishell.h"


// peut etre changer cut en remalocant un maillon lex et en effacant l ancien
// evitera peut etre les leaks
void	cut_lex(t_lexer **lex, t_cmds **cmd)
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
}


int	extracte_node(t_lexer **lex, t_cmds **cmd)
{
	//t_lexer	*new;
	// erreur si il n y a pas de fichier apres un token ou qu il y a un autre token
	if ((*lex)->next == NULL)
	{
		free_garbage();
		return (printf("minishell: parse error near '\\n'"), 0);
	}
	if ((*lex)->next->token != 0)
	{
		printf("minishell: parse error near %s\n", (*lex)->next->str);
		return (free_garbage(), 0);
	}
	// on ajoute le token et son fichier dans la structure cmds
	cut_lex(lex, cmd);
	/*new = cut(lex);
	if (!new)
		return (clear_cmd(cmd), 0);
	ft_add_back_lexer(&(*cmd)->redirection, new);
	new = cut(lex);
	if (!new)
		return (clear_cmd(cmd), 0);
	ft_add_back_lexer(&(*cmd)->redirection, new);*/
	return (1);
}

t_cmds	*incertion(t_lexer **lex, t_cmds *cmd)
{
	int		i;
	t_lexer	*node;
	t_lexer	*tmp;

	// Des que l on rencontre un token on extrait le token et le fichier du lexer
	// pour les mettre dans la redirection de cmd

	tmp = NULL;
	node = (*lex);
	i = 0;
	if ((*lex)->token == Pipe)
	{
		printf( "minishell: parse error near '\\n'");
		return (free_garbage(), NULL);
	}
	while (node != NULL && node->token != Pipe)
	{
		if (node->token != 0)
		{
			if (!extracte_node(&node, &cmd))
				return (free_garbage(), NULL);
			cmd->num_redirections += 1;
		}
		if (!node)
			break ;
		if (tmp == NULL && (node->token == 5 || node->token == 0))
			tmp = node;
		if (node->token == 0)
		{
			i++;
			node = node->next;
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
		cmd->str[i] = ft_strdup((*lex)->str);  // peut etre pas besoins de strdup;
		if (!cmd->str[i])
		{
			printf("malloc error");
			return (free_garbage(), NULL);
		}
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

t_cmds	*parser(t_lexer *lex, char **envp)
{
	t_cmds	*commande_node;
	t_cmds	*commande;

	commande = NULL;
	while (lex != NULL)
	{
		commande_node = ft_calloc(1, sizeof(t_cmds));
		if (commande_node == NULL)
			return (free_garbage(), NULL); // juste free
		commande_node = incertion(&lex, commande_node);
		if (commande_node == NULL)
			return (free_garbage(), NULL);
		add_back_cmds(&commande, commande_node);
		if (lex == NULL)
			break ;
		lex = lex->next;
		if (lex == NULL)
		{
			printf("minishell: parse error near '\\n'");
			return (free_garbage(), NULL);
		}
		if (lex->token == Pipe)
		{
			printf("minishell: parse error near '%s'\n", lex->str);
			return (free_garbage(), NULL);
		}
	}
	return (commande);
}
