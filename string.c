#include "shell.h"
/**
* get_string_length - returns the length of a string
*
* @str: the string whose length to check
*
* Return: integer length of string
*/
int get_string_length(char *str)
{
	int length = 0;

	if (!str)
	{
		printf("Error: string is NULL\n");
		return (0);
	}
	while (*str++)
	{
		length++;
	}
	return (length);
}
/**
* compare_strings - performs lexicogarphic comparison of two strangs.
*
* @str1: the first strang
*
* @str2: the second strang
*
* Return: if str1 < str2, positive if str1 > str2, zero if str1 == str2
*/
int compare_strings(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
* string_starts_with - checks if needle starts with haystack

* @haystack: string to search
*
* @needle: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
* _strcat - concatenates two strings
*
* @dest: the destination buffer
*
* @src: the source buffer
*
* Return: pointer to destination buffer
*/
char *strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
