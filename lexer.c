/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/09 16:39:49 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

char	*extract_from_brackets(char *input, int *pos)
{
	char	b_type;
	char	*extr;
	int		len;
	int		i;

	b_type = input[*pos];
	*pos += 1;
	len = *pos;
	while (input[len] && (input[len] != b_type || (input[len] == b_type
			&& input[len - 1] == '\\')))
		len++;
	len -= *pos;
	extr = malloc(sizeof(char) * (len + 1));
	if (!extr)
		return (NULL);
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
	char	*extr;
	int		len;
	int		i;

	if ((input[*pos] == '\'' || input[*pos] == '\"') && input[*pos - 1] != '\\')
		return (extract_from_brackets(input, pos));
	len = *pos;
	while (input[len] != ' ' && input[len] != '\0' && !((input[len] == '\'' 
			|| input[len] == '\"') && input[len - 1] != '\\') && input[len] != ';')
		len++;
	len -= *pos;
	extr = malloc(sizeof(char) * (len + 1));
	if (!extr)
		return (NULL);
	i = *pos;
	while (input[i] != ' ' && input[i] != '\0' && !((input[i] == '\'' 
			|| input[i] == '\"') && input[i - 1] != '\\') && input[i] != ';')
	{
		extr[i - *pos] = input[i];
		i++;
	}
	extr[i - *pos] = '\0';
	*pos = i;
	return (extr);
}

void	continue_populating(char *cmd, t_node *node)
{
	if (!ft_strncmp(cmd, ";", 1))
		set_info(SEMICOLON, SYMBOL, node);
	else if (!ft_strncmp(cmd, "\'", 1))
		set_info(APOSTROPHE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "\"", 1))
		set_info(QUATATION_MARK, SYMBOL, node);
	else if (!ft_strncmp(cmd, "<", 1))
		set_info(ARROW_LEFT, SYMBOL, node);
	else if (!ft_strncmp(cmd, ">", 1))
		set_info(ARROW_RIGHT, SYMBOL, node);
	else if (!ft_strncmp(cmd, ">>", 2))
		set_info(ARROW_DOUBLE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "|", 1))
		set_info(PIPE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "$", 1))
		set_info(DOLLAR, SYMBOL, node);
	else if (!ft_strncmp(cmd, "$?", 2))
		set_info(DOLLAR_QUESTION, SYMBOL, node);
	else
		set_info(OTHER, ARGUMENT, node);
}

int	populate_node(char *cmd, t_node *node)
{
	node->data = ft_strdup(cmd);
	if (!node->data)
    {
    	ft_printf("Error parsing command, try again.\n");
    	return (1);
    }
	if (!ft_strncmp(cmd, "echo", 4))
		set_info(ECHO, COMMAND, node);
	else if (!ft_strncmp(cmd, "cd", 2))
		set_info(CD, COMMAND, node);
	else if (!ft_strncmp(cmd, "pwd", 3))
		set_info(PWD, COMMAND, node);
	else if (!ft_strncmp(cmd, "export", 6))
		set_info(EXPORT, COMMAND, node);
	else if (!ft_strncmp(cmd, "unset", 5))
		set_info(UNSET, COMMAND, node);
	else if (!ft_strncmp(cmd, "env", 3))
		set_info(ENV, COMMAND, node);
	else if (!ft_strncmp(cmd, "exit", 4))
		set_info(EXIT, COMMAND, node);
	else if (!ft_strncmp(cmd, "-n", 2))
		set_info(N, FLAG, node);
	else
		continue_populating(cmd, node);
	return (0);
}

int	add_node(t_node **head, char *cmd)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (1);
	node->next = NULL;
	if (populate_node(cmd, node))
		return (1);
	add_to_back(head, node);
	return (0);
}

t_node	*lexer(char *input)
{
	int		i;
	char	*cmd;
	t_node	*head;

	i = 0;
	head = NULL;
	if (input[i] == '\0')
		return (head);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			return (head);
		cmd = extract_word(input, &i);
		if (!cmd)
			return (NULL);
		if (cmd[0])
			if (add_node(&head, cmd))
			{
				free (cmd);
				return (NULL);
			}
		if (input[i] == ';')
		{
			if (add_node(&head, ";"))
			{
				free (cmd);
				return (NULL);
			}
			i++;
		}
		free(cmd);
	}
	free(input);
	return (head);
}
