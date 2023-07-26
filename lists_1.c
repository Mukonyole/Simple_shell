#include "shell.h"

/* It defines sets of functions for manipulating linked lists.*/

/**
 * list_len - it determines length of a linked list.
 * @h: first node pointer.
 * Return: list size.
 */

size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - it finds an array of strings corresponding
 * to each str member of a node in a string.
 * @head: first node pointer.
 * Return: an array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		/* memory allocation to array of strings.*/
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		/* copies string from current node's str member.*/
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}

/**
 * print_list - it prints contents of a linked list.
 * @h: first node pointer.
 * Return: list size.
 */

size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
/* iterates through list printing node's num member,colon and space char.*/
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);/* size of the list.*/
}

/**
 * node_starts_with - it returns a node whose string starts with prefix.
 * @node: list head pointer.
 * @prefix: string to match
 * @b: next character after prefix to match.
 * Return: match node or null.
 */
list_t *node_starts_with(list_t *node, char *prefix, char b)
{
	char *pointer = NULL;

	while (node)
	{
		pointer = starts_with(node->str, prefix);
	/* To determine if current node's str member starts with a prefix.*/
		if (pointer && ((b == -1) || (*pointer == b)))
			return (node);/* if nodes matches.*/
		node = node->next;
	}
	return (NULL);/* if no node matches.*/
}

/**
 * get_node_index - it gets an index of a node.
 * @head: list head pointer.
 * @node: node pointer.
 * Return: index of node and -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	/* compare each node to a provided node.Returns index if it matches.*/
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);/* if no node matches.*/
}
