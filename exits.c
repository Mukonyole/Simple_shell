#include "shell.h"

/**
 **_strncpy - it copies a string
 *@dest: destination of string.
 *@src: source of string.
 *@n: amount of chars to copy.
 *Return: concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - it concatenates two strings.
 *@dest: first string.
 *@src: second string.
 *@n: bytes to be used.
 *Return: concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	/* if b is less than n, function adds null character to end of dest.*/
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - it locates a character in a string.
 *@s: the string.
 *@c: the character.
 *Return: a pointer to the memory area.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);/* if character c is foundin string s.*/
	} while (*s++ != '\0');

	return (NULL);/* if end of s is reached and c has not been founs.*/
}
