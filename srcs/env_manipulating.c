#include "../includes/minishell.h"

char	*lcd_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (NULL);
	while (s1[i] == s2[i])
		i++;
	if (i == ft_strlen(s1) && i ==ft_strlen(s2))
		return (s1);
	else
		return (NULL);
}

char	*get_value(char *key)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
//	dprintf(2, "searching value of %s\n", key);
	while (data->env[i].key)
	{
//		dprintf(2, "checking for %s\n", data->env[i].key);
		if (!ft_strncmp(key, data->env[i].key, ft_strlen(key)))
			return (data->env[i].value);
		i++;
	}
	return (NULL);
}
