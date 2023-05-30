/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:27 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 18:59:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_isascii
** --------------------------------
** Description :
**  Cette fonction vérifie si le caractère passé en argument est un code ASCII
**  valide. Les codes ASCII valides vont de 0 à 127 inclusivement.
**
** Paramètres :
**  - c : le caractère à tester.
**
** Retourne :
**  - 1 si le caractère est un code ASCII valide.
**  - 0 sinon.
*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
