#include "shell.h"

/**
 * _strlen - checks length of a string
 * @s: string to be checked
 * Return: string length
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);
	/* check if ptr is null */
	while (*s++)
		a++;
	return (a);
	/* string len */
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 equal strings, else
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
		/* compare s1 and s2 */
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		/* char diff in strings */
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	/* two strings are equal */
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if s2 starts with s1
 * @haystack: string to search
 * @needle: str to find
 * Return: pnter to char following en of string
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	/* case where chars differ */
	return ((char *)haystack);
	/* if 2nd str starts with 1st str */
}

/**
 * _strcat - concanates 2 strings
 * @dest: destination
 * @src: source
 * Return: ptr to start of str
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	/* finds if dest exists */
	while (*src)
		*dest++ = *src++;
	/* append src to dest str */
	*dest = *src;
	return (ret);
}
