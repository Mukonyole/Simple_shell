#include "shell.h"

/* It implements command history feature for a shell program.*/

/**
 * get_history_file - it retrieves history file location.
 * @info: parameter struct.
 * Return: allocated string containing history file.
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");/* Retrieves users home directory.*/
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
/* Allocates memory to a buffer and concatenates home directory path */
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);/*.It returns the buffer.*/
}

/**
 * write_history - it writes shell command's history to a file.
 * @info: parameter struct.
 * Return: 1 on success and -1 otherwise.
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	/* To retrieve full path of history file.*/
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	/* It creates file with specific permissions and opens in r-w mode.*/
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
/* writes each node's string followed by a new line character to the file.*/
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);/*. To flush the buffer.*/
	close(fd);/* Closes file and returns 1 on success and -1 on failure.*/
	return (1);
}

/**
 * read_history - it reads shell's command history from a file.
 * @info: parameter struct.
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);
	/* To retrieve full path of history file.*/

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);/* opens file in read only mode*/
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))/*.Retrieves its size.*/
		fsize = st.st_size;
	if (fsize < 2)
		return (0);/* Returns 0 if file is less that 2 bytes.*/
	buf = malloc(sizeof(char) * (fsize + 1));/* Allocates buffer*/
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);/*Closes file after reading it and parses buffer line by line.*/
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, buf + last, linecount++);
	free(buf);/* frees the buffer.*/
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);/*renumber nodes history linked list*/
	return (info->histcount);
}


/**
 * build_history_list - It adds a line to shell's command history.
 * @info: contains arguments used to maintain constant function prototype.
 * @buf: buffer.
 * @linecount: linecount.
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	/* creates new node and adds it at the end of history linked list.*/

	if (!info->history)
		info->history = node;
/* sets history field of info to new node if linked list history is empty.*/
	return (0);
}

/**
 * renumber_history - it renumbers history linked list after changes.
 * @info: contains arguments used to maintain constant function prototype.
 * Return: new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);/* It returns a new histcount.*/
}
