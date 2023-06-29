/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:39:08 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/19 17:51:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer *check_word(char *str)
{
    t_lexer *new;
    
    new = ft_lstnewl(str);
	if (new == NULL)
		return (NULL);
	new->token = 0;
    if (str[0] == '|' && !str[1])
        new->token = Pipe;
    else if (str[0] == '>' && !str[1])
        new->token = fleched;
    else if (str[0] == '<' && !str[1])
        new->token = flecheg;
    else if (str[0] == '>' && str[1] == '>' && !str[2])
        new->token = fleched2;
    else if (str[0] == '<' && str[1] == '<'  && !str[2])
        new->token = flecheg2;
    return (new);
}

t_lexer *ft_lexer(void)
{
	char    **tab;
	int     i;
	char	*arg;
	t_lexer *lex;
	t_lexer	*new;
    
	lex = NULL;
	tab = NULL;
	if (ft_verif_quote(arg = readline(PROMPT)) == -1)
		return (free(arg), NULL);
	//tab = ft_split(arg, ' ');
	tab = ft_decoup(arg, tab, ' ');
	if (tab == NULL)
		return (NULL);
	free(arg);
	i = 0;
	while (tab[i])
	{
		new = check_word(tab[i++]);
		if (!new)
			return (free_garbage(), NULL);
		ft_add_back_lexer(&lex, new);   
	}
	return (lex);
}
