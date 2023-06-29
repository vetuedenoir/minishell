
#include "../minishell.h"

static int	lents(const char *str, char c)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			while(str[++i] != 34)
				;
			t++;
		}
		else if (str[i] == 39)
		{
			while(str[++i] != 39)
				;
			t++;
		}
		else if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			t++;
		i++;
	}
	return (t);
}

static int    ft_verif_quote(char *str)
{
    int    i;
    int    s;
    int    q;

    i = 0;
    s = 0;
    q = 0;
    if (!str)
        return (-1);
    while (str[i] != '\0')
    {
        if (str[i] == 34)
            q++;
        if (str[i] == 39)
            s++;
        i++;
    }
    if (s % 2 != 0 && q % 2 != 0)
        return (-1);
    return (1);
}

static char	*ft_cop(const char *s, int index, char c)
{
	int		i;
	int		t;
	char	*str;

	i = index;
	t = 0;
	while (s[i] != c && s[i])
	{
		t++;
		i++;
	}
	str = malloc(sizeof(char) * (t + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[index] != c && s[index])
	{
		str[i] = s[index];
		i++;
		index++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_decoup(char c)
{
	char 	*arg;
	char	**tab;
	int	i = -1;
	int	j = 0;

	if (ft_verif_quote(arg = readline(PROMPT)) == -1)
		return (free(arg), NULL);
	if (!(tab = malloc(sizeof(char *) * lents(arg, c) + 1)))
		return (free(arg), NULL);
	while(i++ < (int)ft_strlen(arg))
	{
		if (arg[i] == 34 || arg[i] == 39)
		{
			tab[j] = ft_cop(arg, i + 1, arg[i]);
			i = i + ft_strlen(tab[j]) + 2;
			j++;
		}
		if (arg[i] != c && arg[i])
		{
			tab[j] = ft_cop(arg, i, c);
			i = i + ft_strlen(tab[j]);
			j++;
		}
	}
	return (tab[j] = 0, tab);
}
