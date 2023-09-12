#include "main.h"


/**
 * _memset - This will convert ascii number into char
(* a blank line
 * Description: by placing %c instead of %d, the number will be converted)?
(* section header: Section description)*
 * @s: is a string
 * @b: is a char
 * @n: is an int
 * Return: just return 0 for ok
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
{
s[i] = b;
}
return (s);
}

/**
 ** ffree - free an array of strings
 * @str: is an array of str
 *
 * Return: return int
 */
void ffree(char **str)
{
	char **a = str;

	if (!str)
		return;
	while (**str)
		free(*str++);
	free(a);
}


/**
 * _realloc - return if two strings are equal
 * @old: is the str1
 * @new: is the str2
 * @ptr: is a ptr
 *
 * Return: return int
 */
void *_realloc(void *ptr, unsigned int old, unsigned int new)
{

	char *p;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);
	p = malloc(new);
	if (!p)
		return (NULL);
	old = old < new ? old : new;
	while (old--)
	{
		p[old] = ((char *)ptr)[old];
	}
	free(ptr);
	return (p);
}

/**
 * bfree - two strings are equal
 * @ptr: is the str1
 *
 * Return: return int
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * interactive - two strings are equal
 * @info: is the str1
 *
 * Return: return int
 */

int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);

}
