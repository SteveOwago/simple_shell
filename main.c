#include "shell.h"
/**
 * main - Simple Shell (Hsh)
 * @argc: Argument Count
 * @argv:Argument Value
 * Return: Exit Value By Status
 */

int main(__attribute__((unused)) int argc, char **argv)
{
	char *line, **toks;
	int counter = 0, statue = 1, st = 0;

	if (argv[1] != NULL)
		read_file(argv[1], argv);
	signal(SIGINT, signal_to_handle);
	while (statue)
	{
		counter++;
		if (isatty(STDIN_FILENO))
			PRINTER("($) ");
		line = _getline();
		if (line[0] == '\0')
		{
			continue;
		}
		history(line);
		toks = parse_cmd(line);
		if (_strcmp(toks[0], "exit") == 0)
		{
			exit_bul(toks, line, argv, counter);
		}
		else if (check_builtin(toks) == 0)
		{
			st = handle_builtin(toks, st);
			free_all(toks, line);
			continue;
		}
		else
		{
			st = check_cmd(toks, line, counter, argv);
		}
		free_all(toks, line);
	}
	return (statue);
}

