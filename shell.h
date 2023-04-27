#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int is_interactive(info_t *info);
int replace_string(char **, char *);
int replace_vars(info_t *info);
int replace_alias(info_t *);
void check_chain_status(info_t *info, char *buf, size_t *current_position, size_t start_position, size_t buffer_length);
int is_chain_delimiter(info_t *info, char *buf, size_t *current_position);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_strcpy(char *dest, char *src);
int _putchar(char c);
void print_string(char *str);
char *concat_strings(char *dest, char *src);
char *string_starts_with(const char *haystack, const char *needle);
int compare_strings(char *str1, char *str2);
int get_string_length(char *str);
void fork_cmd(info_t *info);
void find_cmd(info_t *info);
int find_builtin(info_t *info);
int hsh(info_t *info, char **av);
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size);
void free_str_arr(char **str_arr);
char *find_path(info_t *info, char *path_str, char *cmd);
char *duplicate_chars(char *path_str, int start_index, int stop_index);
int is_executable_command(info_t *info, char *file_path);
int free_pointer(void **ptr);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *node_starts_with(list_t *node, char *prefix, char c);
size_t print_list(const list_t *head);
char **list_to_strings(list_t *head);
void free_list(list_t **head_ptr);
int delete_node_at_index(list_t **head, unsigned int index);
size_t print_list_str(const list_t *head);
list_t *add_node_end(list_t **head, const char *str, int num);
list_t *add_node(list_t **head, const char *str, int num);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int line_count);
int read_history(info_t *info);
int write_history(info_t *info);
char *get_history_file(info_t *info);
void free_info(info_t *info, int all);
void set_info(info_t *info, char **av);
void initialize_info(info_t *info);
int set_environment_variable(info_t *info, char *variable, char *value);
int unset_env(info_t *info, char *env_var);
char **get_environment(info_t *info);
void handle_sigint(int signal_number);
int get_line(info_t *info, char **buffer_ptr, size_t *buffer_length);
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_size);
ssize_t get_input(info_t *info);
ssize_t input_buffer(info_t *info, char **buffer, size_t *buffer_length);
char *_strncat(char *dest, const char *src, size_t n);
char *_strncpy(char *dest, const char *src, size_t n);
void remove_comments(char *buf);
char *convert_number(long int num, int base, int flags);
int print_d(int input, int fd);
void print_error(info_t *info, char *estr);
int _erratoi(char *s);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
int _eputchar(char c);
void _eputs(char *str);
int populate_env_list(info_t *info);
int unset_env_var(info_t *info);
int set_env_var(info_t *info);
char *get_env_var(info_t *info, const char *name);
int print_environment(info_t *info);
int print_aliases(info_t *info);
int print_alias(list_t *node);
int set_alias(info_t *info, char *alias_str);
int unset_alias(info_t *info, char *alias_str);
int print_history(info_t *info);
void chain_stat(info_t *info, char *bug, size_t *cur_pos, size_t ist_pos, size_t buf_len);
int print_help(info_t *info);
int change_dir(info_t *info);
int exit_shell(info_t *info);
int string_to_int(char *s);
int is_alphabetic(int c);
int is_chain_del(info_t *info, char *buf, size_t *cur_pos);
int is_delimiter(char c, char *delim);
int is_interactive(info_t *info);
char **strtow2(char *input_str, char del);
char **strtow(char *input_str, char *del_s);
int str_length(const char *string);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *str_concat(char *dest, char *src);
char *str_duplicate(const char *string);
void _puts(char *);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
int _putchar(char);
char *_strchr(char *, char);
int bfree(void **ptr);
int free_pointer(void **ptr);
char _strdup(void **);
#endif
