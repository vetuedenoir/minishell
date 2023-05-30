/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:46 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:02:43 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_isdigit
** -------------------------------
** Description :
**  Cette fonction vérifie si le caractère passé en argument est un chiffre
**  décimal. Les chiffres décimaux valides vont de 0 à 9 inclusivement.
**
** Paramètres :
**  - c : le caractère à tester.
**
** Retourne :
**  - 1 si le caractère est un chiffre décimal valide.
**  - 0 sinon.
*/

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
