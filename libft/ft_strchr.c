/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:49:23 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:54:37 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strchr
** ------------------------------
** Description :
** Cette fonction cherche la première occurrence d'un caractère 'c'
** dans une chaîne de caractères 's'. Si le caractère est trouvé, un
** pointeur sur la position du caractère dans la chaîne est renvoyé.
** Sinon, si le caractère n'est pas trouvé, un pointeur NULL est renvoyé.
**
** Paramètres :
** - s : La chaîne de caractères dans laquelle chercher le caractère 'c'.
** - c : Le caractère à chercher dans la chaîne de caractères 's'.
**
** Retourne :
** - Un pointeur sur la position du caractère 'c' dans la chaîne de
** caractères 's' si le caractère est trouvé.
** - Un pointeur NULL si le caractère 'c' n'est pas trouvé dans la chaîne.
**
** Notes :
** - Cette fonction renvoie également un pointeur sur la fin de la chaîne
** 's' si le caractère recherché est le caractère nul '\0'.
** - Cette fonction prend en charge les chaînes de caractères qui se
** terminent par un caractère nul '\0'.
*/

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if (c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}
