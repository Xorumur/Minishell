#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef enum e_bool {
	FALSE,
	TRUE,
}			t_bool;

int ft_strlen(const char *str)
{
	int len = 0;

	if (str)
		while (*str++)
			len++;
	return (len);
}

void ft_strcpy(char *dst, const char *src)
{
	while ((*dst++ = *src++))
		;
}

t_bool is_operator(const char *str)
{
	if (!strcmp("|", str) || !strcmp(";", str))
		return TRUE;
	else
		return FALSE;
}

// int ft_tablen(char **tab)
// {
// 	int i = 0;
// 	while (tab[i])
// 		i++;
// 	return i;
// }

// void cd(char **command)
// {
// 	if (ft_tablen(command) != 2)
// 	{
// 		write(2, "error: cd: bad arguments\n", 50);
// 		return ;
// 	}
// 	if (chdir(command[1]) == 0)
// 		return ;
// 	write(2, "error: cd: cannot change directory to ", 50);
// 	write(2, command[1], ft_strlen(command[1]));
// 	write(2, "\n", 1);
// }

void minishell(char *argv[], char *envp[], int in)
{
	char	**command = malloc(sizeof(char *) * 100);
	int		fds[2], next_in = STDIN_FILENO, i = 0;

	if (!command)
	{
		write(2, "error: fatal\n", 50);
		exit(0);
	}
	/* consomme l'opérateur lorsque l'on est dans la récursion */
	if (is_operator(argv[i]))
		++argv;
	/* isoler la commande et ses arguments */
	while (argv[i] && !is_operator(argv[i]))
	{
		command[i] = malloc(sizeof(char) * 100);
		if (!command[i])
		{
			write(2, "error: fatal\n", 50);
			exit(0);
		}
		ft_strcpy(command[i], argv[i]);
		++i;
	}
	command[i] = NULL;
	/* si la sortie de la commande est pipée */
	if (argv[i] && !strcmp("|", argv[i]))
	{
		/* créer le pipe :
		 *
		 * on LIT dans fds[0]
		 * on ECRIT dans fds[1]
		 *
		 * TOUT ce que j'ÉCRIS dans fds[1] est LISIBLE dans fds[0]
		 */
		pipe(fds);
		if (fork() == 0)
		{
			/* on remplance stdin par notre in, qui peut être soit
			 * un pipe, soit stdin au premier appel, on remplace stdout par fds[1]
			 */
			dup2(in, STDIN_FILENO);
			dup2(fds[1], STDOUT_FILENO);
			/* si l'execve provoque une erreur (ex: commande introuvable)
			 * il faut quitter sinon le fils executera le code du pére */
			// if (strcmp("cd", command[0]) == 0)
			// {
			// 	cd(command);
			// 	exit(0);
			// }
			if (execve(command[0], command, envp) == -1)
			{
				write(2, "error: cannot execute ", 50);
				write(2, command[0], ft_strlen(command[0]));
				write(2, "\n", 1);
				exit(0);
			}
		}
		/* une fois le fils lancé on peut fermer l'entrée du pipe puisque
		 * seul le fils lancé ci-dessus devait écrire dedans */
		close(fds[1]);
		/* on fait en sorte que l'entrée de la prochaine commande soit
		 * la sortie du pipe instancier ci-dessus */
		next_in = fds[0];
	}
	/* si la sortie de la commande n'est pas pipée */
	else
	{
		if (fork() == 0)
		{
			dup2(in, STDIN_FILENO);
			// if (strcmp("cd", command[0]) == 0)
			// {
			// 	cd(command);
			// 	exit(0);
			// }
			if (execve(command[0], command, envp) == -1)
			{
				write(2, "error: cannot execute ", 50);
				write(2, command[0], ft_strlen(command[0]));
				write(2, "\n", 1);
				exit(0);
			}
		}
	}
	/* si nous avons executée une commande recevant son entrée via un
	 * pipe on le close pour libérer de descripteur de fichier */
	if (in != STDIN_FILENO)
		close(in);
	/* on incrément argv de(s) i argument(s) consommés */
	argv += i;
	/* on rappel notre fonction s'il reste un/des argument(s) */
	if (*argv)
		minishell(argv, envp, next_in);
}

int main(int argc, char *argv[], char *envp[])
{
	if (argc > 1)
		minishell(++argv, envp, STDIN_FILENO);
	while (wait(NULL) > 0)
		;
	return (0);
}