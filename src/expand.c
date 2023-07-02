#include "../minishell.h"

void	expand(t_tool *data)
{
	(void)data;
	printf("mini : %s\n", getenv("USER"));
}
