#include "shell.h"

/* used for getting inputs from the user through command line interface. */

/**
 * input_buf - stores inputs from user.
 * @info: parameters
 * @buf: buffer address.
 * @len: len var address.
 * Return: number of bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
/* buffers chained commands entered by user in command line interface.*/
{
	ssize_t c = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
	#if USE_GETLINE
		c = getline(buf, &len_p, stdin);
	#else
		c = _getline(info, buf, &len_p);
	#endif
		if (c > 0)
		{
			if ((*buf)[c - 1] == '\n')
			{
				(*buf)[c - 1] = '\0'; /* remove trailing newline */
				c--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = c;
				info->cmd_buf = buf;
			}
		}
	}
	return (c);
}

/**
 * get_input - it gets a line minus newline character.
 * @info: parameter.
 * Return: number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, len;
	ssize_t c = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	c = input_buf(info, &buf, &len);
	if (c == -1) /* an EOF */
		return (-1);
	if (len) /* commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		p = buf + a; /* getting a pointer for return */

		check_chain(info, buf, &b, a, len);
		while (b < len) /* iterating to a semicolon or end */
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increament past nulled ';'' */
		if (a >= len) /* end of buffer? */
		{
			a = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (c); /* length of buffer from _getline() */
}

/**
 * read_buf - it reads buffer.
 * @info: parameter.
 * @buf: buffer.
 * @a: size.
 * Return: c
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
	ssize_t c = 0;

	if (*a)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*a = c;
	return (c);
}

/**
 * _getline - it gets next line of input from STDIN.
 * @info: parameter.
 * @ptr: address of pointer to buffer.
 * @length: size of ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t d;
	ssize_t c = 0, s = 0;
	char *p = NULL, *new_p = NULL, *e;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	c = read_buf(info, buf, &len);
	if (c == -1 || (c == 0 && len == 0))
		return (-1);

	e = _strchr(buf + a, '\n');
	d = c ? 1 + (unsigned int)(e - buf) : len;
	new_p = _realloc(p, s, s ? s + d : d + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, d - a);
	else
		_strncpy(new_p, buf + a, d - a + 1);
	s += d - a;
	a = d;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - it blocks ctrl-C used to interrupt running process.
 * @sig_num: signal number.
 * Return: void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
/* it prevents user from accidentally terminating the shell.*/
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
