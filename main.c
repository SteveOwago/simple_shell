#include "shell.h"

/**
* main - entry point
* @arg_count: arg count
* @arg_vect: arg vector
*
* Return: 0 on success, 1 on error
*/

int main(int arg_count, char **arg_vect)
{
	info_t info[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (file_descriptor)
	: "r" (file_descriptor));
	if (arg_count == 2)
	{
		file_descriptor = open(arg_vect[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
			{
				fprintf(stderr, "Error: Permission denied to open %s\n",
				arg_vect[1]);
				exit(98);
			}
			if (errno == ENOENT)
			{
				fprintf(stderr, "%s: 0: Can't open %s\n", arg_vect[0],
				arg_vect[1]);
				exit(98);
			}
			fprintf(stderr, "Error: Failed to open %s\n", arg_vect[1]);
			return (EXIT_FAILURE);
		}
		info->readfd = file_descriptor;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, arg_vect);
	return (EXIT_SUCCESS);
}
