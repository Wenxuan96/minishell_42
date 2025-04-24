/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/24 13:24:50 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prt_tokenlst(t_minishell *shell)
{
	t_token *current;

	current = shell->token_list;
	if (!current)
		return ;
	ft_printf("current tokens are:");
	while (current != NULL)
	{
		ft_printf(" [%s]", current->token_val);
		current = current->next_token;
	}
	ft_printf(".\n");
}

int validate_quotes(const char *input)
{
	char quote = '\0';
	for (int i = 0; input[i]; i++)
	{
		if ((input[i] == '"' || input[i] == '\'') && quote == '\0')
			quote = input[i];
		else if (input[i] == quote)
			quote = '\0';
	}
	return (quote == '\0');
}

// Helper to skip spaces
static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}

void free_tokenlst(t_minishell *shell)
{
	t_token	*current;

	if (!shell->token_list)
		return ;
	while (shell->token_list)
	{
		current = shell->token_list->next_token;
		free(shell->token_list->token_val);
		free(shell->token_list);
		shell->token_list = current;
	}
	shell->token_list = NULL;
}

void tokenize_input(t_minishell *shell)
{
	int		i = 0;
	int		start = 0;
	char	quote_char = '\0';

	if (!validate_quotes(shell->input_str))
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return;
	}

	while (shell->input_str[i])
	{
		if ((quote_char == '\0') && (shell->input_str[i] == '\''
			|| shell->input_str[i] == '\"'))
			quote_char = shell->input_str[i];
		else if (quote_char != '\0' && shell->input_str[i] == quote_char)
			quote_char = '\0';
		else if (quote_char == '\0' && (ft_strchr(" \t|<>", shell->input_str[i]) != NULL))
		{
			if (i != start)
				def_token(shell, i - start, start);
			while (ft_strchr(" \t|<>", shell->input_str[i]) != NULL)
			{
				def_special_token(shell, &i);
				skip_whitespace(shell->input_str, &i);
			}
			start = i;
			continue;
		}
		i++;
	}
	if (i != start)
		def_token(shell, i - start, start);
}

int	read_input(int argc, t_minishell *shell)
{
	int	init;
	int	i;
	
	i = 0;
	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	free_tokenlst(shell);
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str)
	{ /*When ctrl+D is pressed, break the loop, clean memory and exit*/
		ft_exit(shell, "exit");
		return(MS_EXIT_SUCCESS);
	}
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	tokenize_input(shell);
	prt_tokenlst(shell);
	return(MS_EXIT_SUCCESS);
}
