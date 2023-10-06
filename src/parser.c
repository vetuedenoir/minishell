/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:46:15 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/06 12:37:02 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*cut_lex(t_lexer **lex, t_cmds **cmd)
{
	t_lexer	*first;
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
		error("Minishell: syntaxe error near unexpected token 'newline'", NULL, NULL);
		//error("Minishell: parse error near '\\n'", NULL, NULL);
	else if ((*lex)->next->token == 1)
		error("Minishell: parse error near '>'", NULL, NULL);
	else if ((*lex)->next->token == 2)
		error("Minishell: parse error near '<'", NULL, NULL);
	else if ((*lex)->next->token == 3)
		error("Minishell: syntax error near unexpected token '>>'", NULL, NULL);
		//error("Minishell: parse error near >>", NULL, NULL);
	else if ((*lex)->next->token == 4)
		error("Minishell: parse error near '<<'", NULL, NULL);
	else if ((*lex)->next->token == 5)
		error("Minishell: parse error near '|'", NULL, NULL);
	// on ajoute le token et son fichier dans la structure cmds
	if ((*lex)->next == NULL || (*lex)->next->token != 0 )
		return (*cmd = NULL, 0);
	*lex = cut_lex(lex, cmd);
	return (1);
}

t_lexer	*boucle(t_lexer **lex, t_cmds **cmd, t_lexer **tmp, int *i)
{
	*tmp = NULL;
	*i = 0;
	while (*lex != NULL && (*lex)->token != Pipe)
	{
		if ((*lex)->token != 0)
		{
			if (!extracte_node(lex, cmd))
				return (NULL);
			(*cmd)->num_redirections += 1;
		}
		if (!(*lex))
			break ;
		if (*tmp == NULL && ((*lex)->token == 5 || (*lex)->token == 0))
			*tmp = *lex;
		if ((*lex)->token == 0)
		{
			*i = *i + 1;
			*lex = (*lex)->next;
		}
	}
	return (*tmp);
}

t_cmds	*incertion(t_lexer **lex, t_cmds *cmd, t_tool *data)
{
	int		i;
	t_lexer	*tmp;

	// Des que l on rencontre un token on extrait le token et le fichier du lexer
	// pour les mettre dans la redirection de cmd
	if ((*lex)->token == Pipe)
		return (error("Minishell: parse error near '|'", NULL, NULL), NULL);
	*lex = boucle(lex, &cmd, &tmp, &i);
	if (!(*lex))
		return (cmd);
	//= calcule la taille de la liste actualiser jusqu au pipe
	cmd->str = ft_malloc(sizeof(char *) * (i + 1), data);
	if (cmd->str == NULL)
		return (error("malloc error", NULL, NULL), NULL);
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
	clear_lex(lex, (i)); //la fonction ne free pas
	return (cmd);
}

t_cmds	*parser(t_lexer *lex, t_cmds *commande, t_tool *data)
{
	t_cmds	*commande_node;

	commande = NULL;
	while (lex != NULL)
	{
		commande_node = ft_calloc_g(1, sizeof(t_cmds), data);
		if (commande_node == NULL)
			return (NULL);
		commande_node = incertion(&lex, commande_node, data);
		if (commande_node == NULL)
			return (NULL);
		add_back_cmds(&commande, commande_node);
		if (lex == NULL)
			break ;
		lex = lex->next;
		if (lex == NULL)
			return (error("Minishell: parse error near '\\n'", NULL, NULL), NULL);
		if (lex->token == Pipe)
			return (error("Minishell: parse error near '|'\n", NULL, NULL), NULL);
	}
	return (commande);
}
