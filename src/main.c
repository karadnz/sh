/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsenses <hsenses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:39:59 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 14:40:00 by hsenses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_status;

static void	mini_getpid(t_prompt *p) //SIL
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_prompt	init_vars(t_prompt prompt, char *str) //CHANGE
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
	str = mini_getenv("PATH", prompt.envp, 4); //SIL
	if (!str)
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	return (prompt);
}
//static t_prompt	init_vars(t_prompt prompt, char *str, char **argv) //CHANGE
// str = mini_getenv("_", prompt.envp, 1); //SIL
	// if (!str)
	// 	prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);
	// free(str);

//copy and update env vars
static t_prompt	init_prompt(char **envp)//CHANGE ARGV
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	mini_getpid(&prompt);//SIL
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
