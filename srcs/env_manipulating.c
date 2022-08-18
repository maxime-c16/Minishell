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
	char	*str;
	t_data	*data;

	i = -1;
	data = _data();
	str = 0;
	while (str)
	{
		i++;
		str = lcd_strcmp(data->env[i].key, key);
	}
	return (data->env[i].value);
}
