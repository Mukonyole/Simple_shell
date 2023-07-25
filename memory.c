#include "shell.h"
/* Used to free allocated memory.*/

/**
 * bfree - it frees dynamically allocated memory to avoid memory leaks.
 * @ptr: pointer address to free.
 * Return: 1 if freed and 0 otherwise.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	/* checks if pointer is NULL and if pointer it points to is noy NULL.*/
	{
		free(*ptr);
		*ptr = NULL;
		return (1);/* if condition above is true*/
	}
	return (0);/* if ptr and *ptr is NULL to indicate failure.*/
}
