# _printf - Custom printf Implementation

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![C Standard](https://img.shields.io/badge/C-89/90-blue.svg)]()
[![License](https://img.shields.io/badge/license-MIT-green.svg)]()

## 📖 Description

This project is a custom implementation of the C standard library `printf` function. The `_printf` function produces output according to a format string and writes output to stdout, the standard output stream. This implementation handles various format specifiers and provides comprehensive formatting options similar to the standard printf function.

## 🎯 Project Goals

- **Educational Purpose**: Understanding how printf works internally
- **Format Specifier Implementation**: Supporting multiple format specifiers
- **Memory Management**: Efficient buffer handling and memory usage
- **Error Handling**: Proper error checking and validation
- **Code Modularity**: Well-organized, readable, and maintainable code

## ✨ Features

### Supported Format Specifiers

| Specifier | Description | Example |
|-----------|-------------|---------|
| `%c` | Character | `_printf("%c", 'A')` → A |
| `%s` | String | `_printf("%s", "Hello")` → Hello |
| `%d` / `%i` | Decimal/Integer | `_printf("%d", 123)` → 123 |
| `%u` | Unsigned integer | `_printf("%u", 123u)` → 123 |
| `%o` | Octal | `_printf("%o", 8)` → 10 |
| `%x` | Hexadecimal (lowercase) | `_printf("%x", 255)` → ff |
| `%X` | Hexadecimal (uppercase) | `_printf("%X", 255)` → FF |
| `%p` | Pointer | `_printf("%p", ptr)` → 0x7fff... |
| `%b` | Binary | `_printf("%b", 5)` → 101 |
| `%S` | Non-printable characters | Special string handling |
| `%r` | Reverse string | `_printf("%r", "Hello")` → olleH |
| `%R` | ROT13 string | `_printf("%R", "Hello")` → Uryyb |
| `%%` | Literal % | `_printf("%%")` → % |

### Format Modifiers

- **Flags**: `-`, `+`, `0`, `#`, ` ` (space)
- **Width**: Minimum field width
- **Precision**: Precision for numbers and strings
- **Length**: `l` (long), `h` (short)

## 📁 Project Structure

```
.
├── main.h              # Header file with function prototypes and definitions
├── printf.c            # Main _printf function implementation
├── main.c              # Test file demonstrating usage
├── handle_print.c      # Format specifier handler and dispatcher
├── func1.c             # Number format implementations (unsigned, octal, hex)
├── func2.c             # Pointer, special string, and ROT13 implementations
├── get_flags.c         # Flag parsing (-,+,0,#,' ')
├── get_width.c         # Width parsing
├── get_precision.c     # Precision parsing
├── get_size.c          # Size modifier parsing (l,h)
├── write_hand.c        # Output writing and formatting handlers
├── utils.c             # Utility functions
├── a.out               # Compiled executable
└── README.md           # This file
```

## 🔧 Core Components

### 1. Main Function (`printf.c`)
- **`_printf()`**: Main function that processes format string
- **`print_to_buffer()`**: Buffer management for efficient output

### 2. Format Handler (`handle_print.c`)
- Central dispatcher for different format specifiers
- Maps format characters to their corresponding functions
- Handles unknown format specifiers

### 3. Numeric Converters (`func1.c`)
- **`print_unsigned()`**: Unsigned decimal numbers
- **`print_octal()`**: Octal representation
- **`print_hexaxx()`**: Lowercase hexadecimal
- **`print_hexa_vor()`**: Uppercase hexadecimal
- **`print_hexa()`**: Generic hexadecimal conversion

### 4. Special Handlers (`func2.c`)
- **`print_pointer()`**: Memory address formatting
- **`print_non_printable()`**: Non-printable character handling
- **`print_reverse()`**: String reversal
- **`print_rot13string()`**: ROT13 cipher encoding

### 5. Format Parsers
- **`get_flags.c`**: Parse formatting flags
- **`get_width.c`**: Parse field width
- **`get_precision.c`**: Parse precision specifier
- **`get_size.c`**: Parse length modifiers

### 6. Write Handlers (`write_hand.c`)
- **`handle_write_char()`**: Character output with formatting
- **`write_number()`**: Number output with formatting
- **`write_unsgnd()`**: Unsigned number formatting
- **`write_pointer()`**: Pointer address formatting

### 7. Utilities (`utils.c`)
- **`is_printable()`**: Check if character is printable
- **`append_hexa_code()`**: Append hex codes for non-printable chars
- **`is_digit()`**: Digit validation
- **`convert_size_number()`**: Type casting for size modifiers

## 🚀 Usage

### Basic Usage

```c
#include "main.h"

int main(void)
{
    _printf("Hello, %s!\n", "World");
    _printf("Number: %d\n", 42);
    _printf("Hex: %x\n", 255);
    return (0);
}
```

### Advanced Formatting

```c
#include "main.h"

int main(void)
{
    // Width and precision
    _printf("Width: '%10s'\n", "test");
    _printf("Precision: '%.2f'\n", 3.14159);
    
    // Flags
    _printf("Left-aligned: '%-10s'\n", "test");
    _printf("Zero-padded: '%010d'\n", 42);
    _printf("With sign: '%+d'\n", 42);
    
    // Special specifiers
    _printf("Binary: %b\n", 42);
    _printf("Reverse: %r\n", "Hello");
    _printf("ROT13: %R\n", "Hello");
    
    return (0);
}
```

## 🔨 Compilation

### Standard Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o printf_test
```

### With Debug Information
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -g *.c -o printf_test
```

### Using Makefile (if available)
```bash
make
```

## 🧪 Testing

### Running Tests
```bash
./a.out
```

### Test Coverage
The `main.c` file includes comprehensive tests for:
- Basic format specifiers
- Character and string handling
- Numeric conversions (decimal, octal, hex)
- Pointer formatting
- Edge cases and error handling

### Sample Output
```
Let's try to printf a simple sentence.
Length:[39, 39]
Negative:[-762534]
Unsigned:[2147484671]
Unsigned octal:[20000001777]
Unsigned hexadecimal:[80000fff, 80000FFF]
Character:[H]
String:[I am a string !]
Address:[0x7ffe637541f0]
Percent:[%]
```

## 🏗️ Implementation Details

### Buffer Management
- Uses a 1024-byte buffer for efficient output
- Automatically flushes buffer when full
- Minimizes system calls for better performance

### Error Handling
- Returns -1 on error conditions
- Handles NULL format strings
- Validates format specifiers

### Memory Efficiency
- Stack-based buffer allocation
- No dynamic memory allocation
- Efficient string processing

### Code Standards
- Follows Betty coding style
- ANSI C (C89/C90) compliant
- Comprehensive documentation
- Modular design

## 📊 Performance Characteristics

- **Time Complexity**: O(n) where n is the length of the format string
- **Space Complexity**: O(1) with fixed-size buffer
- **Buffer Size**: 1024 bytes
- **Max Format String**: Limited by available memory

## 🔍 Key Algorithms

### Format String Parsing
1. Iterate through format string character by character
2. Handle literal characters directly
3. Parse format specifiers starting with '%'
4. Extract flags, width, precision, and size modifiers
5. Dispatch to appropriate formatting function

### Number Conversion
1. Convert number to string representation in target base
2. Apply formatting (padding, precision, flags)
3. Write to buffer with proper alignment

### Buffer Management
1. Accumulate output in buffer
2. Flush buffer when full or at end of processing
3. Handle buffer overflow gracefully

## 🐛 Known Issues

- Some edge cases with extreme precision values may not be handled
- Limited support for floating-point numbers
- The `func.c` file contains unrelated Pine Script code and should be removed

## 📚 Educational Value

This project demonstrates:
- **Variadic Functions**: Using `va_list`, `va_start`, `va_arg`, `va_end`
- **String Manipulation**: Character-by-character processing
- **Format Parsing**: State machine-like parsing logic
- **Modular Programming**: Well-organized function structure
- **System Calls**: Direct use of `write()` system call
- **Type Conversion**: Number base conversion algorithms
- **Memory Management**: Efficient buffer usage

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Follow the coding standards
4. Add tests for new features
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 👥 Authors

- **Development Team**: ALX Software Engineering Program
- **Educational Context**: System Programming and Algorithm Implementation

## 🔗 Related Resources

- [C Programming Language Standard](https://www.iso.org/standard/74528.html)
- [printf(3) Manual Page](https://man7.org/linux/man-pages/man3/printf.3.html)
- [ALX Software Engineering Program](https://www.alxafrica.com/)

## 🙏 Acknowledgments

- ALX Software Engineering Program for the project requirements
- The C standard library developers for the original printf implementation
- Contributors to the project development and testing

---

**Note**: This is an educational implementation designed for learning purposes. For production use, consider using the standard library printf family of functions.
