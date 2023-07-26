#include "main.h"

/* Function to print the contents of the buffer if it exists */
void print_buffer_content(char buffer[], int *buffer_index);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, num_printed = 0, total_chars_printed = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == BUFF_SIZE)
				print_buffer_content(buffer, &buffer_index);
			total_chars_printed++;
		}
		else
		{
			print_buffer_content(buffer, &buffer_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			num_printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (num_printed == -1)
				return (-1);
			total_chars_printed += num_printed;
		}
	}

	print_buffer_content(buffer, &buffer_index);

	va_end(list);

	return (total_chars_printed);
}

/**
 * print_buffer_content - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buffer_index: Index at which to add next char, represents the length.
 */
void print_buffer_content(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}

