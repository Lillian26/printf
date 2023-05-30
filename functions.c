#include "main.h"

/**
 * print_char - prints a character
 * @types: a list of arguments
 * @buffer: a buffer array to handle print
 * @flags: calculates the activated flags
 * @width: width
 * @precision: specfication for precision
 * @size: Size specifier
 *
 * Return: number of charactes printed
 */
int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flsgs, width, precision, size));
}

/**
 * handle_write_char - prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags: calculates the active flasg
 * @width: get width
 * @precision: precision specifier given
 * @size: size specifier given
 *
 * Return: number of characters printed
 */
int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = 0;
	char padd = '';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';
	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * print_string - prints a string
 * @types: list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags given
 * @width: get the width
 * @precision: the precision specifier
 * @size: the size specifier
 * Return: number of chars printsed
 */
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char*);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(width);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      "
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, "", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, "", 1);
			return (width);
		}
	}
	return (write(1, str, length));
}

/**
 * print_percent - prints a percent sign
 * @types: list of arguments
 * @buffer: the buffer array to handle input
 * @flags: calculates the active flags
 * @width: get width
 * @precision: precision specifier
 * @size: size specification
 * Return: number of chars printes
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(width);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - prints int
 * @types: list of arguments
 * @buffer: buffr array of handling print
 * @flags: Calculates active flags
 * @width: gets width
 * @precision: precision specifier
 * @size: size specification
 * Return: the number of chars to be printed
 */
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);
	if (n == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /=  10;
	}
	i++;
	return (write_numbers(is_negative, i, buffer,
				flags, width, precision, size));
}

/**
 * print_binary - prints an unsigned number
 * @types: list of argumnets
 * @buffer: buffer array to handle print
 * @flags: calculates the active flags
 * @width: get width
 * @precision: precision specification
 * @size: size specification
 * Return: number of chars printed
 */
int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(width);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;/*2 ^ 31*/
	a[0] = n / m;
	for (i = 1; 1 < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0; sum = 0; count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];
			write(1, &z, 1);
			count++
		}
	}
	return (count);
}
