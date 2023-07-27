#include "main.h"

/* Function to calculate the size to cast the argument */
/**
 * get_size - Determines the size to cast the argument
 * @format_string: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 *
 * Return: Size.
 */
int get_size(const char *format_string, int *index)
{
	int current_index = *index + 1;
	int size = 0;

	if (format_string[current_index] == 'l')
		size = SIZE_LONG;
	else if (format_string[current_index] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*index = current_index - 1;
	else
		*index = current_index;

	return (size);
}

