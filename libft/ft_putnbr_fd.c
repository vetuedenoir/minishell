/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:30 by kscordel          #+#    #+#             */
/*   Updated: 2022/11/15 16:58:03 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_putnbr_fd
** -------------------------------
** Description :
** Cette fonction affiche un nombre entier
** sur le descripteur de fichier spécifié.
** Elle gère également les nombres négatifs.
**
** Paramètres :
** - n : le nombre entier à afficher.
** - fd : le descripteur de fichier sur lequel afficher le nombre.
**
** Retourne :
** Aucune valeur de retour.
**
** Notes :
** - Cette fonction utilise une méthode récursive pour afficher le nombre.
** - Le nombre est d'abord converti en un long entier pour éviter les erreurs de
** débordement.
** - La fonction ft_putchar_fd() est appelée pour afficher chaque chiffre du
** nombre à partir de la droite. Le chiffre est converti en caractère en
** ajoutant 48 (le code ASCII pour le chiffre 0).
** - Si le nombre est négatif, un signe "-" est affiché avant le nombre.
*/

void	ft_putnbr_fd(int n, int fd)
{
	int long	nb;

	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd(nb % 10 + 48, fd);
}
