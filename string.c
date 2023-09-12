#include "main.h"

/**
 * _strlen - return the length of a string
 * @str: is the str
 *
 * Return: return int
 */
int _strlen(char *str)
	{
		int i = 0;

		if (!str)
			return (i);
		while (str[i] != '\0')
			i++;

		return (i);
	}

/**
 * *_strcpy - return if two strings are equal
 * @str1: is the str1
 * @str2: is the str2
 *
 * Return: return int
 */
char *_strcpy(char *str1, char *str2)
{

	int i = 0;

	if (str1 == str2 || str2 == 0)
		return (str1);
	while (str2[i] != '\0')
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = str2[i];
	return (str1);
}

/**
 * _strcmp - two strings are equal
 * @s1: is the str1
 * @s2: is the str2
 *
 * Return: return int
 */

int _strcmp(char *s1, char *s2)
{
int i = 0;
while (s1[i] == s2[i])
{
if (s1[i] == '\0' || s2[i] == '\0')
	return (0);
i++;
}
return (s1[i] - s2[i]);
}

/**
 * *starts_with - two strings are equal
 * @str: is the str1
 * @needle: is the str2
 *
 * Return: return int
 */

char *starts_with(const char *str, const char *needle)
{
while (*needle)
	if (*needle++ != *str++)
		return (NULL);
return ((char *)str);

}

