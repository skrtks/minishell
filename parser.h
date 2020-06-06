/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/06 16:33:34 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

void parse (t_node *cmd_list, t_node *env_list);

#endif
