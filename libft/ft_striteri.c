/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:52:28 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 12:43:38 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

/*
** Nom de la fonction : ft_striteri
** -------------------------------
** Description :
** Applique une fonction à chaque caractère de la chaîne de caractères passée
** en paramètre, en précisant l'indice de chaque caractère.
**
** Paramètres :
** - s : la chaîne de caractères à parcourir.
** - f : le pointeur de fonction qui prend en paramètres un unsigned int et
** un char* et ne retourne rien. Cette fonction sera appliquée à chaque
** caractère de la chaîne, en précisant l'indice de chaque caractère.
**
** Retourne : rien.
**
** Notes :
** - Cette fonction est similaire à la fonction ft_striter, mais ajoute un
** paramètre qui permet de préciser l'indice de chaque caractère.
** - Si la chaîne de caractères ou le pointeur de fonction est NULL, cette
** fonction ne fait rien.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!f || !s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
