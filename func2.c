#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width of the output
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_character = 0, padding = ' '; /* Renamed 'extra_c' to 'extra_character' and 'padd' to 'padding'*/
	int buffer_index = BUFF_SIZE - 2, length = 2, padding_start = 1; /* Renamed 'i' to 'buffer_index'*/
	unsigned long address_number; /* Renamed 'num_addrs' to 'address_number*/
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *); /* Renamed 'addrs' to 'address'*/

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	address_number = (unsigned long)address;

	while (address_number > 0)
	{
		buffer[buffer_index--] = map_to[address_number % 16];
		address_number /= 16;
		length++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';
	if (flags & FLAG_PLUS)
		extra_character = '+', length++;
	else if (flags & FLAG_SPACE)
		extra_character = ' ', length++;

	buffer_index++;

	return (write_pointer(buffer, buffer_index, length,
		width, flags, padding, extra_character, padding_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width of the output
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = 0, offset = 0; /* Renamed 'i' to 'index'*/
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[index] != '\0')
	{
		if (is_printable(str[index]))
			buffer[index + offset] = str[index];
		else
			offset += append_hexa_code(str[index], buffer, index + offset);

		index++;
	}

	buffer[index + offset] = '\0';

	return (write(1, buffer, index + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width of the output
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int index, count = 0; /* Renamed 'i' to 'index'*/

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (index = 0; str[index]; index++)
		;

	for (index = index - 1; index >= 0; index--)
	{
		char character = str[index]; /* Renamed 'z' to 'character'*/

		write(1, &character, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width of the output
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char character; /* Renamed 'x' to 'character'*/
	char *str;
	unsigned int index, j; /* Renamed 'i' to 'index'*/
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (index = 0; str[index]; index++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[index])
			{
				character = out[j];
				write(1, &character, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			character = str[index];
			write(1, &character, 1);
			count++;
		}
	}
	return (count);
}

