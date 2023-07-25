#include "shell.h"

/**
 * _memset - it fills a memory with a given value.
 * @s: memory area pointer.
 * @b: the byte.
 * @n: amount of bytes.
 * Return: memory block pointer.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

/* uses for loop to fill each byte of memory block with a given value.*/
	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - it frees a string of strings.
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - it reallocates a block of memory.
 * @ptr: pointer to previous block of memory.
 * @old_size: bytes size of previous block.
 * @new_size: byte size of new block.
 * Return: pointer to new block of memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);/*It firts check if pointer is null.*/
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);/* if new size is zero,it frees previous block of memory.*/

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
