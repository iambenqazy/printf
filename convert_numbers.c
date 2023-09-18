#include "main.h"

unsigned int convertSignedInt(va_list args, Buffer * output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convertBinary(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convertUnsignedInt(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convertOctal(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convertSignedInt(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int d, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG_LENGTH)
		d = va_arg(args, long int);
	else
		d = va_arg(args, int);
	if (len == SHORT_LENGTH)
		d = (short)d;
	if (SPACE_FLAG == 1 && d >= 0)
		ret += copy_to_buffer(output, &space, 1);
	if (prec <= 0 && NEG_FLAG == 0)
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += copy_to_buffer(output, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0)
			ret += copy_to_buffer(output, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			ret += copy_to_buffer(output, &pad, 1);
	}
	if (ZERO_FLAG == 0 && d < 0)
		ret += copy_to_buffer(output, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += copy_to_buffer(output, &plus, 1);
	if (!(d == 0 && prec == 0))
		ret += convert_signed_base(output, d, "0123456789",
				flags, 0, prec);
	ret += print_negative_width(output, ret, flags, wid);
	return (ret);
}

unsigned int convertBinary(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned int num;

	num = va_arg(args, unsigned int);

	(void)len;

	return (convert_unsigned_base(output, num, "01", flags, wid, prec));
}

unsigned int convertOctal(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	if (len == LONG_LENGTH)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT_LENGTH)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += copy_to_buffer(output, &zero, 1);

	if (!(num == 0 && prec == 0))
		ret += convert_unsigned_base(output, num, "01234567",
				flags, wid, prec);

	ret += print_negative_width(output, ret, flags, wid);

	return (ret);
}

unsigned int convertUnsignedInt(va_list args, Buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;

	if (len == LONG_LENGTH)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT_LENGTH)
		num = (unsigned short)num;

	if (!(num == 0 && prec == 0))
		ret += convert_unsigned_base(output, num, "0123456789",
				flags, wid, prec);

	ret += print_negative_width(output, ret, flags, wid);

	return (ret);
}
