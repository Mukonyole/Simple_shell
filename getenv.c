#include "shell.h"

/* It provides functions for managing environment variables.*/

/**
 * get_environ - it returns string array copy
 * of environ stored in info structure.
 * @info: contains arguments used to maintain constant function prototype.
 * Return: Always 0.
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	/* checks if struct contains environ variable or not.*/
	{
		info->environ = list_to_strings(info->env);
		/* converts linked list of environ variables to an array of strings.*/
		info->env_changed = 0;
	}

	return (info->environ);/* it returns environ field.*/
}

/**
 * _unsetenv - it removes an environ var from linked list of a structure info.
 * @info: contains arguments used to maintain constant function prototype.
 * @var: string environment variuable.
 * Return: 1 on delete and 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *b;

	if (!node || !var)
		return (0);

	while (node)
	/* checks if var string matches environment variable name.*/
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			/* deletes if a match is found.*/
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);/* value of env_changed field in info structure.*/
}

/**
 * _setenv - sets environ var to value in the linked list.
 * @info: contains arguments used to maintain constant function prototype.
 * @var: string environment variable.
 * @value: string environment variable value.
 * Return: Always 0.
 */

int _setenv(info_t *info, char *var, char *value)

{
	char *buf = NULL;
	list_t *node;
	char *b;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	/* memory allocation to a buf.*/
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	/* To check if var string matches env var name.*/
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		/*if match is found,existing node is replaced with new value.*/
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	/* if no match is found,new node is created at end of linked list.*/
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
