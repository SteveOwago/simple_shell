#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *buffer_length)
{
	ssize_t read_bytes = 0;
	size_t length_param = 0;

	if (!*buffer_length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read_bytes = getline(buffer, &length_param, stdin);
#else
		read_bytes = _getline(info, buffer, &length_param);
#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0';
				(*buffer)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*buffer_length = read_bytes;
				info->cmd_buf = buffer;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t buf_index, iterator, buf_leng;
	ssize_t read_bytes = 0;
	char **buf_ptr = &(info->arg), *pointer;

	_putchar(BUF_FLUSH);
	read_bytes = input_buffer(info, &buf, &buf_leng);
	if (read_bytes == -1)
		return (-1);
	if (buf_leng)
	{
		iterator = buf_index;
		pointer = buf + buf_index;
		check_chain(info, buf, &iterator, buf_index, buf_leng);
		while (iterator < buf_leng)
		{
			/* iterate to semicolon or end */
			if (is_chain_del(info, buf, &iterator))
				break;
			iterator++;
		}
		buf_index = iterator + 1;
		if (buf_index >= buf_leng)
		{
			/* reached end of buffer? */
			buf_index = buf_leng = 0;
				info->cmd_buf_type = CMD_NORM;
		}
			*free_pointer = pointer;
			return (_strlen(pointer));
			info->cmd_buf_type = CMD_NORM
			}
		*buffer_pointer = pointer;
		return (_strlen(pointer));
	}
*buffer_pointer = buf;
return (read_bytes);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @buffer_size: size
 *
 * Return: read_status
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_size)
{
	ssize_t read_status = 0;

	if (*buffer_size)
		return (0);
	read_status = read(info->readfd, buffer, READ_BUF_SIZE);
	if (read_status >= 0)
		*buffer_size = read_status;
	return (read_status);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @buffer_ptr: address of pointer to buffer, preallocated or NULL
 * @buffer_length: size of preallocated buffer_ptr buffer if not NULL
 *
 * Return: buffer_length
 */
int get_line(info_t *info, char **buffer_ptr, size_t *buffer_length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *buffer_ptr;
	if (p && buffer_length)
		str = *buffer_length;
	if (i == len)
		i = len = 0;

	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, str, str ? str + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (str)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	str += k - i;
	i = k;
	p = new_p;

	if (str_length)
		*length = str;
	*buffer_ptr = p;
	return (str);
}

/**
 * sigintHandler - Handles SIGINT signal (Ctrl+C)
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
