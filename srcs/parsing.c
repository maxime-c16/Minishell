/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/26 14:32:23 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	parsing(char *cmd, char **env)
{
	char	**token;

	if (!test_env(env))
		return (0);
	if (!split_env(env))
		return (0);
	if (!cmd)
		hasta_la_vista();
	token = ft_split_parsing(cmd, ' ');
	if (!token)
		hasta_la_vista();
	token = expand(token);
	ft_parse_and_insert(token, env);
	free(cmd);
  return (1);
}
