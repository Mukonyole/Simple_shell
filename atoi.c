#include "shell.h"

/**
 * interactive - it checks if shell is ruunning in interactive mode.
 * @info: The struct address.
 * Return: 1 if in interactive mode while 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - it checks if character is a delimeter
 * by comparing it to each character in delim string until it finds a match.
 * @c: the character to check.
 * @delim: the delimeter string.
 * Return: 1 if match is found and 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);/* Returns 1 if match is found */
	return (0);/* otherwise */
}

/**
 * _isalpha - it checks if a given character c is an alphabet or not.
 * @c: The input character.
 * Return: 1 if character is an alphabet or 0 otherwise.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - it converts a string to an integer.
 * @s: the string to be converted
 * Return: 0 if no numeric character is found and a converted number otherwise.
 */

int _atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;
	/**
	 * if numeric numeric char is found, it multiplies existing value by 10
	 * and adds value of new digit.
	 *
	  **/
		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result; /* if negative sign is found, final result is negated. */
	else
		output = result;
	return (output); /* returns coverted number otherwise */
}
