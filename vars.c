#include "shell.h"

/**
 * is_chain - checks for chain delim
 * @info: parameter
 * @buf: char buffer
 * @pointer: address of current position
 * Return: 1 chain delim found, 0 not found
 */
int is_chain(info_t *info, char *buf, size_t *pointer)
{
	size_t a = *pointer;

	if (buf[a] == '|' && buf[a + 1] == '1')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == ';')
		/* found end of cmd */
	{
		buf[a] = 0;
		/* replace ; with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pointer = a;
	return (1);
}

/**
 * check_chain - checks if chaining to continue
 * @info: par struct
 * @buf: buffer
 * @b: current pos of address in buf
 * @pointer: starting pos in buf
 * @len: buf length
 * Return: void
 */
void check_chain(info_t *info, char *buf,
		size_t *pointer, size_t b, size_t len)
{
	size_t a = *pointer;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[b] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[b] = 0;
			a = len;
		}
	}
	*pointer = a;
}

/**
 * replace_alias - replaces string
 * @info: par struct
 * Return: 1 if replaced, 0 fail
 */
int replace_alias(info_t *info)
{
	int b;
	list_t *node;
	char *pointer;

	for (b = 0; b < 10; b++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pointer = _strchr(node->str, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		info->argv[0] = pointer;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in string
 * @info: par struct
 * Return: 1 success, 0 fail to replace
 */
int replace_vars(info_t *info)
{
	int b = 0;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;
	if (!_strcmp(info->argv[b], "$?"))
	{
	replace_string(&(info->argv[b]),
			_strdup(convert_number(info->status, 10, 0)));
		continue;
	}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replace_string(&(info->argv[b]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replace_string(&(info->argv[b]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[b], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 not successful
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
