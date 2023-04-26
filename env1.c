#include "main.h"

/**
 * env_name_compare - compares env variables names
 * with the name passed.
 * @env_nname: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int env_name_compare(const char *env_nname, const char *name)
{
	int i;

	for (i = 0; env_nname[i] != '='; i++)
	{
		if (env_nname[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environment: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environment)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environmentment variables */
	/* environment is declared in the header file */
	for (i = 0; _environment[i]; i++)
	{
		/* If name and env are equal */
		mov = env_name_compare(_environment[i], name);
		if (mov)
		{
			ptr_env = _environment[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @data_sh: data relevant.
 * Return: 1 on success.
 */
int _env(dt_shell *data_sh)
{
	int i, j;

	for (i = 0; data_sh->_environment[i]; i++)
	{

		for (j = 0; data_sh->_environment[i][j]; j++)
			;

		write(STDOUT_FILENO, data_sh->_environment[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_sh->status = 0;

	return (1);
}
