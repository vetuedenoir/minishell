/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:36:26 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 16:35:39 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strtrim
** ------------------------------
** Description :
** Cette fonction alloue et retourne une copie de la chaîne de caractères s1
** sans les caractères spécifiés dans l'ensemble `set` au début et à la fin
** de la chaîne. Si la chaîne s1 ne contient aucun caractère à retirer, une
** copie identique de s1 est retournée. La chaîne de caractères retournée
** est terminée par un caractère nul.
**
** Paramètres :
** - s1 : la chaîne de caractères à traiter.
** - set : la chaîne de caractères représentant l'ensemble de caractères
**         à retirer de `s1`.
**
** Retourne :
** - La nouvelle chaîne de caractères obtenue à partir de `s1`,
**   sans les caractères spécifiés dans `set`,
**   ou NULL si l'allocation de mémoire a échoué.
**
** Notes :
** - Si `s1` ou `set` est NULL, la fonction renvoie NULL.
** - La mémoire allouée par cette fonction doit être libérée par l'appelant
**   à l'aide de la fonction `free`.
*/

static int	checkchar(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	len;
	size_t	av;
	size_t	i;
	char	*str;

	av = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (checkchar(s1[av], set) && s1)
		av++;
	len = ft_strlen(s1);
	while (checkchar(s1[len - 1], set) && av < len)
		len--;
	str = malloc(sizeof(char) * (len - av + 1));
	if (!str)
		return (NULL);
	while (av < len)
		str[i++] = s1[av++];
	str[i] = '\0';
	return (str);
}
