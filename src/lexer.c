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

int	new_size(char *str)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == 34)
		{
			while (str[++i] != 34)
				;
		}
		if (str[i] == 39)
		{
			while (str[++i] != 39)
				;
		}
		if (str[i] && ft_strchr("<>|", str[i]))
		{
			if (str[i] == str[i + 1] && str[i] != '|')
				i++;
			t += 2;
		}
		i++;
	}
	return (t);
}

char	*copy_with_space(char *str, char *s)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			while (str[++i] != 34)
				s[y++] = str[i - 1];
			s[y++] = str[i - 1];
		}
		if (str[i] == 39)
		{
			while (str[++i] != 39)
				s[y++] = str[i - 1];
			s[y++] = str[i - 1];
		}
		if (str[i] && ft_strchr("<>|", str[i]))
		{
			s[y++] = ' ';
			s[y++] = str[i++];
			if (str[i - 1] == str[i] && str[i - 1] != '|')
				s[y++] = str[i++];
			s[y++] = ' ';
		}
		else
			s[y++] = str[i++];
	}
	s[y] = 0;
	return (s);
}

char	*add_space(char *str)
{
	char	*s;
	int	t;

	t = new_size(str);
	if (!t || t == -1)
		return (str);
	s = malloc(sizeof(char) * (ft_strlen(str) + t + 1));
	if (!s)
		return (NULL);
	s = copy_with_space(str, s);
	return (s);
}

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

t_lexer *ft_lexer(t_tool *data)
{
	char		**tab;
	char		*arg;
	int		i;
	t_lexer	*lex;
	t_lexer	*new;
    
	lex = NULL;
	tab = NULL;
	if (ft_verif_quote(data->str = readline(PROMPT)) == -1)
		return (free(data->str), NULL);
	memory_add(data->str);
	arg = add_space(data->str);
	printf("arg = %s\n", arg);
	tab = ft_decoup(&arg, tab, ' ');
	if (tab == NULL)
		return (NULL);
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
