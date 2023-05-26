/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:39:59 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 20:46:45 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

static t_prompt	init_vars(t_prompt prompt, char *str)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = mini_getenv("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	return (prompt);
}

//copy and update env vars
static t_prompt	init_prompt(char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	prompt = init_vars(prompt, str);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char				*str;
	char				*line;
	t_prompt			prompt;

	prompt = init_prompt(envp);
	while (argv && argc)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt(prompt);
		if (str)
			line = readline(str);
		else
			line = readline("guest@minishell $ ");
		free(str);
		if (!check_args(line, &prompt))
			break ;
	}
	exit(g_status);
}
