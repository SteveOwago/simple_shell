#include "shell.h"
/**
* strtow - splits a string into words. Repeat delimiters are ignored
*
* @input_str: the input string
*
* @del_s: the delimeter string
*
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow(char *input_str, char *del_s)
{
	int i, j, len, b, num_words = 0;
	char **words;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	if (!del_s)
		del_s = " ";
	for (i = 0; input_str[i] != '\0'; i++)
	{
		if (!is_delimiter(input_str[i], del_s) &&
			(is_delimiter(input_str[i + 1], del_s) || !input_str[i + 1]))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
	return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_del(input_str[i], del_s))
			i++;
		len = 0;
		while (!is_del(input_str[i + len], del_s) && input_str[i + len])
			len++;
		words[j] = malloc((len + 1) * sizeof(char));
		if (!words[j])
		{
			for (len = 0; len < j; len++)
				free(words[len]);
			free(words);
			return (NULL);
		}
		for (b = 0; b < lein; b++)
			words[j][b] = input_str[i++];
		words[j][b] = 0;
	}
	words[j] = NULL;
	return (words);
}
/**
* strtow2 - splits a string into words
*
* @input_str: the input string
*
* @del: the delimeter
*
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *input_str, char del)
{
	int i, j, length, b, num_wd = 0;
	char **wd;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);

	for (i = 0; input_str[i] != '\0'; i++)
	{
		if ((input_str[i] != del && input_str[i + 1] == del) ||
				(input_str[i] != del && !input_str[i + 1]) || input_str[i + 1] ==
				del)
			num_wd++;
	}
	if (num_wd == 0)
		return (NULL);
	wd = malloc((1 + num_wd) * sizeof(char *));
	if (!wd)
		return (NULL);
	for (i = 0, j = 0; j < num_wd; j++)
	{
		while (input_str[i] == del && input_str[i] != del)
			i++;
		length = 0;
		while (input_str[i + length] != del &&
			input_str[i + length] && input_str[i + length] != del)
			length++;
		wd[j] = malloc((length + 1) * sizeof(char));
		if (!wd[j])
		{
			for (length = 0; length < j; length++)
				free(wd[length]);
			free(wd);
			return (NULL);
		}
		for (b = 0; b < length; b++)
			wd[j][b] = input_str[i++];
		wd[j][b] = 0;
	}
	wd[j] = NULL;
	return (wd);
}
