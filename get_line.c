#include "main.h"

/**
 * bring_line - assigns the line var for get_line
 * @line_prt: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **line_prt, size_t *n, char *buffer, size_t j)
{

	if (*line_prt == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*line_prt = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*line_prt = buffer;
	}
	else
	{
		_strcpy(*line_prt, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @line_prt: buffer that stores the input
 * @n: size of line_prt
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **line_prt, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(line_prt, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
