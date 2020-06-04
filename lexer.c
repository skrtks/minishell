/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/04 15:01:51 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

char	*extract_from_brackets(char *input, int *pos)
{
	char b_type;
	char *extr;
	int len;
	int i;

	b_type = input[*pos];
	*pos += 1;
	len = *pos;
	while (input[len] && (input[len] != b_type || (input[len] == b_type
			&& input[len - 1] == '\\')))
		len++;
	len -= *pos;

	extr = malloc(sizeof(char) * (len + 1));
	if (!extr)
		exit (1);
	i = *pos;
	while (input[i] && (input[i] != b_type || (input[i] == b_type
			&& input[i - 1] == '\\')))
	{
		extr[i - *pos] = input[i];
		i++;
	}
	extr[i - *pos] = '\0';
	*pos = i + 1;
	return (extr);
}

char	*extract_word(char *input, int *pos)
{
	char *extr;
	int len;
	int i;

	if ((input[*pos] == '\'' || input[*pos] == '\"') && input[*pos - 1] != '\\')
		return (extract_from_brackets(input, pos));
	len = *pos;
	while (input[len] != ' ' && input[len] != '\0' && !((input[len] == '\'' 
			|| input[len] == '\"') && input[len - 1] != '\\'))
		len++;
	len -= *pos;

	extr = malloc(sizeof(char) * (len + 1));
	if (!extr)
		exit (1);
	i = *pos;
	while (input[i] != ' ' && input[i] != '\0' && !((input[i] == '\'' 
			|| input[i] == '\"') && input[i - 1] != '\\'))
	{
		extr[i - *pos] = input[i];
		i++;
	}
	extr[i - *pos] = '\0';
	*pos = i;
	return (extr);
}

void	continue_populating(char *cmd, node_t *node)
{
	if (!ft_strncmp(cmd, ";", ft_strlen(cmd)))
		set_info(SEMICOLON, SYMBOL, node);
	else if (!ft_strncmp(cmd, "\'", ft_strlen(cmd)))
		set_info(APOSTROPHE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "\"", ft_strlen(cmd)))
		set_info(QUATATION_MARK, SYMBOL, node);
	else if (!ft_strncmp(cmd, "<", ft_strlen(cmd)))
		set_info(ARROW_LEFT, SYMBOL, node);
	else if (!ft_strncmp(cmd, ">", ft_strlen(cmd)))
		set_info(ARROW_RIGHT, SYMBOL, node);
	else if (!ft_strncmp(cmd, ">>", ft_strlen(cmd)))
		set_info(ARROW_DOUBLE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "|", ft_strlen(cmd)))
		set_info(PIPE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "$", ft_strlen(cmd)))
		set_info(DOLLAR, SYMBOL, node);
	else if (!ft_strncmp(cmd, "$?", ft_strlen(cmd)))
		set_info(DOLLAR_QUESTION, SYMBOL, node);
	else 
		set_info(OTHER, ARGUMENT, node);
}

void	populate_node(char *cmd, node_t *node)
{
	node->data = cmd;
	printf("[%s]", cmd);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		set_info(ECHO, COMMAND, node);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		set_info(CD, COMMAND, node);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		set_info(PWD, COMMAND, node);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		set_info(EXPORT, COMMAND, node);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		set_info(UNSET, COMMAND, node);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		set_info(ENV, COMMAND, node);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		set_info(EXIT, COMMAND, node);
	else if (!ft_strncmp(cmd, "-n", ft_strlen(cmd)))
		set_info(N, FLAG, node);
	else 
		continue_populating(cmd, node);
}

void	add_node(node_t **head, char *cmd)
{
	node_t *node;

	node = malloc(sizeof(node_t));
	if(!node)
		exit (1);
	node->next = NULL;
	populate_node(cmd, node);
	add_to_back(head, node);
}

node_t	*lexer(char *input)
{
	int i;
	char *cmd;
	node_t *head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			return head;
		cmd = extract_word(input, &i);
		add_node(&head, cmd);
		free (cmd);
	}
	return head;
}