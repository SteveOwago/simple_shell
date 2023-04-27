#include "shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
	{
		fprintf(stderr, "Error: _eputs() called with NULL string\n");
		return;
	}
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int buf_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buf_index++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int buf_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buf_index++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string to given fd
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
	{
		fprintf(stderr, "Error: _putsfd() called with NULL string\n");
		return (0);
	}
	while (*str)
	{
		char_count += _putfd(*str++, fd);
	}
	return (char_count);
}
