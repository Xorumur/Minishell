#include "includes/minishell.h"

static g_data g;

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)env;
    (void)argv;

	init_env();
	while (1)
	{
		minishell();
	}
} 