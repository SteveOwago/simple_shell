#include "shell.h"
/**
* is_executable_command - determines if a file is an executable command
* @info: the info struct
* @file_path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_executable_command(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
	{
		fprintf(stderr, "Error: Could not find file path.\n");
		return (0);
	}
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
* duplicate_chars - duplicates characters
* @path_str: the PATH string
* @start_index: starting index
* @stop_index: stopping index
*
* Return: pointer to new buffer
*/
char *duplicate_chars(char *path_str, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
	{
		if (path_str[i] != ':')
		{
			buffer[k++] = path_str[i];
		}
	}
	buffer[k] = 0;
	return (buffer);
}
/**
* find_path - finds this cmd in the PATH string
* @info: the info struct
* @path_str: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_path(info_t *info, char *path_str, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_str)
	{
		fprintf(stderr, "Error: No PATH string provided.\n");
		return (NULL);
	}
	if ((str_length(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable_command(info, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = duplicate_chars(path_str, current_position, i);
			if (!*path)
			{
				_strncat(path, cmd);
			}
			else
			{
				_strncat(path, "/");
				_strncat(path, cmd);
			}
			if (is_executable_command(info, path))
				return (path);
			if (!path_str[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}
