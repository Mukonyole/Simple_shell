#include "shell.h"
/**
 * piped_chars_count - counts character occurance in string
 * @string: string to search
 * @c: character to search
 * Return: no of occurance of chars
 */
unsigned int piped_chars_count(char *string, char c);

unsigned int piped_chars_count(char *string, char c)
{
	unsigned int count = 0;

	while (*string != c)
	{
		count++;
		string++;
	}
	return (count + 1);
}
