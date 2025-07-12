/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:52:12 by wxi               #+#    #+#             */
/*   Updated: 2025/07/12 12:15:45 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	get_redir_type(t_token *token)
{
	t_redir_type	type;

	type = NONE;
	if (ft_strcmp(token->token_val, ">") == 0 && token->token_val[1] == '\0')
		type = OUTPUT;
	else if (ft_strcmp(token->token_val, "<") == 0
		&& token->token_val[1] == '\0')
		type = INPUT;
	else if (ft_strcmp(token->token_val, ">>") == 0
		&& token->token_val[2] == '\0')
		type = OUTPUT_APPEND;
	else if (ft_strcmp(token->token_val, "<<") == 0
		&& token->token_val[2] == '\0')
		type = HEREDOC;
	return (type);
}

int	fill_redirlst(t_redir_type type, char *file,
		t_process *current_process, t_token **current_token)
{
	if (!file)
		return (0);
	if (!current_process->redirections)
	{
		current_process->redirections = new_redir_lst(type, file);
		if (!current_process->redirections)
			return (0);
	}
	else
		redir_lst_add_back(new_redir_lst(type, file),
			&current_process->redirections);
	*current_token = (*current_token)->next_token;
	if ((*current_token)->next_token)
		*current_token = (*current_token)->next_token;
	return (1);
}

int	find_n_def_redir(t_redir_type type, char *file,
		t_process *current_process, t_token **current_token)
{
	while (*current_token != NULL && (*current_token)->type != PIPELINE)
	{
		if ((*current_token)->type == REDIRECTION)
		{
			type = get_redir_type(*current_token);
			file = ft_strdup(get_file(*current_token));
			if (!fill_redirlst(type, file, current_process, current_token))
				return (0);
		}
		else
			*current_token = (*current_token)->next_token;
	}
	if (*current_token && (*current_token)->type == PIPELINE)
		*current_token = (*current_token)->next_token;
	return (1);
}

void	expand_n_skip(t_token	**token, t_minishell *shell)
{
	char	*new_val;

	if (get_redir_type(*token) == HEREDOC)
	{
		(*token) = (*token)->next_token;
		if ((*token)->in_quotes == true)
			shell->heredoc_inquote = true;
	}
	else
	{
		(*token) = (*token)->next_token;
		if (*token != NULL && (*token)->token_val[0] == '$')
		{
			new_val = def_expansion(*token, shell);
			free((*token)->token_val);
			(*token)->token_val = new_val;
		}
	}
	if (*token != NULL)
		(*token) = (*token)->next_token;
}
