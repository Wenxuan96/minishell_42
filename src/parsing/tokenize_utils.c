/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 08:45:53 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/18 17:54:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_checker(char *command)
{
	if (ft_strncmp(">>", command, 2) == 0 && command[2] == '\0')
		return (OUTPUT_APPEND);
	else if (ft_strncmp(">", command, 1) == 0 && command[1] == '\0')
		return (OUTPUT);
	else if (ft_strncmp("<<", command, 2) == 0 && command[2] == '\0')
		return (HEREDOC);
	else if (ft_strncmp("<", command, 1) == 0 && command[1] == '\0')
		return (INPUT);
	return (CMD_NOTFOUND);
}

int	token_checker(char *command)
{
	if ((ft_strlen(command) == 1 && command[0] == '|'))
		return (PIPELINE);
	if (redir_checker(command) != CMD_NOTFOUND)
		return (REDIRECTION);
	return (WORD);
}

int	validate_1st_two_chr(char *str)
{
	if (ft_strchr("|&", str[0]) != NULL)
		return (ft_printf("1. synt err near token `newline'\n"), 0);
	if (ft_strlen(str) == 1 || ft_strlen(str) == 2)
	{
		if (ft_strchr("<|>&.", str[0]) != NULL)
		{
			if (str[1] == '\0' || (str[1] != '\0' && ft_strchr("<|>&.",
						str[1]) != NULL))
				return (ft_printf("2. synt err near token `newline'\n"), 0);
		}
	}
	else if (ft_strlen(str) >= 3)
	{
		if (str[0] == '\"' && (str[2] == '\"' || str[3] == '\"'))
		{
			if (str[1] == '.')
				return (ft_printf("3. synt err near token `newline'\n"), 0);
		}
	}
	return (1);
}

int	is_valid_heredoc(char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i + 1] == '\0')
		return (ft_printf("syntax error near token `newline'\n"), 0);
	else if (*i == start && str[*i + 1] != '\0')
		(*i)++;
	else if ((str[start] != str[*i] && ft_strchr("<|>&#", str[*i]) != NULL)
		|| (str[start] == str[*i] && (start + 1 != *i)))
		return (ft_printf("syntax error near token `newline'\n"), 0);
	else if (str[start] == str[*i] && (start + 1 == *i))
	{
		(*i)++;
		if (str[*i] == '\0')
			return (ft_printf("synt err near token `newline'\n"), 0);
		while (str[*i] != '\0')
		{
			if (str[*i] == ' ' || str[*i] == '\t')
				(*i)++;
			if (ft_strchr("<|>&#", str[*i]) != NULL)
				return (ft_printf("synt err near token `newline'\n"), 0);
			(*i)++;
		}
	}
	return (1);
}

int	is_valid_input(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 2 && ft_strchr("<|>&", str[0]) != NULL)
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] == ' ' || str[i] == '\t')
			{
				i++;
				continue ;
			}
			if (ft_strchr("|&", str[i]) != NULL && str[i + 1] == '\0')
				return (ft_printf("4. synt err near token `newline'\n"), 0);
			else if (str[i] == '<' || str[i] == '>')
			{
				if (!is_valid_heredoc(str, &i))
					return (0);
				continue ;
			}
			i++;
		}
	}
	return (i);
}
