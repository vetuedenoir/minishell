/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:55:43 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 16:49:28 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
** Nom de la fonction : ft_split
** ----------------------------
** Description :
** Cette fonction alloue et retourne un tableau de chaînes de caractères
** obtenu en séparant la chaîne de caractères s en fonction du caractère
** c donné en paramètre. Chaque chaîne dans le tableau est une sous-chaîne
** de s, séparée par le caractère c.
**
** Paramètres :
** - s : la chaîne de caractères à séparer.
** - c : le caractère à utiliser pour séparer s.
**
** Retourne :
** - Un tableau de chaînes de caractères obtenu en séparant s en fonction de c,
** ou NULL si l'allocation de mémoire a échoué.
**
** Notes :
** - Si s est NULL, la fonction renvoie NULL.
** - La mémoire allouée par cette fonction doit être libérée par l'appelant
** à l'aide de la fonction free.
** - Le dernier élément du tableau est un pointeur NULL pour indiquer sa fin.
*/

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

/*
** La fonction lents calcule le nombre de sous-chaînes de caractères
** présentes dans la chaîne s, délimitées par le caractère c.
*/

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

/*
** La fonction cpy_tsx copie chaque mot dans sa sous-chaîne.
** Elle prend en entrée la chaîne de caractères s,
** l'index de début du mot dans s et le caractère délimitant c.
*/

static void	*free_all(char **ts, int x)
{
	while (--x >= 0)
		free(ts[x]);
	free(ts);
	return (NULL);
}

/*
** La fonction free_all libère la mémoire allouée pour le tableau de chaînes
** et pour toutes ses sous-chaînes. Elle prend en entrée le tableau de chaînes ts
** et le nombre d'éléments à libérer x.
** Elle est apeller en cas d'erreur.
*/

char	**ft_split(char const *s, char c)
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
				return (free_all(ts, x));
			i += ft_strlen(ts[x]);
			x++;
		}
		i++;
	}
	ts[x] = 0;
	return (ts);
}
