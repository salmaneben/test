#include "main.h"

/* Function to calculate the width for printing */
/**
 * get_width - Determines the width for output
 * @format_string: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 * @arg_list: List of arguments
 *
 * Return: Width.
 */
int get_width(const char *format_string, int *index, va_list arg_list)
{
	int current_index;
	int width = 0;

	for (current_index = *index + 1; format_string[current_index] != '\0'; current_index++)
	{
		if (is_digit(format_string[current_index]))
		{
			width *= 10;
			width += format_string[current_index] - '0';
		}
		else if (format_string[current_index] == '*')
		{
			current_index++;
			width = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}

	*index = current_index - 1;

	return (width);
}

