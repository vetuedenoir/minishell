/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:54:53 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:39:13 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_putstr_fd
** -------------------------------
** Description :
** Cette fonction envoie une chaîne de caractères à l'emplacement spécifié
** par le descripteur de fichier passé en argument.
**
** Paramètres :
** - s : la chaîne de caractères à envoyer.
** - fd : le descripteur de fichier de destination.
**
** Retourne :
** - rien
**
** Notes :
** - Si la chaîne de caractères est NULL, la fonction ne fait rien.
** - La fonction utilise la fonction système write pour écrire les caractères
** de la chaîne dans le fichier.
*/

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
