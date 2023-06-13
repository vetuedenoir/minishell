/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/02 17:41:59 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer lex;

	lex = NULL;
	if (argc != 1 || argv[1] != NULL)
		return (ft_printf("Erreur : Ce programme ne prend pas d argument\n"), 0);
	while (1)
	{
		lex = ft_lexer();
		if (lex != NULL)
		{
			parser(lex, envp);

		}
	}
	return (0);
}
