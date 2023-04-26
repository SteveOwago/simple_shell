#include "main.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @data_sh: data structure (args and input)
 * Return: Return 0
*/
int get_help(dt_shell *data_sh)
{

	if (data_sh->args[1] == 0)
		helping_aux_general();
	else if (_strcmp(data_sh->args[1], "setenv") == 0)
		helping_aux_setenv();
	else if (_strcmp(data_sh->args[1], "env") == 0)
		helping_aux_env();
	else if (_strcmp(data_sh->args[1], "unsetenv") == 0)
		helping_aux_unsetenv();
	else if (_strcmp(data_sh->args[1], "help") == 0)
		helping_aux();
	else if (_strcmp(data_sh->args[1], "exit") == 0)
		helping_aux_exit();
	else if (_strcmp(data_sh->args[1], "cd") == 0)
		helping_aux_cd();
	else if (_strcmp(data_sh->args[1], "alias") == 0)
		helping_aux_alias();
	else
		write(STDERR_FILENO, data_sh->args[0],
		      _strlen(data_sh->args[0]));

	data_sh->status = 0;
	return (1);
}
