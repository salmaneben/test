#include "main.h"

/* Function to print a character */
/**
 * print_char - Outputs a character
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        char character = va_arg(arg_list, int);

        return (handle_write_char(character, print_buffer, format_flags, format_width, format_precision, format_size));
}

/* Function to print a string */
/**
 * print_string - Outputs a string
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        int string_length = 0, index;
        char *input_string = va_arg(arg_list, char *);

        UNUSED(print_buffer);
        UNUSED(format_flags);
        UNUSED(format_width);
        UNUSED(format_precision);
        UNUSED(format_size);
        if (input_string == NULL)
        {
                input_string = "(null)";
                if (format_precision >= 6)
                        input_string = "      ";
        }

        while (input_string[string_length] != '\0')
                string_length++;

        if (format_precision >= 0 && format_precision < string_length)
                string_length = format_precision;

        if (format_width > string_length)
        {
                if (format_flags & FLAG_MINUS)
                {
                        write(1, &input_string[0], string_length);
                        for (index = format_width - string_length; index > 0; index--)
                                write(1, " ", 1);
                        return (format_width);
                }
                else
                {
                        for (index = format_width - string_length; index > 0; index--)
                                write(1, " ", 1);
                        write(1, &input_string[0], string_length);
                        return (format_width);
                }
        }

        return (write(1, input_string, string_length));
}

/* Function to print a percent sign */
/**
 * print_percent - Outputs a percent sign
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        UNUSED(arg_list);
        UNUSED(print_buffer);
        UNUSED(format_flags);
        UNUSED(format_width);
        UNUSED(format_precision);
        UNUSED(format_size);
        return (write(1, "%%", 1));
}

/* Function to print an integer */
/**
 * print_int - Outputs an integer
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        int buffer_index = BUFFER_SIZE - 2;
        int is_negative = 0;
        long int number = va_arg(arg_list, long int);
        unsigned long int num;

        number = convert_size_number(number, format_size);

        if (number == 0)
                print_buffer[buffer_index--] = '0';

        print_buffer[BUFFER_SIZE - 1] = '\0';
        num = (unsigned long int)number;

        if (number < 0)
        {
                num = (unsigned long int)((-1) * number);
                is_negative = 1;
        }

        while (num > 0)
        {
                print_buffer[buffer_index--] = (num % 10) + '0';
                num /= 10;
        }

        buffer_index++;

        return (write_number(is_negative, buffer_index, print_buffer, format_flags, format_width, format_precision, format_size));
}

/* Function to print a binary number */
/**
 * print_binary - Outputs a binary number
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_binary(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        unsigned int number, m, index, sum;
        unsigned int binary_array[32];
        int count;

        UNUSED(print_buffer);
        UNUSED(format_flags);
        UNUSED(format_width);
        UNUSED(format_precision);
        UNUSED(format_size);

        number = va_arg(arg_list, unsigned int);
        m = 2147483648; /* (2 ^ 31) */
        binary_array[0] = number / m;
        for (index = 1; index < 32; index++)
        {
                m /= 2;
                binary_array[index] = (number / m) % 2;
        }
        for (index = 0, sum = 0, count = 0; index < 32; index++)
        {
                sum += binary_array[index];
                if (sum || index == 31)
                {
                        char z = '0' + binary_array[index];

                        write(1, &z, 1);
                        count++;
                }
        }
        return (count);
}
