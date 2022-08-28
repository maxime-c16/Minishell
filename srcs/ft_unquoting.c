#include "../includes/minishell.h"

static int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char	*ft_unquote_line(char *cmd)
{
	char	*ret;
	
}

static char	**ft_unquote_node(char **cmd)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * ft_tab_len(cmd) + 1);
	if (!ret)
		hasta_la_vista();
	while (cmd[i])
	{
		ret[i] = ft_unquote_line(cmd[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_unquoting(void)
{
	t_list	*lst;

	lst = _lst();
	while (lst)
	{
		lst->token->cmd = ft_unquote_node(lst->token->cmd);
		lst = lst->next;
	}
}