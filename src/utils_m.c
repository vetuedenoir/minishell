/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:09:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/26 14:15:47 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc_g(size_t nmemb, size_t size, t_tool *data)
{
	void	*mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = ft_malloc(nmemb * size, data);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}

char	*ft_strdup_g(const char *s, t_tool *data)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_malloc(sizeof(char) * (ft_strlen(s) + 1), data);
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
static int	lents(const char *str, char c)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			t++;
		i++;
	}
	return (t);
}

static char	*cpy_tsx(const char *s, int index, char c)
{
	int		i;
	int		t;
	char	*str;

	i = index;
	t = 0;
	while (s[i] != c && s[i])
	{
		t++;
		i++;
	}
	str = malloc(sizeof(char) * (t + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[index] != c && s[index])
	{
		str[i] = s[index];
		i++;
		index++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_g(char const *s, char c)
{
	char	**ts;
	int		x;
	int		i;

	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	ts = malloc(sizeof(char *) * (lents(s, c) + 1));
	if (ts == NULL)
		return (NULL);
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c && s[i])
		{
			ts[x] = cpy_tsx(s, i, c);
			if (ts[x] == NULL)
				return (free_all(ts, x)); // a changer
			i += ft_strlen(ts[x]);
			x++;
		}
		i++;
	}
	ts[x] = 0;
	return (ts);
}*/
