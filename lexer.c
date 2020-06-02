/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaas  #+#    #+#                 */
/*   Updated: 2020/06/02 15:20:49 by samkortekaas  ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

char *extract_cmd(char *input, int *pos)
{
	char *extr;
	int len;
	int i;

	len = *pos;
	while (input[len] != ' ' && input[len] != '\0')
		len++;
	len -= *pos;

	extr = malloc(sizeof(char) * (len + 1));
	if (!extr)
		exit (1);
	i = *pos;
	while (input[i] != ' ' && input[i] != '\0')
	{
		extr[i - *pos] = input[i];
		i++;
	}
	extr[i - *pos] = '\0';
	*pos = i;
	return (extr);
}

void populate_node(char *cmd, node_t *node)
{
	node->data = cmd;
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
	{
		node->command = PWD;
		node->type = COMMAND;
	}
	else
	{
		node->command = OTHER;
		node->type = ARGUMENT;
	}
}

void add_to_back(node_t **head, node_t *node)
{
	node_t *ptr;

	if (!(*head))
		(*head) = node;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}

void add_node(node_t **head, char *cmd)
{
	node_t *node;

	node = malloc(sizeof(node_t));
	if(!node)
		exit (1);
	node->next = NULL;
	populate_node(cmd, node);
	add_to_back(head, node);
}

node_t *lexer(char *input)
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
		cmd = extract_cmd(input, &i);
		add_node(&head, cmd);
	}
	return head;
}