#include "shell.h"
/* used to manipulates and and access environment variables */

/**
 * _myenv - it prints current environment.
 * @info: it contains arguments used to
 * maintain constant function prototype.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);/* prints each node as a string.*/
	return (0);
}

/**
 * _getenv - it access value of an environ variable.
 * @info: it contains arguments used to
 * maintain constant function prototype.
 * @name: env var name.
 * Return: the value or the string.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pointer;

	while (node)
	{
		pointer = starts_with(node->str, name);
		if (pointer && *pointer)
			return (pointer);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - it sets a new environment variable
 * or modify an existing one.
 * @info: it contains arguments used to
 * maintain constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect argc\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - it removes an environment variable.
 * @info: it contains arguments used to
 * maintain constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("few arguments.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * populate_env_list - it populates an env linked list.
 * @info: it contains arguments used to
 * maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
