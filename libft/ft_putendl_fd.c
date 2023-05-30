/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:55:19 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:37:49 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_putendl_fd
** ----------------------------------
** Description :
** Cette fonction écrit la chaîne de caractères 's' suivie d'un caractère
** de fin de ligne ('\n') dans le fichier correspondant au descripteur de
** fichier 'fd'.
**
** Paramètres :
** - s : la chaîne de caractères à écrire.
** - fd : le descripteur de fichier dans lequel écrire.
**
** Retourne :
** - rien.
**
** Notes :
** - Si la chaîne de caractères 's' est NULL, rien n'est écrit.
** - Cette fonction utilise la fonction ft_strlen pour déterminer la longueur
** de la chaîne de caractères à écrire.
*/

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
