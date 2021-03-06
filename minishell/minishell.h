/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:50 by rpunet            #+#    #+#             */
/*   Updated: 2021/06/13 22:57:55 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft.h"
# include "ft_printf.h"

# define READ		0
# define WRITE		1
# define BUILTINS	2

/*
** STRUCTS ---------------------------------
*/
typedef struct s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef struct s_lex
{
	t_tok			*list_token;
}					t_lex;

enum				e_tok{
	TOKEN = -1,
	SEMICOLON = ';',
	SPACE = ' ',
	PIPE = '|',
	REDIR = '>',
	INDIR = '<',
	APPEND = 66,
	QUOTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	VARIABLE = '$',
	NULTOK = 0,
};

enum				e_seq{
	GENERAL,
	QUOTED,
	DQUOTED,
	VAR,
	SCAPED,
};

typedef struct s_ASTnode
{
	int					type;
	char				*data;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}					t_ASTnode;

typedef struct s_cmd
{
	int				io[2];
}					t_cmd;

enum				e_node
{
	SEQ_NODE,
	PIPE_NODE,
	REDIR_NODE,
	INDIR_NODE,
	APPEND_NODE,
	CMDNAME_NODE,
	TOKEN_NODE,
	//DATA,
};
/*
** tipo general para comprobaciones de free, etc
** de los tipos terminales que guardan datos en node->data.
** los demás solo tienen node->type
*/

int			ft_get_input(char **line);
t_tok		*tok_init(int datasize);
void		tok_delete(t_tok *token);

int			ft_lexer(char *line, t_lex *lexer, int size, char **envp);

int			ft_parser(t_lex *lexer, t_ASTnode **syntax_tree);
void		ASTdelete(t_ASTnode *node);
int			terminal(int	tokentype);
t_ASTnode	*GR_seq(void);
t_ASTnode	*gr_seq_1(void);
t_ASTnode	*gr_seq_2(void);
t_ASTnode	*gr_seq_3(void);
t_ASTnode	*GR_job(void);
t_ASTnode	*gr_job_1(void);
t_ASTnode	*gr_job_2(void);
t_ASTnode	*GR_instr(void);
t_ASTnode	*gr_instr_1(void);
t_ASTnode	*gr_instr_2(void);
t_ASTnode	*gr_instr_3(void);
t_ASTnode	*GR_cmd(void);
t_ASTnode	*gr_cmd_1(void);
t_ASTnode	*GR_tokenlist(void);
t_ASTnode	*gr_tokenlist_1(void);
t_ASTnode	*gr_tokenlist_2(void);

void		execute_CMD(t_ASTnode *cmd_node, int in, int out, char ***envp, int *fds);
void		execute_INSTR(t_ASTnode *instr, char ***envp, int *fds);
void		execute_JOB(t_ASTnode *job, char ***envp);
void		execute_SEQ(t_ASTnode *seq, char ***envp);
void		ft_execute(t_ASTnode *syntax_tree, char ***envp);

void		free_char_array(char **arr, int size);
int			exit_failure(char *format, ...);
void		do_nothing(void *vd);
void		*return_null(char *ptr);

int			check_builtins(char **args, char **envp);
int			ft_pwd(char **arg, char **envp);
int			ft_cd(char **args, char ***envp);
int			ft_echo(char **args, char **envp);
int			ft_exit(void);
int			ft_export(char **args, char ***envp);
char	**ft_envdup(char **envp, int len, int add, char *ignore);
int		ft_unset(char **args, char ***envp);
char	*read_key(char *var);
void	delete_var(char ***envp, char *del);
void	add_single_exp(char ***envp, char *arg);
char	*find_variable(char **envp, char *arg, int *no_del);
void	delete_var(char ***envp, char *del);

int			double_len(char **arr);

int		exec_process(char **args, char **envp, int i);
char	*find_directory(DIR **dir, char **args);

void	expand_vars(char **cmd, char **envp);
char	*find_value(char **envp, char *key);

#endif
