#include "../minishell.h"

char**	beautiful(char **str, t_tool *data)
{
	char	**dup;
	int		t;
	int		i;

	t = 0;
	i = 0;
	if (str[0] && !strncmp(str[0], "ls", 3))
	{
		while (str[i++])
			t++;
		dup = ft_malloc(sizeof(char *) * (t + 2), data);
		if (!dup)
			return (str);
		i = 0;
		t = 0;
		while (str[i])
		{
			dup[t] = ft_strdup_g(str[i], data);
			if (!dup[t++])
				return (str);
			i++;
			if (i == 1)
				dup[t++] = ft_strdup_g("--color=always", data);
		}
		dup[t] = NULL;
		return (dup);
    }
	return (str);
}