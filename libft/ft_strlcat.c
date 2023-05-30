/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:47:30 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 14:34:01 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strlcat
** -------------------------------
** Description :
** Cette fonction concatène la chaîne de caractères src à la fin de la chaîne
** de caractères dst. La taille maximale de la chaîne dst est passée en argument
** avec le paramètre size.
**
** Paramètres :
** - dst : le buffer dans lequel la chaîne src doit être concaténée.
** - src : la chaîne de caractères à concaténer à la fin de dst.
** - size : la taille maximale de la chaîne dst, incluant l'espace pour le
** caractère nul de fin de chaîne.
**
** Retourne :
** - Le nombre total de caractères qui auraient été écrits dans dst si
** la taille avait été suffisante, sans compter le caractère nul de fin de
** chaîne.
**
** Notes :
** - Cette fonction garantit que la chaîne dst est toujours terminée par un
** caractère nul de fin de chaîne.
** - Si la chaîne dst est plus grande que size, la fonction tronquera src
** pour la faire rentrer dans dst, et ajoutera un caractère nul de fin de
** chaîne à la fin de dst.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && len + 1 < size)
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	dst[len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
