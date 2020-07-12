/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 11:40:54 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/12 10:39:18 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"
# include "libft/libft.h"
# include "builtins/builtins.h"

/* check.c */
int		check_cmd_list(t_node *cmd_list);

/* execute.c */
t_node	*execute(t_node *node, t_env *env_list);

/* check_path.c */
int		check_for_path(char **cmd, t_env *env_list);

/* expand.c */
char	*expand(char *word, t_env *envlist, int in_quotes);

char	*check_spec_char(const char *str, int c);

int		add_export_node(t_env **head, char *export_var);
int		add_env_node(t_env **head, char *env_var);
int		check_cmd_list(t_node *cmd_list);
int		check_equal_sign(const char *str);
int		compare_data(const char *str1, const char *str2);
int		compare_exp(const char *input, const char *in_list);
int		populate_node(char *cmd, t_node *node);
int		set_metachar(t_node **head, char *input, int *pos);

void	error_message(void);
t_node	*free_on_error(char *cmd, t_node *cmd_list);

void	add_to_back_env(t_env **head, t_env *node);
void	free_cmdlist(t_node **head);
void	free_envlist(t_env **head);

char	*get_env_string(t_env *env_list, int *id_len, char *id, char *exp);
char	*get_exp(char *word, int i, t_env *env_list, int *id_len);
char	*update_str(char *word, int i, char *exp, int id_len);
char	**free_array(char **array);

int check_cmd_list(t_node *cmd_list); // weg?
char *clean_and_free(char *s1, char *s2, char *s3);
int check_invalid_id(char *str);

#endif


//echo hoi | cat -e ; cd libft ' pwd