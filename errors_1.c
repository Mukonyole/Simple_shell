#include "shell.h"

/**
 * _erratoi - it converts a string to an integer.
 * @s: the string.
 * Return: Converted number,0 if no numbers found in string and -1 on error.
 */
int _erratoi(char *s)/* it takes a string an input.*/
{
	int a = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			result *= 10;
			result += (s[a] - '0');
			if (result > INT_MAX)
				return (-1);
	/* it returns -1 if string does not contain numbers.*/
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints error to standard output.
 * @info: parameter and return information.
 * @estr: string with error type.
 * Return: converted number,0 if no numbers in string and -1 on error.
 */
void print_error(info_t *info, char *estr)
/* It takes two parameters,info structure and estr as string.*/
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - it prints a decimal (integer) number to a file descriptor.
 * @input: input.
 * @fd: the filedescriptor.
 * Return: number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - it converts a number to astring in a specified base.
 * @num: number.
 * @base: base.
 * @flags: argument flags.
 * Return: pointer to a converted string.
 */
char *convert_number(long int num, int base, int flags)
/*takes number,base and flags showing if number is signed or unsigned.*/
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - it replaces first instance of '#' with '\0'.
 * @buf: string address to modify.
 * Return: Always 0.
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
