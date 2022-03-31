#include "includes/minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)env;
    (void)argv;

	while (1)
	{
		minishell();
	}
} 