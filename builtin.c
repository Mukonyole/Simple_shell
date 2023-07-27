#include "shell.h"

/**
 * _myexit - it exits the shell.
 * @info: it contains arguments which is used to
 * maintain constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])/* If an argument passed to the function */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);/* if no argument, it sets err_num to -1 and returns -2 */
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - it changes current directory of the process.
 * @info: it contains arguments which is used
 * to maintain constant function prototype.
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *a, *dir, buffer[1024];
	int chdir_ret;

	a = getcwd(buffer, 1024); /* getting current working directory */
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");/*if no arg is passed */
		if (!dir)
			chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);/* it changes directory to obtained directory */
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - it changes current directory of a process.
 * @info: it contains arguments which is used
 * to maintain constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info) /* it takes a pointer info_t as an argument */
{
	char **arg_array;

	arg_array = info->argv; /* assigning information to argv */
	_puts("Function not found \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
