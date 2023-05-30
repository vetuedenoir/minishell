/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:17:21 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:03:59 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_isprint
** --------------------------------
** Description :
**  Cette fonction vérifie si le caractère passé en argument est un caractère
**  imprimable. Les caractères imprimables sont ceux qui peuvent être affichés
**  sur un écran ou une imprimante. Cette fonction retourne 1 pour les caractères
**  imprimables et 0 pour les autres.
**
** Paramètres :
**  - c : le caractère à tester.
**
** Retourne :
**  - 1 si le caractère est un caractère imprimable.
**  - 0 sinon.
**
** Remarques :
**  - Les caractères imprimables ont des codes ASCII compris
**    entre 32 et 126 inclusivement.
*/

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
