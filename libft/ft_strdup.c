/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:40:24 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:57:16 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strdup
** ------------------------------
** Description :
**  Cette fonction alloue de la mémoire avec malloc() et copie la chaîne de
**  caractères passée en argument dans cette nouvelle zone mémoire. La chaîne
**  est copiée jusqu'au caractère nul inclus.
**
** Paramètres :
**  - s : la chaîne de caractères à dupliquer.
**
** Retourne :
**  - Un pointeur sur la nouvelle chaîne de caractères dupliquée, ou NULL en
**    cas d'erreur lors de l'allocation de mémoire.
**
** Notes :
**  - Il est de la responsabilité de l'appelant de libérer la mémoire allouée
**    pour la nouvelle chaîne de caractères lorsqu'elle n'est plus utilisée.
**  - La fonction ft_strlen() est utilisée pour déterminer la taille de la chaîne
**    de caractères à dupliquer.
**  - La nouvelle chaîne de caractères est toujours terminée
**    par un caractère nul.
*/

char	*ft_strdup(const char *s)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
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
