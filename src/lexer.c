/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:39:08 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 14:24:06 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_size(char *str)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (str[++i])
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
	}
	return (t);
}

int	quote_space(char *str, char **s, int *y)
{
	int		i;
	int		yy;
	char	*l;

	l = *s;
	yy = *y;
	i = 0;
	if (str[i] == 34)
	{
		while (str[++i] != 34)
			l[yy++] = str[i - 1];
		l[yy++] = str[i - 1];
	}
	if (str[i] == 39)
	{
		while (str[++i] != 39)
			l[yy++] = str[i - 1];
		l[yy++] = str[i - 1];
	}
	*y = yy;
	*s = l;
	return (i);
}

char	*copy_with_space(char *str, char *s)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i += quote_space(&str[i], &s, &y);
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

char	*add_space(char *str, t_tool *data)
{
	char	*s;
	int		t;

	if (str[0] == '\0')
		return (NULL);
	t = new_size(str);
	if (!t)
		return (str);
	s = ft_malloc(sizeof(char) * (ft_strlen(str) + t + 1), data);
	if (!s)
		return (ft_perror("minishell: malloc", NULL), NULL);
	s = copy_with_space(str, s);
	return (s);
}

t_lexer	*check_word(char *str, t_tool *data)
{
	t_lexer	*new;

	new = ft_lstnewl(str, data);
	if (new == NULL)
		return (ft_perror("minishell: malloc", NULL), NULL);
	new->token = 0;
	if (str[0] == '|' && !str[1])
		new->token = Pipe;
	else if (str[0] == '>' && !str[1])
		new->token = fleched;
	else if (str[0] == '<' && !str[1])
		new->token = flecheg;
	else if (str[0] == '>' && str[1] == '>' && !str[2])
		new->token = fleched2;
	else if (str[0] == '<' && str[1] == '<' && !str[2])
		new->token = flecheg2;
	return (new);
}
