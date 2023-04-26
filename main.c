#include "main.h"

/**
 * free_data - frees data structure
 *
 * @data_sh: data structure
 * Return: no return
 */
void free_data(data_shell *data_sh)
{
	unsigned int i;

	for (i = 0; data_sh->_environment[i]; i++)
	{
		free(data_sh->_environment[i]);
	}

	free(data_sh->_environment);
	free(data_sh->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @data_sh: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *data_sh, char **av)
{
	unsigned int i;

	data_sh->av = av;
	data_sh->input = NULL;
	data_sh->args = NULL;
	data_sh->status = 0;
	data_sh->counter = 1;

	for (i = 0; environment[i]; i++)
		;

	data_sh->_environment = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environment[i]; i++)
	{
		data_sh->_environment[i] = _strdup(environment[i]);
	}

	data_sh->_environment[i] = NULL;
	data_sh->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell data_sh;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&data_sh, av);
	shell_loop(&data_sh);
	free_data(&data_sh);
	if (data_sh.status < 0)
		return (255);
	return (data_sh.status);
}
