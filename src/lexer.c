/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:39:08 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/02 17:40:45 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer *check_word(char *str)
{
    int i;
    t_lexer *new;
    
    i = 0;
    new = ft_lstnewl(str);
    if (str[0] == '|' && !str[1])
        new.token = Pipe;
    else if (str[0] == '>' && !str[1])
        new.token = fleched;
    else if (str[0] == '<' && !str[1])
        new.token = flecheg;
    else if (str[0] == '>' && str[1] == '>' && !str[2])
        new.token = fleched2;
    else if (str[0] == '<' && str[1] == '<'  && !str[2])
        new.token = flecheg2;
    return (new);
}

t_lexer *ft_lexer(void)
{
	char    **tab;
	int     i;
	t_lexer *lex;
	t_lexer	*new;
    
	lex = NULL;
	tab = ft_split(readline(PROMPT), " ");
	if (tab = NULL)
		return (NULL);
	while (tab[i])
	{
		new = check_word(tab[i++]);
		if (!new)
		{
			ft_clearl(lex);
			return (cleartb(tab), NULL);
		}
		ft_add_back_lexer(lex, new);   
	}
	cleartb(tab);
	return (lex);
}
