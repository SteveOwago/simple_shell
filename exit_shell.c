#include "main.h"

/**
 * shell_exit - shell quit handler
 *
 * @data_sh: data relevant (status and args)
 * Return: 0 on success.
 */
int shell_exit(dt_shell *data_sh)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (data_sh->args[1] != NULL)
	{
		ustatus = _atoi(data_sh->args[1]);
		is_digit = _isdigit(data_sh->args[1]);
		str_len = _strlen(data_sh->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(data_sh, 2);
			data_sh->status = 2;
			return (1);
		}
		data_sh->status = (ustatus % 256);
	}
	return (0);
}
