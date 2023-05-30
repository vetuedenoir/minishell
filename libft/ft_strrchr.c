/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:22:15 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 16:30:06 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strrchr
** -------------------------------
** Description :
** Cette fonction cherche la dernière occurrence du caractère c dans la chaîne
** s. La recherche commence par la fin de la chaîne s et se poursuit vers le
** début jusqu'à ce que le caractère c soit trouvé ou que la fin de la chaîne
** s soit atteinte.
**
** Paramètres :
** - s : la chaîne de caractères dans laquelle chercher.
** - c : le caractère à chercher.
**
** Retourne :
** - Un pointeur vers la dernière occurrence du caractère c dans la chaîne s,
** ou NULL si le caractère n'est pas présent dans la chaîne.
**
** Notes :
** - Le caractère de fin de chaîne ('\0') est considéré comme faisant partie
** de la chaîne s.
*/

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i--;
	}
	return (NULL);
}
