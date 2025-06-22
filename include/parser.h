/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:36:26 by wxi               #+#    #+#             */
/*   Updated: 2025/06/22 17:53:20 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

typedef struct s_minishell t_minishell;
typedef struct s_token t_token;
typedef struct s_process t_process;
typedef enum e_redir_type t_redir_type;


/*Tokenization*/
int             tokenize_input(t_minishell *shell);
int				redir_checker(char *command);
int				token_checker(char *command);
void			free_tokenlst(t_minishell *shell);
int			    def_token(t_minishell *shell, int t_len, int t_start);
int			    def_special_token(t_minishell *shell, int *i);
char			*remove_outer_quotes(char *str);
int				validate_quotes(const char *input);
void			ms_token_add_back(t_token **token_lst, t_token *new_token);
int 			init_processlst(t_minishell *shell);
int				count_commands(t_token	**token);
int				count_pipes(t_minishell *shell);
void 			prt_cmds(t_process *process_lst);
char			*get_file(t_token *token);
void			print_process(t_minishell *shell);
int			    def_in_quotes(char c1, char c2, t_token	*new_token, char *sub);
char 			*def_expansion(t_token *token, t_minishell *shell);
int				find_n_def_redir(t_redir_type type, char *file, t_process *current_process, t_token **current_token);
int				fill_redirlst(t_redir_type type, char *file, t_process *current_process, t_token **current_token);
t_redir_type	get_redir_type(t_token *token);
void			init_val(int *n, char **a, char **b, char **c);

#endif