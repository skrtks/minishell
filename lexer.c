/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/11 09:17:55 by merelmourik   ########   odam.nl         */
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
	while (input[len] && (input[len] != b_type || (input[len] == b_type\
			&& input[len - 1] == '\\')))
		len++;
	len -= *pos;
	extr = malloc(sizeof(char) * (len + 1));
	if (!extr)
		return (NULL);
	i = *pos;
	while (input[i] && (input[i] != b_type || (input[i] == b_type\
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
	while (input[len] != ' ' && input[len] != '\0' && !((input[len] == '\'' ||\
		input[len] == '\"') && input[len - 1] != '\\') && input[len] != ';')
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
	if (input[i] == '\0')		//deze kan weg?
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
				free(cmd);			//koppelen aan de free functie
				return (NULL);
			}
		if (input[i] == ';')
			if (add_node(&head, ";"))
			{
				free(cmd);
				return (NULL);
			}
		i++;
		free(cmd);
	}
	return (head);
}
