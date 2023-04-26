#include "shell.h"

/**
 * main - entry point
 * @arg_count: arg count
 * @arg_vector: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **arg_vector)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (arg_count == 2)
	{
		fd = open(arg_vector[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arg_vector[0]);
				_eputs(": 0: Can't open ");
				_eputs(arg_vector[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, arg_vector);
	return (EXIT_SUCCESS);
}
