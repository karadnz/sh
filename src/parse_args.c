/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsenses <hsenses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:40:05 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 14:40:06 by hsenses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_status;

static char	**split_all(char **args, t_prompt *prompt) //SOR
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, \
			mini_getenv("HOME", prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

//splitted_cmd = args
static void	*parse_args(char **args, t_prompt *prompt)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	prompt->cmds = fill_nodes(split_all(args, prompt), -1); //SOR
	if (!prompt->cmds)
		return (prompt);
	i = ft_lstsize(prompt->cmds);
	g_status = builtin(prompt, prompt->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&prompt->cmds, free_content);
		return (NULL);
	}
	return (prompt);
}

void	*check_args(char *line, t_prompt *prompt)
{
	char	**splitted_cmd;

	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (line[0] != '\0')
		add_history(line);
	splitted_cmd = ft_splitcmd(line, " "); //SOR
	free(line);
	if (!splitted_cmd)
	{
		mini_perror(QUOTE, NULL, 1);
		return (""); //ptr 0 olmadigi icin mainde breaklemez
	}	
	prompt = parse_args(splitted_cmd, prompt); //execve de hata olursa ptr 0 olacak??
	if (prompt && prompt->cmds)
		ft_lstclear(&prompt->cmds, free_content);
	return (prompt);
}
//	t_mini	*n;
//if (p && p->cmds)
	// 	n = p->cmds->content;//SOR BAS SON MU
	// if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
	// 	p->envp = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
	// 		p->envp, 1); //SIL
