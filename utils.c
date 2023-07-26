#include "main.h"

/**
 * is_printable - Evaluates if a character is printable
 * @character: Character to be evaluated.
 *
 * Return: 1 if character is printable, 0 otherwise
 */
int is_printable(char character)
{
	if (character >= 32 && character < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ASCII in hexadecimal code to buffer
 * @buffer: Array of characters.
 * @index: Index at which to start appending.
 * @ascii_code: ASCII CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int index)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = map_to[ascii_code / 16];
	buffer[index] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a character is a digit
 * @character: Character to be evaluated
 *
 * Return: 1 if character is a digit, 0 otherwise
 */
int is_digit(char character)
{
	if (character >= '0' && character <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number
 */
long int convert_size_number(long int number, int size)
{
	if (size == SIZE_LONG)
		return (number);
	else if (size == SIZE_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @number: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convert_size_unsgnd(unsigned long int number, int size)
{
	if (size == SIZE_LONG)
		return (number);
	else if (size == SIZE_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}

