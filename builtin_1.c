#include "shell.h"

/**
 * _myhistory - displays history list.
 * @info: contains arguments used to
 * maintain constant function prototype.
 *  Return: Always 0.
 */
int _myhistory(info_t *info)
/* it takes structure info_t as input and returns an integer value */
/* it displays history list from the latest command */

{
	print_list(info->history);
	return (0);
}

/**
* unset_alias - it sets alias to a tring.
* @info: the struct parameter.
* @str: the string alias.
* Return: 0 on success and 1 on error.
*/

int unset_alias(info_t *info, char *str)
/* it sets an alias to a string */
{
	char *b, j;
	int ret;

	b = _strchr(str, '=');
	/* searches for the position of a character */
	if (!b)
		return (1);/* if it does not find character */
	j = *b;
	*b = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = j;
	return (ret);/* value returned by delete_node_at_index*/
}

/**
 * set_alias - sets alias to string.
 * @info: parameter struct.
 * @str: string alias.
 * Return: Always 0 on success and 1 on error.
 */
int set_alias(info_t *info, char *str)
/* it takes pointer info_t as input and returns integer*/
{
	char *b;

	b = _strchr(str, '='); /*search for position of a character*/
	if (!b)
		return (1);/* if no character is found*/
	if (!*++b)
		return (unset_alias(info, str));
	/* if character immediately after = is empty*/

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
	/* adds node to the end of alias list */
}

/**
 * print_alias - prints an alias string.
 * @node: alias node.
 * Return: Always 0 on success and 1 on error.
 */
int print_alias(list_t *node)
/* takes list_t pointer as input and returns integer value.*/
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		/* searches for position of character*/
		for (a = node->str; a <= b; a++)
		_putchar(*a);/* it prints string using putchar if found */
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);/* if node is null and vice versa */
}

/**
 * _myalias - it creates and manipulates aliases in a shell.
 * @info: contains arguments used to
 * maintain constant function prototype.
 *  Return: Always 0.
 */
int _myalias(info_t *info)
{
	int c = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (c = 1; info->argv[c]; c++)
	{
		b = _strchr(info->argv[c], '=');
		if (b)
		set_alias(info, info->argv[c]);
		else
		print_alias(node_starts_with(info->alias, info->argv[c], '='));
	}

	return (0);
}
