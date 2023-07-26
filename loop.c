#include "shell.h"

/* Used in implementing shell functions.*/

/**
 * hsh - main function that runs shell loop.
 * @info: the parameter.
 * @av: the argument vector.
 * Return: 0 on success and 1 on error.
 */
int hsh(info_t *info, char **av)
/* info_t holds information about shell state */
/* av holds command line arguments.*/
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("cisfun$ ");/* Command line.*/
		_eputchar(BUF_FLUSH);
		r = get_input(info);/* reads input from user.*/
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);/* Inputs processing.*/
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);/* write file history.*/
	free_info(info, 1);/* free up allocated memory.*/
	if (!interactive(info) && info->status)/* interactive mode on command line.*/
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);/* process ends when user enters 'exit'.*/
		exit(info->err_num);
	}
	return (builtin_ret);/* Result of last command executed.*/
}

/**
 * find_builtin - searches for a builtin command.
 * @info: the parameter.
 * Return: -1 if builtin not found and 0 if builtin is found.
 */
int find_builtin(info_t *info)
/* infor_t holds infor about commands and its arguments.*/
{
/* searches for builtin command matching first arg in argv array */
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
	return (built_in_ret);/* return value of command entered.*/
}

/**
 * find_cmd - searches for a command in PATH.
 * @info: the parameter.
 * Return: void
 */
void find_cmd(info_t *info)
/* it first check if first agruments in argv is valid.*/
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
		if (!is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	/* search for commands in a path.*/
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);/* EXecution of command if found.*/
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");/* if command not found.*/
		}
	}
}

/**
 * fork_cmd - creates a child process to execute the command.
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();/* create a new child process.*/
	if (child_pid == -1)
	{
		perror("Error:");/* if folk call fails.*/
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
/* if fork call succeed,child pid replaces its image with cmd */
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);/* if execve fails.*/
		}
	}
	else
	{
		wait(&(info->status));
		/* Parent pid wait for child pid to finish executing.*/
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
		/* sets status member of info_t to exit status of child pid.*/
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
