/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/17 20:04:11 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer *lex;
	t_cmds	*cmd;
	(void)envp;

	lex = NULL;
	if (argc != 1 || argv[1] != NULL)
		return (ft_printf("Erreur : Ce programme ne prend pas d argument\n"), 0);
	while (1)
	{
		lex = ft_lexer();
		if (lex != NULL)
		{
			printlex(lex);
			cmd = parser(lex, envp); // reste a verifier le chemin dans le path
			print_cmd(cmd); // pour voir ce que c a sort
		//	clear_cmd(&cmd);
		}
	}
	return (0);
}
