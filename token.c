#include "shell.h"

/**
 * strtow - splint string into letters
 * @str: input string
 * @d: delimiter
 * Return: pointer to array of string
 */
char **strtow(char *str, char *d)
{
	int a, b, c, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	/* check if string is empty */
	if (!d)
		d = "";
	/* no delim, fallback to space character */
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;
	/* count no. of words in string */
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	/* allocating mem for words counted */
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
 * strtow2 - split string into words
 * @str: i/p string
 * @d: delimeter
 * Return: pointer to array of string/null on fail
 */
char **strtow2(char *str, char d)
{
	int a, b, c, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
	       if((str[a] != d && str[a + 1] == d) || (str[a] != d && !str[a + 1]) || str[a + 1] == d)
		       numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	/* allocating mem for array of strings */
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
	s[b] = NULL;
	/* inserting null delim at end of every string */
	return (s);
}
