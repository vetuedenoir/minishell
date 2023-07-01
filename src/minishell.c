/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:03:05 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/29 14:03:40 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*g_garbage_collector = NULL;

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer *lex;
	t_tool	data;

	if (argc != 1 || argv[1] != NULL)
		return (ft_printf("Erreur : Ce programme ne prend pas d argument\n"), 0);
	while (1)
	{
		lex = ft_lexer(&data);
		if (lex != NULL)
		{
			printlex(lex);
			data.cmds = parser(lex, envp);
			check_path(&data.cmds, envp);
			print_cmd(data.cmds); // pour voir ce que c a sort
			free_garbage();	
		}
	}
	return (0);
}
