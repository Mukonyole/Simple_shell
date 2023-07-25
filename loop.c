#include "shell.h"

/**
 * hsh - fnct that loops shell
 * @info: parameter
 * @av: argument vector
 * Return: 0 Success, 1 error
 */
int hsh(info_t *info, char **av)
	/* info_t holds info abt shell, av store cmd arguments */
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("cisisfun$ ");
		/* prompt */
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			/* process inputs */
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	/* free allocated mem */
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		/* exit exits shell  */
		exit(info->err_num);
	}
	return (builtin_ret);
	/* return result of previous command */
}

/**
 * find_builtin - search for inbuilt commands
 * @info: parameters
 * Return: 0 found, -1 not found
 */
int find_builtin(info_t *info)
{
	int a, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
	return (built_in_ret);
	/* returns val of command typed */
}

/**
 * find_cmd - searches command in PATH
 * @info: parameters
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], "\t\n"))
			b++;
	if (!b)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	/* search cmd in path */
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if (interactive(info) || _getenv(info, "PATH=" || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		/* Executes cmd if found */
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
			/* when command is not found */
		}
	}
}

/**
 * fork_cmd - creates child process to exec cmd
 * @info: parameter
 * Return: void
 */
void fork_xmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	/* create new process */
	if (child_pid == -1)
	{
		perror("Error:");
		/* if child process fails to created */
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
			/* child replace itself with cmd associated in the path */
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
			/* exit if execve fail */
		}
	}
	else
	{
		wait(&(info->status));
		/* parent wait for child proc to finish */
		if (WIFEXITED(info->status))
		{
			info->ststus = WEXITSTATUS(info->status);
			/* setting info_t to exit status of child process */
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
