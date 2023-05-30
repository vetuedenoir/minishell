/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:59:41 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 15:28:59 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strnstr
** ------------------------------
** Description :
** Cette fonction cherche la première occurrence de la sous-chaîne de
** caractères little dans la chaîne de caractères big. La recherche s'arrête
** après len caractères ont été examinés ou lorsque le caractère nul est
** atteint dans la chaîne big. Si la sous-chaîne little est trouvée, un
** pointeur vers le début de la sous-chaîne dans big est renvoyé. Sinon,
** la fonction renvoie NULL.
**
** Paramètres :
** - big : la chaîne de caractères dans laquelle chercher la sous-chaîne.
** - little : la sous-chaîne de caractères à chercher dans big.
** - len : le nombre maximal de caractères à examiner dans big.
**
** Retourne :
** - Un pointeur vers le début de la sous-chaîne dans big si elle est trouvée.
** - NULL si la sous-chaîne n'est pas trouvée.
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j]
			&& little[j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
