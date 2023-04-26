#ifndef  _MAIN_H_
#define  _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environment;


/**
 * struct data - struct that contains all relevant data on runtime
 * @arg_vector: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environment: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **arg_vector;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environment;
	char *pid;
} dt_shell;

/**
 * struct separator_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct separator_list_s
{
	char separator;
	struct separator_list_s *next;
} separator_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(dt_shell *data_sh);
} builtin_t;

/* aux_lists.c */
separator_list *add_separator_node_end(separator_list **head, char sep);
void free_separator_list(separator_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int compare_charss(char str[], const char *delimit);
char *_strtok(char str[], const char *delimit);
int _isdigit(const char *s);

/* aux_str3.c */
void string_reverse(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(dt_shell *data_sh, char *input, int i, int bool);
int check_syntax_error(dt_shell *data_sh, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(dt_shell *data_sh);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(separator_list **heads, line_list **head_list, char *input);
void go_next(separator_list **list_s, line_list **list_l, dt_shell *data_sh);
int split_commands(dt_shell *data_sh, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, dt_shell *data);
int check_variables(r_var **h, char *in, char *st, dt_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, dt_shell *data_sh);

/* get_line.c */
void bring_line(char **line_prt, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **line_prt, size_t *n, FILE *stream);

/* bulletin_find */
int bulletin_find(dt_shell *data_sh);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environment);
int is_executable(dt_shell *data_sh);
int check_error_cmd(char *dir, dt_shell *data_sh);
int cmd_exec(dt_shell *data_sh);

/* env1.c */
char *_getenv(const char *name, char **_environment);
int _env(dt_shell *data_sh);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, dt_shell *data_sh);
int _setenv(dt_shell *data_sh);
int _unsetenv(dt_shell *data_sh);

/* cd.c */
void cd_dot(dt_shell *data_sh);
void cd_to(dt_shell *data_sh);
void cd_previous(dt_shell *data_sh);
void cd_to_home(dt_shell *data_sh);

/* cd_shell.c */
int cd_shell(dt_shell *data_sh);

/* get_builtin */
int (*get_builtin(char *cmd))(dt_shell *data_sh);

/* _exit.c */
int shell_exit(dt_shell *data_sh);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(dt_shell *, char *, char *, char *);
char *error_get_cd(dt_shell *data_sh);
char *error_not_found(dt_shell *data_sh);
char *error_shell_exit(dt_shell *data_sh);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(dt_shell *data_sh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(dt_shell *data_sh);


/* get_error.c */
int get_error(dt_shell *data_sh, int error_value);

/* get_sigint.c */
void get_signalint(int signal);

/* helping_aux.c */
void helping_aux_env(void);
void helping_aux_setenv(void);
void helping_aux_unsetenv(void);
void helping_aux_general(void);
void helping_aux_exit(void);

/* helping_aux2.c */
void helping_aux(void);
void helping_aux_alias(void);
void helping_aux_cd(void);

/* get_help.c */
int get_help(dt_shell *data_sh);

#endif
