/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/21 15:02:58 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Step 1: read from stdinput and save the input
Signal is needed to continue reading user input
if signal is received, read and malloc stdin
*/

// static void prt_input(char **input_arr)
// {
// 	int	i;
	
// 	i = 0;
// 	while (input_arr[i])
// 		ft_printf("current splitted input is: %s\n", input_arr[i++]);
// }

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
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str)
	{ /*When ctrl+D is pressed, break the loop, clean memory and exit*/
		ft_exit(shell, "exit");
		return(MS_EXIT_SUCCESS);
	}
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	// shell->input_arr = ft_split(shell->input_str, ' ');
	// prt_input(shell->input_arr); /*To test what inputs are there*/
	quote_manager(shell);
	return(MS_EXIT_SUCCESS);
}

int redir_checker(char *command)
{
	if (ft_strncmp(">>", command, 2) == 0)
		return (OUTPUT_APPEND);
	else if (ft_strncmp(">", command, 1) == 0)
		return (OUTPUT);
	else if (ft_strncmp("<<", command, 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp("<", command, 1) == 0)
		return (INPUT);
	return (MS_TARGET_NOT_FOUND);
}

int token_checker(t_minishell *shell, char *command)
{
	int i;

	i = 0;
	while (shell->std_commands[i])
	{
		if (ft_strncmp(shell->std_commands[i++], command, ft_strlen(command)) != 0)
			ft_printf("%s: command not found", command);
		return (MS_TARGET_NOT_FOUND);
	}
	i = 0;
	while (shell->system_commands[i])
	{
		if (ft_strncmp(shell->system_commands[i++], command, ft_strlen(command)) == 0)
			return (SYSTEM_COMMAND);
	}
	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strncmp(shell->buildin_commands[i++], command, ft_strlen(command)) == 0)
			return (BUILDIN_COMMAND);
	}
	if (redir_checker(command) != MS_TARGET_NOT_FOUND)
		return (REDIRECTION);
	return (MS_EXIT_SUCCESS);
}

t_token	*def_token(t_minishell *shell, int t_len)
{
	t_token	*new_token;
	
	new_token = new_token_lst(shell->token_val);
	new_token->in_quotes = 127; //write check quote()
	new_token->is_dynamic = 127; //write check dynamic()
	new_token->len = t_len;
	new_token->start = shell->token_val;
	new_token->type = token_checker(shell, shell->token_val);
	new_token->next_token = NULL;
	return (new_token);
}

void add_token_to_list(t_minishell *shell, t_token *new_token)
{
	(void)shell;
	(void)new_token;
}

void tokenize_input(t_minishell *shell)
{
	int i = 0;
	int start = 0;
	int in_quote = 0;
	char quote_char = 0;
	int	len;
	t_token *new_token;

	while (shell->input_str[i])
	{
		if (!in_quote && (shell->input_str[i] == '\'' || shell->input_str[i] == '\"'))
		{
			// Entering quote
			in_quote = 1;
			quote_char = shell->input_str[i];
			i++;
		}
		else if (in_quote && shell->input_str[i] == quote_char)
		{
			// Exiting quote
			in_quote = 0;
			i++;
		}
		else if (!in_quote && (shell->input_str[i] == ' ' || shell->input_str[i + 1] == '\0'))
		{
			// Found end of a token (space or end of string)
			len = i - start;
			if (shell->input_str[i + 1] == '\0')
				len++; // Include last char

			new_token = def_token(shell, len);
			add_token_to_list(shell, new_token); // <--- your function to add to linked list

			// Skip spaces
			while (shell->input_str[i] == ' ')
				i++;
			start = i;
		}
		else
			i++;
	}
}

// void	tokenize_input(t_minishell *shell, char	**input_arr)
// {
// 	int				i;
// 	t_token_type 	token_type;
	
// 	i = 0;
// 	while (input_arr[i])
// 	{
// 		//need a redir edge case checker function/logic here, read bash manual
// 		if (ft_strncmp("|", input_arr[i], 1) == 0)//pay attention if | is in double quote
// 			def_token(input_arr[i], PIPELINE);
// 		else if (redir_checker(input_arr[i]) != MS_TARGET_NOT_FOUND)
// 			def_token(input_arr[i], REDIRECTION);
// 		else if ((token_type = command_checker(shell, input_arr[i])) != MS_TARGET_NOT_FOUND)
// 			def_token(input_arr[i], token_type);
// 		else
// 			def_token(input_arr[i], WORD);
// 	}
// }

