/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_get_env_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:13:36 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/09 08:41:36 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **execve_get_envvars(t_minishell *shell)
{
    char    **envvars;
    int     num_vars;
    int     i;
    t_environment   *var_list;
    size_t          total_len;

    i = 0;
    total_len = 0;
    num_vars = 0;
    var_list = shell->env_list;
    while (var_list != NULL)
    {
        if (var_list->value != NULL)
        {
            num_vars++;
        }
        var_list = var_list->next_env_var;         
    }
    envvars = (char **)malloc((num_vars + 1) * sizeof(char *));
    var_list = shell->env_list;
    while (var_list != NULL)
    {
        if (var_list->value != NULL)
        {
            total_len = ft_strlen(var_list->env_var) + ft_strlen(var_list->value) + 2;
            envvars[i] = (char *)malloc(total_len * sizeof(char));
            ft_strlcpy(envvars[i], var_list->env_var, total_len);
            ft_strlcat(envvars[i], "=", total_len);
            ft_strlcat(envvars[i], var_list->value, total_len);
            // printf("%s\n", envvars[i]);
        }
        var_list = var_list->next_env_var;
        i++; 
    }
    envvars[i] = NULL;
    return (envvars);
}

