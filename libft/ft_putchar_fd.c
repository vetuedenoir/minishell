/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:53:58 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:34:38 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** Nom de la fonction : ft_putchar_fd
** ----------------------------------
** Description :
** Cette fonction écrit un caractère sur le flux de sortie spécifié.
**
** Paramètres :
** - c : le caractère à écrire.
** - fd : le descripteur de fichier sur lequel écrire le caractère.
**
** Retourne :
** Rien.
**
** Notes :
** - La fonction write est utilisée pour écrire le caractère
**   sur le flux de sortie spécifié par le descripteur de fichier fd.
** - Le caractère est passé en référence à la fonction write,
**   avec une taille de 1 octet.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
