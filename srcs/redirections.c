/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:50:35 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/20 23:18:38 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_redirections(t_list *lst)
{
	int		i;
	int		j;
	int		k;
	char	**token;
	t_list	*tmp;

	i = *lst->help->l;
	j = *lst->help->m;
	k = *lst->help->n;
	token = lst->help->token;
	if (j == 1)
		lst->token->type = 0;
	else if (ft_strncmp(token[i - 1], "|", 1) == 0)
		lst->token->type = PIPE;
	else
		lst->token->type = 0;
	if (!token[i])
		lst->token->cmd = malloc(sizeof(char *) * (i - j + 2));
	else
		lst->token->cmd = malloc(sizeof(char *) * (i - j + 1));
	while (j < i)
	{
		lst->token->cmd[k] = ft_strdup(token[j - 1]);
		printf("%s\n", lst->token->cmd[k]);
		j++;
		k++;
	}
	if (!token[i])
	{
		lst->token->cmd[k] = ft_strdup(token[j - 1]);
		printf("%s\n", lst->token->cmd[k]);
		lst->token->cmd[k + 1] = NULL;
	}
	else
		lst->token->cmd[k] = NULL;
	j = i;
	if (!token[i])
		return (lst);
	tmp = ft_lstnew(NULL);
	tmp->token = malloc(sizeof(t_token));
	tmp->token->cmd = NULL;
	ft_lstadd_back(&lst, tmp);
	return (lst);
}
