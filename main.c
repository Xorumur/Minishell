/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:31:32 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 14:31:32 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_data(void)
{
	g_data.quoterror = FALSE;
	g_data.status.is_fork = FALSE;
	g_data.status.is_redir = FALSE;
	g_data.status.is_pipe = FALSE;
	g_data.status.is_heredoc = FALSE;
	g_data.status.is_dlredir = FALSE;
	g_data.status.ctrlc = FALSE;

}

void	tokenizer(void)
{
	t_tokenlist		*tokens;
	t_tokenlist		*curr_node;
	t_token			*curr_tok;
		
	tokens = NULL;
	curr_tok = lexer_get_next_token(g_data.lexer);
	while (curr_tok != NULL)
	{
		curr_node = ft_lstnew_token(curr_tok);
		ft_lstadd_back_token(&tokens, curr_node);
		curr_tok = lexer_get_next_token(g_data.lexer);
	}
	g_data.tokens = tokens;
}

void	minishell(void)
{
	init_data();
	echo_control_seq(0);
	g_data.cmd = readline("|---Mathiew * minishell---$> ");
	if (g_data.cmd && ft_strlen(g_data.cmd))
		add_history(g_data.cmd);
	if (g_data.cmd == NULL)
	{
		// free_all();
		// free_tab(g_data.tab_env);
		// while (1) ;
		exit(ft_putstr_fd("exit\n", STDERR_FILENO));
	}
	else if (!(g_data.cmd[0] == 0))
	{
		/*
		** The command is valid -> Tokenize and execute it :
		*/
		signal(SIGQUIT, handle_sigquit); // Activate handler for sigquit (^\Quit: 3)
		echo_control_seq(1);
		g_data.lexer = init_lexer(g_data.cmd);
		tokenizer();
		t_tokenlist* tmp = g_data.tokens;
		while (tmp)
		{
			printf("id = %i value = [%s]\n", tmp->token->e_type, tmp->token->value);
			tmp = tmp->next;
		}
		// At the end of every commands free everything that is used for commands
		// Free token list
		if (g_data.env)
			free_tab(g_data.tab_env);
		g_data.tab_env = get_new_env();
		if (g_data.quoterror == FALSE)
			parsing();// Execute command
		else
			printf("Error: quote error\n");
		free_all();
	}
	signal(SIGQUIT, SIG_IGN);
	if (g_data.cmd)
		free(g_data.cmd);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	// Check if env exist before stocking it
	if (env[0])
	{
		g_data.status.is_env = TRUE;
		init_data_env(env);
	}
	else
		g_data.status.is_env = FALSE;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_data.verif = FALSE;
	while (42)
	{
		minishell();
	}
	return (0);
}
