#include "../includes/minishell.h"

static int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	ft_count_quote(char *cmd)
{
	int		ret;
	int		i;
	char	first_quote;

	i = 0;
	ret = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			first_quote = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != first_quote)
				i++;
			ret += 2;
		}
		if (!cmd[i])
			break ;
		i++;
	}
	return (ret);
}

char	find_next_quote(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '"')
			return (cmd[i]);
		else if (cmd[i] == '\'')
			return (cmd[i]);
		i++;
	}
	return ('\0');
}

void	ft_unquote_error(char *cmd, int i)
{
	if (cmd[i] == '\0')
	{
		printf("minishell: error: quote not closed\n");
		hasta_la_vista(1);
	}
}

static void	init_unquote(int *i, int *j, char **ret, char *cmd)
{
	(*i) = 0;
	(*j) = 0;
	(*ret) = malloc(sizeof(char) * (ft_strlen(cmd) - ft_count_quote(cmd) + 1));
	if (!ret)
		hasta_la_vista(0);
}

static char	*ft_unquote_line(char *cmd)
{
	char	*ret;
	int		i;
	int		j;
	char	first_quotes;

	init_unquote(&i, &j, &ret, cmd);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			first_quotes = cmd[i++];
			while (cmd[i] != first_quotes)
			{
				ret[j++] = cmd[i++];
				ft_unquote_error(cmd, i);
			}
			i++;
			if (cmd[i] == '\0')
				break ;
		}
		ret[j++] = cmd[i++];
	}
	ret[j] = '\0';
	return (free(cmd), ret);
}

static char	**ft_unquote_node(char **cmd)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_tab_len(cmd) + 1));
	if (!ret)
		hasta_la_vista(0);
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
		if (lst->token->cmd)
			lst->token->cmd = ft_unquote_node(lst->token->cmd);
		lst = lst->next;
	}
}
