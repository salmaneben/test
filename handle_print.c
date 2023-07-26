#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @args: List of arguments to be printed.
 * @index: Pointer to the current index in the format string
 * @buffer: Buffer array to handle print.
 * @flags: Active flags
 * @width: Width for printing
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: 1 or 2;
 */
int handle_print(const char *format, int *index, va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_length = 0, printed_chars = -1; /* Renamed 'unknow_len' to 'unknown_length'*/
	format_t format_types[] = { /* Renamed 'fmt_types' to 'format_types'*/
		{'c', print_character}, {'s', print_string}, {'%', print_percent},
		{'i', print_rot13}, {'d', print_rot13}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_string}, {'\0', NULL}
	};
	for (i = 0; format_types[i].fmt != '\0'; i++)
		if (format[*index] == format_types[i].fmt)
			return (format_types[i].fn(args, buffer, flags, width, precision, size));

	if (format_types[i].fmt == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_length += write(1, &format[*index], 1);
		return (unknown_length);
	}
	return (printed_chars);
}

