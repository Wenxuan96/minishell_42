// int	export_builtin(t_process *process, t_minishell *shell)
// {
// 	char			**split_vars;
// 	int				found;
// 	t_environment	*current;
// 	int				i;
// 	char			*temp;
// 	size_t			var_len;

// 	i = 1;
// 	var_len = 0;
// 	current = shell->env_list;
// 	if (process->command_arguments[1] == NULL)
// 	{
// 		prt_env_lst(shell->env_list);
// 		return (1);
// 	}
// 	while (process->command_arguments[i] != NULL)
// 	{
// 		split_vars = ft_split_env(process->command_arguments[i], '=');
// 		if (!split_vars || !split_vars[0])
// 		{
// 			display_shell_error(process, "export: not a valid identifier",
// 				EXEC_FAILURE);
// 			i++;
// 			continue ;
// 		}
// 		var_len = ft_strlen(split_vars[0]);
// 		if (var_len > 0 && (split_vars[0][0] == '\'' || split_vars[0][0] == '\"'
// 			|| split_vars[0][var_len - 1] == '\'' || split_vars[0][var_len
// 			- 1] == '\"'))
// 		{
// 			temp = split_vars[0];
// 			split_vars[0] = ft_trim_quotes(split_vars[0]);
// 			free(temp);
// 		}
// 		if (split_vars[1] && (split_vars[1][0] == '\''
// 				|| split_vars[1][0] == '\"'))
// 		{
// 			temp = split_vars[1];
// 			split_vars[1] = ft_trim_quotes(split_vars[1]);
// 			free(temp);
// 		}
// 		if (is_valid_env(split_vars[0]))
// 		{
// 			found = 0;
// 			current = shell->env_list;
// 			while (current != NULL)
// 			{
// 				if (ft_strcmp(current->env_var, split_vars[0]) == 0)
// 				{
// 					free(current->value);
// 					if (split_vars[1] != NULL)
// 						current->value = ft_strdup(split_vars[1]);
// 					else
// 						current->value = NULL;
// 					found = 1;
// 					break ;
// 				}
// 				current = current->next_env_var;
// 			}
// 			if (found == 0)
// 			{
// 				ft_var_lstadd_back(&shell->env_list,
// 					ft_new_var_lst(split_vars[0], split_vars[1]));
// 			}
// 		}
// 		else
// 			display_shell_error(process, "export: not a valid identifier",
// 				EXEC_FAILURE);
// 		free_2darray(split_vars);
// 		i++;
// 	}
// 	return (1);
// }