#include "main.h"

/* Function to print the value of a pointer variable */
/**
 * print_pointer - Outputs the value of a pointer variable
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_pointer(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        char extra_char = 0, padding_char = ' ';
        int buffer_index = BUFFER_SIZE - 2, output_length = 2, padding_start = 1; /* length=2, for '0x' */
        unsigned long address_num;
        char map_to[] = "0123456789abcdef";
        void *address = va_arg(arg_list, void *);

        UNUSED(format_width);
        UNUSED(format_size);

        if (address == NULL)
                return (write(1, "(nil)", 5));

        print_buffer[BUFFER_SIZE - 1] = '\0';
        UNUSED(format_precision);

        address_num = (unsigned long)address;

        while (address_num > 0)
        {
                print_buffer[buffer_index--] = map_to[address_num % 16];
                address_num /= 16;
                output_length++;
        }

        if ((format_flags & FLAG_ZERO) && !(format_flags & FLAG_MINUS))
                padding_char = '0';
        if (format_flags & FLAG_PLUS)
                extra_char = '+', output_length++;
        else if (format_flags & FLAG_SPACE)
                extra_char = ' ', output_length++;

        buffer_index++;

        return (write_pointer(print_buffer, buffer_index, output_length,
                format_width, format_flags, padding_char, extra_char, padding_start));
}

/* Function to print ascii codes in hexa of non printable characters */
/**
 * print_non_printable - Outputs ascii codes in hexadecimal of non printable characters
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        int char_index = 0, offset = 0;
        char *input_string = va_arg(arg_list, char *);

        UNUSED(format_flags);
        UNUSED(format_width);
        UNUSED(format_precision);
        UNUSED(format_size);

        if (input_string == NULL)
                return (write(1, "(null)", 6));

        while (input_string[char_index] != '\0')
        {
                if (is_printable(input_string[char_index]))
                        print_buffer[char_index + offset] = input_string[char_index];
                else
                        offset += append_hexa_code(input_string[char_index], print_buffer, char_index + offset);

                char_index++;
        }

        print_buffer[char_index + offset] = '\0';

        return (write(1, print_buffer, char_index + offset));
}

/* Function to print a reverse string */
/**
 * print_reverse - Outputs a reversed string
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_reverse(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        char *input_string;
        int string_index, char_count = 0;

        UNUSED(print_buffer);
        UNUSED(format_flags);
        UNUSED(format_width);
        UNUSED(format_size);

        input_string = va_arg(arg_list, char *);

        if (input_string == NULL)
        {
                UNUSED(format_precision);

                input_string = ")Null(";
        }
        for (string_index = 0; input_string[string_index]; string_index++)
                ;

        for (string_index = string_index - 1; string_index >= 0; string_index--)
        {
                char z = input_string[string_index];

                write(1, &z, 1);
                char_count++;
        }
        return (char_count);
}

/* Function to print a string in rot13 */
/**
 * print_rot13string - Outputs a string in rot13
 * @arg_list: List of arguments
 * @print_buffer: Buffer array for handling print operations
 * @format_flags:  Flags for controlling the format
 * @format_width: Width of the output
 * @format_precision: Precision of the output
 * @format_size: Size specifier
 * Return: Number of characters printed
 */
int print_rot13string(va_list arg_list, char print_buffer[],
        int format_flags, int format_width, int format_precision, int format_size)
{
        char x;
        char *input_string;
        unsigned int i, j;
        int char_count = 0;
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

        input_string = va_arg(arg_list, char *);
        UNUSED(print_buffer);
        UNUSED(format_flags);
        UNUSED(format_width);
        UNUSED(format_precision);
        UNUSED(format_size);

        if (input_string == NULL)
                input_string = "(AHYY)";
        for (i = 0; input_string[i]; i++)
        {
                for (j = 0; in[j]; j++)
                {
                        if (in[j] == input_string[i])
                        {
                                x = out[j];
                                write(1, &x, 1);
                                char_count++;
                                break;
                        }
                }
                if (!in[j])
                {
                        x = input_string[i];
                        write(1, &x, 1);
                        char_count++;
                }
        }
        return (char_count);
}
