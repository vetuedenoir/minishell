/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:38:44 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/22 19:27:34 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    export(char *var, t_list **env)
{
    t_list  *node;

    if (!env || !var)
        return ;
    if (ft_strchr(var, '='))
    {
        node = ft_lstnew(var);
        if (node)
            ft_lstadd_back(env, node);    
    }
}

void    unset(char *var, t_list **env)
{
    char    *s;

    if (!env || !var)
    return ;
    while (*env)
    {
        s = (*char)(*env)->content;
        if (!ft_strncmp(var, s, ft_strlen(var) + 1))
        {
            free(s);
            (*env)->content = NULL;
        }
        *env = (*env)->next;
    }
}

void    echo(char **arg)
{
    int opt;
    int i;

    opt = 0;
    if (!arg)
        return ;
    if (ft_strncmp(arg[0], "-n", 3))
    {
        arg = arg[1];
        opt = 1;   
    }
    i = 0;
    while (arg)
        printf("%s", arg[i++]);
    if (!opt)
    write(1, "\n", 1);
}

void    env(t_list *env)
{
    while (env)
    {
        printf("%s\n", (*char)env->content);
        env = env->next;
    }
}