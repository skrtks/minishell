/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/15 13:50:36 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H
#include "lexer.h"

t_node	*cd(t_node *node, t_env *env_list);
char	*get_homedir(t_env *env_list);

#endif