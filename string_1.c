#include "shell.h"

/**
 * _strcpy - copy src str to dest str
 * @dest: destination
 * @src: source
 * Return: ptr to dest
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		/* check if src and dest are same */
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
		/* copies each char to dest */
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - duplicates str
 * @str: string
 * Return: ptr to dup str
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		/* det len of str */
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	/* mem for new str */
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
	/* ptr to new str */

}

/**
 * _puts - print i/p str
 * @str: str
 * Return: 0
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
		/* prints each char */
	}
}

/**
 * _putchar - sends chars to console
 * @c: character
 * Return: 1 success, -1 error
 */
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
		/* checks if char is flush char */
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
	/* if char is not flush char */
}
