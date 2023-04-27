#include "shell.h"
#include <stdlib.h>
#include <string.h>
/**
* memset_fill - fills memory with a constant byte
*
* @dest: the pointer to the memory area
*
* @fill_byte: the byte to fill *dest with
*
* @num_bytes: the amount of bytes to be filled
*
* Return: (dest) a pointer to the memory area dest
*/
char *memset_fill(char *dest, char fill_byte, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
		dest[i] = fill_byte;
	return (dest);
}
/**
* free_str_arr - frees a string of strings
*
* @str_arr: string of strings
*
*/
void free_str_arr(char **str_arr)
{
	char **arr_ptr = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(arr_ptr);
}
/**
* realloc_mem - reallocates a block of memory
*
* @ptr: pointer to previous malloc'ated block
*
* @old_size: byte size of previous block
*
* @new_size: byte size of new block
*
* Return: pointer to da ol'block nameen.
*/
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
