#include "main.h"

/**
 * bulletin_find - finds builtins and commands
 *
 * @data_sh: data relevant (args)
 * Return: 1 on success.
 */
int bulletin_find(dt_shell *data_sh)
{
	int (*builtin)(dt_shell *data_sh);

	if (data_sh->args[0] == NULL)
		return (1);

	builtin = get_builtin(data_sh->args[0]);

	if (builtin != NULL)
		return (builtin(data_sh));

	return (cmd_exec(data_sh));
}
