#include "shell.h"

/* split string into array of words based on a specified delimiter.*/

/**
 * **strtow - splits a string into words.
 * @str: input string.
 * @d: the delimeter.
 * Return: a pointer to an array of strings
 */

char **strtow(char *str, char *d)
{
	int a, b, c, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);/* if string is empty.*/
	if (!d)
		d = " ";/* if d is NULL, it defaults to a space character.*/
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;/* Counts number of words in inputr string.*/

	if (numwords == 0)
		return (NULL);/* if no words in the string.*/
	s = malloc((1 + numwords) * sizeof(char *));
	/* memory allocation based on number of words counted.*/
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - it splits a string into words.
 * @str: input string.
 * @d: the delimeter.
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, b, c, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);/* if no words in the string.*/
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	/* memory allocation to array of strings.*/
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;/* add null delimiter to end of every string.*/
	return (s);
}
