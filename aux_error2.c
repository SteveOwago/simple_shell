#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @data_sh: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(dt_shell *data_sh)
{
	int length;
	char *error;
	char *str_ver_counter;
	char *msg;

	str_ver_counter = aux_itoa(data_sh->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(data_sh->arg_vector[0]) + _strlen(str_ver_counter);
	length += _strlen(data_sh->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(str_ver_counter);
		return (NULL);
	}

	_strcpy(error, data_sh->arg_vector[0]);
	_strcat(error, ": ");
	_strcat(error, str_ver_counter);
	_strcat(error, ": ");
	_strcat(error, data_sh->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(str_ver_counter);

	return (error);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @data_sh: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(dt_shell *data_sh)
{
	int length;
	char *str_ver_counter;
	char *error;

	str_ver_counter = aux_itoa(data_sh->counter);
	length = _strlen(data_sh->arg_vector[0]) + _strlen(str_ver_counter);
	length += _strlen(data_sh->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(str_ver_counter);
		return (NULL);
	}
	_strcpy(error, data_sh->arg_vector[0]);
	_strcat(error, ": ");
	_strcat(error, str_ver_counter);
	_strcat(error, ": ");
	_strcat(error, data_sh->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(str_ver_counter);
	return (error);
}
