/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:52 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 21:57:23 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STD_IN 0
# define STD_OUT 1
# define INFILE 10
# define OUTFILE 11
# define HERDOC 12
# define APPAND 13
# define PATH "d:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

# include <stdio.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <dirent.h>
# include <stdbool.h>
# include <paths.h>
# include <sys/types.h>
# include <sys/wait.h>

int	g_exit_status;

typedef struct s_red
{
	char			*file_name;
	int				type;
	int				pipe_0;
	struct s_red	*next;
}					t_red;

typedef struct s_lex
{
	int		i;
	int		arglen;
	int		argstart;
}			t_lex;

typedef struct s_cmd
{
	char			**content;
	int				*quoted;
	int				*pipe;
	t_red			*red;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

//....................../execution/.....................

t_env	*create_list(char ***str);
int		check_builtins(char *str);
void	exe_builtins(t_cmd *cmd, t_env **env);
int		red_test(t_red *red);
int		redirections(t_red *red);
void	ft_pipe2(int fd[]);
void	ft_pipe(int fd[]);
t_env	*ft_lstneww(char *env_name, char *env_content);
void	ft_lstadd_backk(t_env **lst, t_env *new);
void	execution_base(t_cmd *cmd, t_env **env, char **envp);
void	ft_echo(char **str);
void	ft_cd(char **str, t_env *env);
void	ft_env(char **str, t_env *env);
void	ft_pwd(void);
int		ft_strcmpp(char *str1, char *str2);
void	ft_export(char **str, t_env **env);
void	ft_unset(t_env **env, t_cmd *cmd);
int		ft_exit(char **str);
int		exit_status(int status);
void	sig_int_main(int sig);
void	sig_int(int sig);
char	*find_path(t_env *env, t_cmd *cmd);
int		charcmp(char c, char d);
int		is_numor_char(char c);
int		join_and_init(char *str, t_env **env);
int		check_ifitsthere(char *str, t_env *env);
void	init_content(char *str, t_env *env);
void	join_content(char *str, t_env *env);
int		parse(char *str);
void	print_env(t_env *env);

//....................../include/.......................

//./include/cmd_include.c
t_cmd	*ft_cmdlast(t_cmd *cmd);
t_cmd	*ft_cmdnew(char **content, int *quoted, int *pipe);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
void	ft_cmddelone(t_cmd *cmd, void (*del)(void*));
void	ft_cmdclear(t_cmd **cmd, void (*del)(void*));
//./include/ft_dellst.c
void	ft_dellst(t_list **lst, t_list *del);
//./include/ft_error.c
void	ft_error(char *s);
//./include/dubstr_include.c
int		ft_dubstrlen(char **s);
void	free_dub(char **content);
int		*remove_array_column(int *arr, int arr_size, int col);
char	**reallocate_dub(char **content, char *arg_content);
char	**remove_str(char **content, int remove_index);
//./include/env_include.c
t_env	*ft_envnew(char *content, char *name);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **env, t_env *new);
void	ft_envdelone(t_env *env, void (*del)(void*));
void	ft_envclear(t_env **env, void (*del)(void*));
//./include/ft_is_opp.c
int		ft_is_opp(t_list *arg);
//./include/ft_lstinsert.c
void	ft_lstinsert(t_list **lst, t_list *new);
//./include/ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);
//./include/ft_substr_lex.c
char	*ft_substr_lex(char *s, unsigned int start, size_t end);
//./include/in_between_include.c
void	del_in_between(t_list **tmp);
int		ft_cmpecho(const char *s);
int		ft_ncmp(char *s1);
void	is_echo(t_list **tmp);
//./include/red_include.c
t_red	*ft_rednew(char *file_name);
t_red	*ft_redlast(t_red *red);
void	ft_reddelone(t_red *red, void (*del)(void*));
void	ft_redclear(t_red **red, void (*del)(void*));
void	ft_redadd_back(t_red **red, t_red *new);
//....................../lexing/........................
//./lexing/clean_line.c
void	ft_replace(t_list **arg, t_env *env);
void	ft_expend(t_list **arg, t_env *env, int d);
void	dollar(t_list **arg, t_env *env);
void	clean_line(t_list **arg, t_env *env);
//./lexing/collect_args.c
void	collect_args(char *buff, t_lex *lex, t_list **arg);
//./lexing/concatenate.c
void	concatenate(t_list **arg);
//./lexing/define_opp.c
void	define_pipe(t_list **arg);
void	ft_is_redirections(t_list **arg);
//./lexing/double_quoting.c
int		double_quoting(char *buff, t_lex *lex, t_list **arg);
//./lexing/ft_herdoc.c
void	cmd_handler(int sig);
int		ft_herdoc(t_list **arg, t_env *env);
//./lexing/single_quoting.c
int		lex(char *buff, t_list **arg, t_env *env);
//./lexing/lex.c
int		single_quoting(char *buff, t_lex *lex, t_list **arg);
//./lexing/spaces.c
int		only_space(t_list *arg);
void	del_spaces(t_list **arg);
//....................../parsing/.......................
//./parsing/ft_errors.c
int		ft_errors(t_list *arg);
//./parsing/ft_red.c
void	redirections_parser(t_cmd *cmd);
//./parsing/splite_pipe.c
t_cmd	*split_pipe(t_list *arg);
//./parsing/wildcard.c
void	ft_wildcard(t_list **arg);
//./minishell.c
void	handler(int sig);

#endif