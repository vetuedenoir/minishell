/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:54:21 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 14:40:44 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strlcpy
** -------------------------------
** Description :
** Cette fonction copie une chaîne de caractères src dans dest. La chaîne
** de caractères src est copiée dans dest jusqu'à ce qu'un caractère nul soit
** trouvé ou que n caractères aient été copiés. La chaîne de destination est
** toujours terminée par un caractère nul.
**
** Paramètres :
** - dest : un pointeur vers la chaîne de destination.
** - src : la chaîne source à copier.
** - n : la taille du tampon de destination.
**
** Retourne :
** - La longueur de la chaîne source.
**
** Notes :
** - Si la taille de la chaîne destination est égale à zéro, la fonction ne
** copie rien et retourne simplement la longueur de la chaîne source.
** - La fonction ne garantit pas que la chaîne destination est toujours
** terminée par un caractère nul si n est inférieur ou égal à la longueur
** de la chaîne source.
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (src[i] && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
