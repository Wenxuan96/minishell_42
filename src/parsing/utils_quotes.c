/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:42:08 by wxi               #+#    #+#             */
/*   Updated: 2025/07/14 17:03:50 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	detect_outer_quote_type(t_quote_context *ctx, 
		const char *s, size_t start, size_t end)
{
	if ((s[start] == '\'' && s[end] == '\'') || (s[start] == '"' && s[end] == '"'))
	{
		ctx->has_quotes = true;
		if (s[start] == '"')
			ctx->double_quoted = true;
		else
			ctx->single_quoted = true;
	}
}

t_quote_context	*get_outer_quote_context(const char *s)
{
	t_quote_context	*ctx;
	size_t			start;
	size_t			end;

	start = 0;
	end = strlen(s);
	ctx = malloc(sizeof(t_quote_context));
	if (!ctx)
		return (NULL);
	ft_memset(ctx, 0, sizeof(t_quote_context));
	if (end == 0)
		return (ctx);
	end--;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	while (end > start && (s[end] == ' ' || s[end] == '\t'))
		end--;
	detect_outer_quote_type(ctx, s, start, end);
	return (ctx);
}

bool	should_skip_quote(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == '\0')
		{
			*quote = c;
			return true;
		}
		else if (c == *quote)
		{
			*quote = '\0';
			return true;
		}
	}
	return false;
}

char *collapse_quotes(const char *src)
{
	char	*result;
	size_t	i = 0;
	size_t	j = 0;
	char	quote;

	result = malloc(strlen(src) + 1);
	i = 0;
	j = 0;
	quote = '\0';
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (should_skip_quote(src[i], &quote))
		{
			i++;
			continue;
		}
		result[j++] = src[i++];
	}
	result[j] = '\0';
	return (result);
}

int	def_in_quotes(t_token	*new_token, char *sub)
{
	t_quote_context *ctx;

	ctx = get_outer_quote_context(sub);
	new_token->in_quotes = ctx->has_quotes;
	new_token->double_quoted = ctx->double_quoted;
	free(new_token->token_val);
	new_token->token_val = NULL;
	new_token->token_val = collapse_quotes(sub);
	if (!new_token->token_val)
		return (0);
	printf("double_quoted = %s\n", new_token->double_quoted ? "true" : "false");
	printf("in_quotes = %s\n", new_token->in_quotes ? "true" : "false");
	free(ctx);
	return (1);
}
