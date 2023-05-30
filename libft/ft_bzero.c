/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:25:24 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 18:50:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_bzero
** -----------------------------
** Description :
**  Cette fonction remplit les n premiers octets de la zone mémoire pointée
**  par s avec des zéros. Elle est généralement utilisée pour initialiser une
**  zone mémoire avant d'y écrire des données.
**
** Paramètres :
**  - s : pointeur vers la zone mémoire à remplir avec des zéros.
**  - n : nombre d'octets à remplir avec des zéros.
**
** Retourne :
**  Rien.
**
** Remarques :
**  - Le comportement est indéfini si le pointeur s n'est pas valide.
**  - Si n vaut 0, cette fonction ne fait rien.
**  - La zone mémoire pointée par s doit être allouée
**    avant l'appel à cette fonction.
*/

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*buf;

	buf = s;
	i = 0;
	while (i < n)
	{
		buf[i] = '\0';
		i++;
	}
}
