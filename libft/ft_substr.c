/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:15:48 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 16:44:21 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_substr
** ------------------------------
** Description :
** Cette fonction alloue et retourne une nouvelle chaîne de caractères,
** qui est une sous-chaîne de la chaîne s. La sous-chaîne commence à l'index
** start et a une longueur maximale de len caractères.
**
** Paramètres :
** - s : la chaîne source.
** - start : l'index de départ de la sous-chaîne.
** - len : la longueur maximale de la sous-chaîne.
**
** Retourne :
** - La sous-chaîne de s allant de start à start + len si elle est valide, ou
** NULL si l'allocation de mémoire a échoué.
**
** Notes :
** - Si start est supérieur à la longueur de s, la fonction retourne une
** chaîne vide.
** - Si la longueur de la sous-chaîne dépasse la fin de s, elle sera tronquée
** à la fin de s.
** - La fonction alloue de la mémoire pour la nouvelle chaîne de caractères
** retournée, il est donc important de la libérer avec free() une fois
** qu'elle n'est plus nécessaire.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;
	size_t		t;

	if (!s)
		return (NULL);
	t = ft_strlen(s);
	if (start > t)
		start = t;
	if ((size_t)start + len > t)
		len = t - start;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len && s[i + start])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
