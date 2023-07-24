#include "shell.h"

/* functions for outputting strings and characters to standard error.*/

/**
 * _eputs - it prints error messages to user.
 * @str: string to be printed.
 * Return: Nothing
 **/
void _eputs(char *str)/* it takes a string as input */
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
/* iterating over each character until it reaches null terminator.*/
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - writes a single character to a standard error.
 * @c: The character.
 * Return: On success 1 and -1 on error.
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	/* it checks if character is BUF_FLASH constant or buffer is full */
	{
		write(2, buf, a);
	/**
	 * it writes buffer to standard error using
	 * write system call if either condition is true.
	 **/
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - it writes the character to a specified fd.
 * @c: The character.
 * @fd: The filedescriptor.
 * Return: On success 1 and -1 on error
 */
int _putfd(char c, int fd)
/* it ouputs a single character to a file other than standard error.*/
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putsfd - it prints an input string.
 * @str: the string.
 * @fd: the filedescriptor.
 * Return: number of characters.
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)/* iterating over each string .*/
	{
		a += _putfd(*str++, fd);
		/* writes it to a specified file descriptor.*/
	}
	return (a);
}
