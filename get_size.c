#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 *
 * Return: Size to cast the argument.
 */
int get_size(const char *format, int *index)
{
	int current_index = *index + 1; /* Renamed 'curr_i' to 'current_index'*/
	int size = 0;

	if (format[current_index] == 'l')
		size = SIZE_LONG;
	else if (format[current_index] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*index = current_index - 1;
	else
		*index = current_index;

	return (size);
}

