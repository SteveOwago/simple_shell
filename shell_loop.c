#include "shell.h"
/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_ret = 0;

	while (read_status != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_status = get_input(info);
		if (read_status != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}
/**
* find_builtin - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* -2 if builtin signals exit()
*/
int find_builtin(info_t *info)
{
	int i, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", print_environment},
		{"help", print_help},
		{"history", print_history},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{"cd", change_dir},
		{"alias", print_aliases},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_ret = builtintbl[i].func(info);
			break;
		}
	return (builtin_ret);
}
/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, num_args = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			num_args++;
	if (!num_args)
		return;
	path = find_path(info, get_env_var(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((is_interactive(info) || get_env_var(info, "PATH=")
			|| info->argv[0][0] == '/') && find_cmd(info, info->argv[0]))
		fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 150;
			print_error(info, "No Command\n");
		}
	}
}
/**
* fork_cmd - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
	/* TODO: PUT ERROR FUNCTION */
		perror("Fatal Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(98);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 150)
				print_error(info, "Permission denied\n");
		}
	}
}
