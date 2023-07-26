#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char character = va_arg(types, int); /* Renamed 'c' to 'character'*/

	return (handle_write_character(character, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/

/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *input_string = va_arg(types, char *); /* Renamed 'str' to 'input_string'*/

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (input_string == NULL)
	{
		input_string = "(null)";
		if (precision >= 6)
			input_string = "      ";
	}

	while (input_string[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & FLAG_MINUS)
		{
			write(1, &input_string[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &input_string[0], length);
			return (width);
		}
	}

	return (write(1, input_string, length));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%", 1));
}

/************************* PRINT INT *************************/

/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int buffer_index = BUFF_SIZE - 2;
	int is_negative = 0;
	long int number = va_arg(types, long int); /* Renamed 'n' to 'number'*/
	unsigned long int num;

	number = convert_size_number(number, size);

	if (number == 0)
		buffer[buffer_index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)number;

	if (number < 0)
	{
		num = (unsigned long int)((-1) * number);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[buffer_index--] = (num % 10) + '0';
		num /= 10;
	}

	buffer_index++;

	return (write_number(is_negative, buffer_index, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int number, divider, i, sum; /* Renamed 'n' to 'number' and 'm' to 'divider'*/
	unsigned int binary_representation[32]; /* Renamed 'a' to 'binary_representation'*/
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	number = va_arg(types, unsigned int);
	divider = 2147483648; /* (2 ^ 31) */
	binary_representation[0] = number / divider;
	for (i = 1; i < 32; i++)
	{
		divider /= 2;
		binary_representation[i] = (number / divider) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += binary_representation[i];
		if (sum || i == 31)
		{
			char z = '0' + binary_representation[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
/*```

In this refactored version, I've made the following changes:

1. Updated comments to reflect the changes in variable names.
2. Renamed `c` to `character` in `print_char` function.
3. Renamed `str` to `input_string` in `print_string` function.
4. Renamed `n` to `number` and `m` to `divider` in `print_int` and `print_binary` functions.
5. Renamed `a` to `binary_representation` in `print_binary` function.

Remember to test the code thoroughly after refactoring to ensure it still works as expected.*/
