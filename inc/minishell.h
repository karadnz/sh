/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:37:47 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 19:02:28 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "colors.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_prompt
{
	t_list	*cmds; //echo, asdf, asdf,asdf | grep asd
	char	**envp;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd; //echo, asdf, asdf,asdf 
	char	*full_path; // /bin/echo
	int		infile;
	int		outfile;
}			t_mini;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};


/* Handle executing */
int		builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);

/* full_cmd ilk elemani builtin mi diye kontrol eder */
int		is_builtin(t_mini *n);

/* cd builtin */
int		mini_cd(t_prompt *prompt);

/* Checks for errors and returns whether first arg is a directory */
void	cd_error(char **str[2]);

/* pwd builtin */
int		mini_pwd(void);

/* echo bultin */
int		mini_echo(t_list *cmd);

/* export builtin */
int		mini_export(t_prompt *prompt);

/* unset builtin */
int		mini_unset(t_prompt *prompt);

/* exit builtin */
int		mini_exit(t_list *cmd, int *is_exit);

/* splitcmd and parse */
void	*check_args(char *line, t_prompt *prompt);

/* ft_split bosluk tirnaklari dikkate alarak  */
char	**ft_splitcmd(char const *line, char *set);

/* ft_split <|> tirnaklari dikkate alarak */
char	**ft_cmdsubsplit(char const *s, char *set);

/* son haldeki tirnaklari siler */
char	*ft_strtrim_all(char const *s1, int squote, int dquote);

/* cmds i doldurur */
t_list	*fill_nodes(char **args, int i);

/* gelen flaglere gore dosyayi acar ve fd dondurur */
int		get_fd(int oldfd, char *path, int flags[2]);

/* open outfule > */
t_mini	*get_outfile1(t_mini *node, char **args, int *i);

/* open outfile >> */
t_mini	*get_outfile2(t_mini *node, char **args, int *i);

/* open infile < */
t_mini	*get_infile1(t_mini *node, char **args, int *i);

/* open heredoc << */
t_mini	*get_infile2(t_mini *node, char **args, int *i);

/* non-builtin execve, sonraki nodeun infileini pipein read endi yapar */
void	*exec_cmd(t_prompt *prompt, t_list *cmd);

/* gerekliyse forkla  */
void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2]);

/* child icinde execve  */
void	child_builtin(t_prompt *prompt, t_mini *n, int l, t_list *cmd);

/* command PATH icindeki dir lerde var mi diye kontrol eder ve command in full pathini dondurur */
void	get_cmd(t_prompt *prompt, t_list *start, char **split_path, char *path);

/* expand env */
char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);

/* expand ~ */
char	*expand_path(char *str, int i, int quotes[2], char *var);

/* Retrieves a string from standard input, expanding vars when needed */
int		get_here_doc(char *str[2], char *aux[2]);

/* stderr e custom error basmak icin */
void	*mini_perror(int err_type, char *param, int err);

/* getenv */
char	*mini_getenv(char	*var, char **envp, int n);

/* setenv */
char	**mini_setenv(char *var, char *value, char **envp, int n);

/* readline icin prompt */
char	*mini_getprompt(t_prompt prompt);

/* free linked list */
void	free_content(void *content);

/* Function to handle SIGINT signals for main process */
void	handle_sigint(int sig);

#endif
