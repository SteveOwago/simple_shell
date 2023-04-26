#include "main.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @data_sh: data structure that contains arguments
 * @errorval: error value
 * Return: error
 */
int get_error(data_shell *data_sh, int errorval)
{
	char *error;

	switch (errorval)
	{
	case -1:
		error = error_env(data_sh);
		break;
	case 126:
		error = error_path_126(data_sh);
		break;
	case 127:
		error = error_not_found(data_sh);
		break;
	case 2:
		if (_strcmp("exit", data_sh->args[0]) == 0)
			error = error_exit_shell(data_sh);
		else if (_strcmp("cd", data_sh->args[0]) == 0)
			error = error_get_cd(data_sh);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data_sh->status = errorval;
	return (errorval);
}
