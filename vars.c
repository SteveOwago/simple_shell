#include "shell.h"
/**
* is_chain_del - test if current char in buffer is a chain delimeter
*
* @info: the parameter struct
*
* @buf: the char buffer
*
* @cur_pos: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int is_chain_del(info_t *info, char *buf, size_t *cur_pos)
{
	size_t j = *cur_pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	return (0);
	*cur_pos = j;
	return (1);
}
/**
* chain_status - checks we should continue chaining based on last status
*
* @info: the parameter struct
*
* @buf: the char buffer
*
* @cur_pos: address of current position in buf
*
* @ist_pos: starting position in buf
*
* @buf_len: length of buf
*
* Return: Void
*/
void chain_stat(info_t *info, char *buf, size_t *cur_pos, size_t ist_pos,
size_t buf_len)
{
	size_t j = *cur_pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[ist_pos] = 0;
			j = buf_len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[ist_pos] = 0;
			j = buf_len;
		}
	}
	*cur_pos = j;
}
/**
* replace_alias - replaces an aliases in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
	node = node_starts_with(info->alias, info->argv[0], '=');
	if (!node)
		return (0);
	free(info->argv[0]);
	p = _strchr(node->str, '=');
	if (!p)
		return (0);
	p = _strdup(p + 1);
	if (!p)
		return (0);
	info->argv[0] = p;
	}
	return (1);
}
/**
* replace_vars - replaces vars in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *)
{
	int b;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;
		if (!_strcmp(info->argv[b], "$?"))
		{
			replace_string(&(info->argv[b]),
			_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replace_string(&(info->argv[b]),
			_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replace_string(&(info->argv[b]),
			_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[b], _strdup(""));
	}
	return (0);
}
/**
* replace_string - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
	free(*old);

	*old = new;
	return (1);
}
