/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/18 10:23:46 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

static char		*extract_from_brackets(const char *input, int *pos)
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

static char		*extract_word(char *input, int *pos)
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

static int		new_node(t_node **head, char *cmd)
{
	t_node *new_node;
	t_node *last;

	last = *head;
	if (!(new_node = malloc(sizeof(t_node))))
		return (1);
	populate_node(cmd, new_node);
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->previous = NULL;
		*head = new_node;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->previous = last;
	return (0);
}

t_node			*lexer(char *input)
{
	int		i;
	char	*cmd;
	t_node	*head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!(cmd = extract_word(input, &i)))
			return (NULL);
		if (cmd[0])
			if (new_node(&head, cmd))
				return (free_on_error(cmd));
		if (input[i] == ';')
		{
			if (new_node(&head, ";"))
				return (free_on_error(cmd));
			i++;
		}
		free(cmd);
	}
	return (head);
}
