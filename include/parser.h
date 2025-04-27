/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:36:26 by wxi               #+#    #+#             */
/*   Updated: 2025/04/27 21:37:16 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

typedef struct s_minishell t_minishell;
typedef struct s_token t_token;

/*Tokenization*/
void			tokenize_input(t_minishell *shell);
int				redir_checker(char *command);
int				token_checker(char *command);
void			free_tokenlst(t_minishell *shell);
void			def_token(t_minishell *shell, int t_len, int t_start);
void			def_special_token(t_minishell *shell, int *i);
char			*remove_outer_quotes(char *str);
int				validate_quotes(const char *input);
void			ms_token_add_back(t_token **token_lst, t_token *new_token);
int 			init_processlst(t_minishell *shell);

#endif