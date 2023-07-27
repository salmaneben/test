#include "main.h"

/* Function to print an unsigned number */
/**
 * print_unsigned - Outputs an unsigned number
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_unsigned(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        int buffer_index = BUFFER_SIZE - 2;
        unsigned long int num = va_arg(arg_list, unsigned long int);

        num = convert_size_unsgnd(num, format_size);

        if (num == 0)
                print_buffer[buffer_index--] = '0';

        print_buffer[BUFFER_SIZE - 1] = '\0';

        while (num > 0)
        {
                print_buffer[buffer_index--] = (num % 10) + '0';
                num /= 10;
        }

        buffer_index++;

        return (write_unsgnd(0, buffer_index, print_buffer, format_flags, format_width, format_precision, format_size));
}

/* Function to print an unsigned number in octal notation */
/**
 * print_octal - Outputs an unsigned number in octal format
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        int buffer_index = BUFFER_SIZE - 2;
        unsigned long int num = va_arg(arg_list, unsigned long int);
        unsigned long int init_num = num;

        UNUSED(format_width);

        num = convert_size_unsgnd(num, format_size);

        if (num == 0)
                print_buffer[buffer_index--] = '0';

        print_buffer[BUFFER_SIZE - 1] = '\0';

        while (num > 0)
        {
                print_buffer[buffer_index--] = (num % 8) + '0';
                num /= 8;
        }

        if (format_flags & FLAG_HASH && init_num != 0)
                print_buffer[buffer_index--] = '0';

        buffer_index++;

        return (write_unsgnd(0, buffer_index, print_buffer, format_flags, format_width, format_precision, format_size));
}

/* Function to print an unsigned number in hexadecimal notation */
/**
 * print_hexaxx - Outputs an unsigned number in hexadecimal format
 * @arg_list: List of arguments
 * @map_to: Array of values to map the number to
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @flag_ch: Flag character
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_hexaxx(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* Function to print an unsigned number in upper hexadecimal notation */
/**
 * print_hexa_vor - Outputs an unsigned number in upper hexadecimal format
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa_vor(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        return (print_hexa(arg_list, "0123456789ABCDEF", print_buffer,
                format_flags, 'X', format_width, format_precision, format_size));
}

/* Function to print a hexadecimal number in lower or upper case */
/**
 * print_hexa - Outputs a hexadecimal number in either lower or upper case
 * @arg_list: List of arguments
 * @map_to: Array of values to map the number to
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @flag_ch: Flag character
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list arg_list, char map_to[], char print_buffer[],
        int format_flags, char flag_ch, int format_width, int format_precision, int format_size)
{
        int buffer_index = BUFFER_SIZE - 2;
        unsigned long int num = va_arg(arg_list, unsigned long int);
        unsigned long int init_num = num;

        UNUSED(format_width);

        num = convert_size_unsgnd(num, format_size);

        if (num == 0)
                print_buffer[buffer_index--] = '0';

        print_buffer[BUFFER_SIZE - 1] = '\0';

        while (num > 0)
        {
                print_buffer[buffer_index--] = map_to[num % 16];
                num /= 16;
        }

        if (format_flags & FLAG_HASH && init_num != 0)
        {
                print_buffer[buffer_index--] = flag_ch;
                print_buffer[buffer_index--] = '0';
        }

        buffer_index++;

        return (write_unsgnd(0, buffer_index, print_buffer, format_flags, format_width, format_precision, format_size));
}
