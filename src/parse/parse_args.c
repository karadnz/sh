/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:40:05 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 20:49:05 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

//env expand, split <|>
//line = 			echo asdf sdaf| grep a
//splitted_cmd = 	echo, asdf, sdaf|, grep, a
//subsplit = 		sdaf|
//return =			echo, asdf, sdaf, |, grep, a
static char	**split_all(char **args, t_prompt *prompt)
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
	prompt->cmds = fill_nodes(split_all(args, prompt), -1);
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
	splitted_cmd = ft_splitcmd(line, " ");
	free(line);
	if (!splitted_cmd)
	{
		mini_perror(QUOTE, NULL, 1);
		return ("");
	}	
	prompt = parse_args(splitted_cmd, prompt);
	if (prompt && prompt->cmds)
		ft_lstclear(&prompt->cmds, free_content);
	return (prompt);
}
