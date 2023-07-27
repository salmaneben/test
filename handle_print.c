#include "main.h"

/* Function to print an argument based on its type */
/**
 * handle_print - Outputs an argument based on its type
 * @format_string: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags: Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *format_string, int *index, va_list arg_list, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size)
{
	int i, unknown_length = 0, printed_chars = -1;
	format_t format_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexaxx},
		{'X', print_hexa_vor}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; format_types[i].format != '\0'; i++)
		if (format_string[*index] == format_types[i].format)
			return (format_types[i].benx(arg_list, print_buffer, format_flags, format_width, format_precision, format_size));

	if (format_types[i].format == '\0')
	{
		if (format_string[*index] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (format_string[*index - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (format_width)
		{
			--(*index);
			while (format_string[*index] != ' ' && format_string[*index] != '%')
				--(*index);
			if (format_string[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_length += write(1, &format_string[*index], 1);
		return (unknown_length);
	}
	return (printed_chars);
}

