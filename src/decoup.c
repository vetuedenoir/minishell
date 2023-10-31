/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:45:46 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/31 12:38:13 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	lents(const char *str, char c)
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
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			t++;
	}
	return (t);
}

int	ft_verif_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34 && s[i] != 0)
				i++;
			if (s[i] == 0)
				return (error("minishell: double quote doesn't guard",
						NULL, NULL), 1);
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i] != 0)
				i++;
			if (s[i] == 0)
				return (error("minishell: single quote doesn't guard",
						NULL, NULL), 1);
		}
	}
	return (0);
}

int	line_lents(const char *s, int index, char c)
{
	int	t;
	int	i;

	i = index;
	t = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == 34)
		{
			while (s[++i] != 34)
				t++;
			t++;
		}
		if (s[i] == 39)
		{
			while (s[++i] != 39)
				t++;
			t++;
		}
		i++;
		t++;
	}
	return (t);
}

static char	*cpy_tsx(const char *s, int index, char c, t_tool *data)
{
	int		i;
	char	*str;

	str = ft_malloc(sizeof(char) * (line_lents(s, index, c) + 1), data);
	if (str == NULL)
		return (ft_perror("minishell: malloc", NULL), NULL);
	i = 0;
	while (s[index] != c && s[index])
	{
		if (s[index] == 34)
		{
			while (s[++index] != 34)
				str[i++] = s[index - 1];
			str[i++] = s[index - 1];
		}
		if (s[index] == 39)
		{
			while (s[++index] != 39)
				str[i++] = s[index - 1];
			str[i++] = s[index - 1];
		}
		if (s[index])
			str[i++] = s[index++];
	}
	return (str[i] = '\0', str);
}

char	**ft_decoup(char *arg, char **tab, char c, t_tool *data)
{
	int	i;
	int	x;
	int	t;

	i = -1;
	x = 0;
	tab = ft_malloc(sizeof(char *) * (lents(arg, c) + 1), data);
	if (!tab)
		return (ft_perror("minishell: malloc", NULL), NULL);
	t = (int)ft_strlen(arg);
	while (i++ < t)
	{
		if (arg[i] != c && arg[i])
		{
			tab[x] = cpy_tsx(arg, i, c, data);
			if (tab[x] == NULL)
				return (free_garbage(data), NULL);
			i += ft_strlen(tab[x]);
			x++;
		}
	}
	tab[x] = NULL;
	return (tab);
}
