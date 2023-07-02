
#include "../minishell.h"

static int	lents(const char *str, char c)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (str[++i])
	{
		if (str[i] == 34)
		{
			while(str[++i] != 34)
				;
		}
		if (str[i] == 39)
		{
			while(str[++i] != 39)
				;
		}
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			t++;
	}
	return (t);
}

int    ft_verif_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == 34)
		{
			i++;
			while(s[i] != 34 && s[i] != 0)
				i++;
			if (s[i] == 0)
				return (0);
		}
		else if (s[i] == 39)
		{
			i++;
			while(s[i] != 39 && s[i] != 0)
				i++;
			if (s[i] == 0)
				return (0);
		}
	}
	return (1);
}

static char	*cpy_tsx(const char *s, int index, char c)
{
	int		i;
	int		t;
	char	*str;

	i = index;
	t = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == 34)
		{
			while (s[++i] != 34)
				t++;
			t++;
		}
		if (s[i] == 39)
		{
			while (s[++i] != 39)
				t++;
			t++;
		}
		i++;
		t++;
	}
	str = ft_malloc(sizeof(char) * (t + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[index] != c && s[index])
	{
		if (s[index] == 34)
		{
			while (s[++index] != 34)
				str[i++] = s[index - 1];
			str[i++] = s[index - 1];
		}
		if (s[index] == 39)
		{
			while (s[++index] != 39)
				str[i++] = s[index - 1];
			str[i++] = s[index - 1];
		}
		if (s[index])
			str[i++] = s[index++];
	}
	str[i] = '\0';
	return (str);
}

char	**ft_decoup(char *arg, char **tab, char c)
{
	int	i;
	int	x;
	int	t;

	i = -1;
	x = 0;
	if (!(tab = ft_malloc(sizeof(char *) * (lents(arg, c) + 1))))
		return (NULL);
	t = (int)ft_strlen(arg);
	while(i++ < t)
	{
		if (arg[i] != c && arg[i])
		{
			tab[x] = cpy_tsx(arg, i, c);
			if (tab[x] == NULL)
				return (free_garbage(), NULL);
			i += ft_strlen(tab[x]);
			x++;
		}
	}
	tab[x] = NULL;
	return (tab);
}
