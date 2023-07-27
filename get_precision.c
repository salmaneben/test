#include "main.h"

/* Function to calculate the precision for printing */
/**
 * get_precision - Determines the precision for output
 * @format_string: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 * @arg_list: List of arguments
 *
 * Return: Precision.
 */
int get_precision(const char *format_string, int *index, va_list arg_list)
{
	int current_index = *index + 1;
	int precision = -1;

	if (format_string[current_index] != '.')
		return (precision);

	precision = 0;

	for (current_index += 1; format_string[current_index] != '\0'; current_index++)
	{
		if (is_digit(format_string[current_index]))
		{
			precision *= 10;
			precision += format_string[current_index] - '0';
		}
		else if (format_string[current_index] == '*')
		{
			current_index++;
			precision = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}

	*index = current_index - 1;

	return (precision);
}

