#include "shell.h"

/**
 * add_node - adds new node at start ol linked list
 * @head: head node address
 * @str: string value stored in a node
 * @num: interger for indexing
 * Return: new head
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)/*is head pointer not null*/
		return (NULL);
	new_head = malloc(sizeof(list_t));
	/*Allocates mem for new node */
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		/* num fied to input index value,str field duplicates input string */
		new_head->str = strdup(str);
		if (!new_head->str)
			/*linking new node to prev node head */
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	/* head pointer points to new node */
	*head = new_head;
	return (new_head);

}

/**
 * add_node_end - adds new node at end of linked list
 * @head: head node
 * @str: string stored in a node
 * @num: value of index
 * Return: new node added to list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	/* creates new node */
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	/* initialise new node */
	new_node->num = num;
	/* linking new node to prev node */
	if (str)
	{
		new_node->str = strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - print string val of each node
 * @h: first node pointer
 * Return: list size
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		/* print value of each node */
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes note at index
 * @head: head node mem address
 * @index: index of node to be deleted
 * Return: 1 success, 0 fail to delete
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all mem allocated
 * @head_ptr: head mem address
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
	/* sets head ptr to null */
}
