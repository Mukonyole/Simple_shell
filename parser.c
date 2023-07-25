#include "shell.h"

/**
 * is_cmd - check if file is executable cmd
 * @info: info struct
 * @path: file path
 * used to find and exec cmds in shell
 * Return: 1 success, 0 fail
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	/* det if path correspond to exec cmd */
	if (st.st_mode & S_IFREG)
	{
		return (1);
		/* path for regular cmd */
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 * @pathstr: path string
 * @start: start index
 * @stop: stopping index
 * Return: new buffer ptr
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - finds cmd in path
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 * Return: full path of cmd if found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
