#include "../incs/ft_printf.h"

void	unicode_to_utf8(wchar_t c, char **as)
{
	if (c<(1<<7))
		*(*as)++ = (unsigned char)(c);
	else if (c<(1<<11))
	{
		*(*as)++ = (unsigned char)((c>>6)|0xC0);
		*(*as)++ = (unsigned char)((c&0x3F)|0x80);
	}
	else if (c<(1<<16))
	{
		*(*as)++ = (unsigned char)(((c>>12))|0xE0);
		*(*as)++ =  (unsigned char)(((c>>6)&0x3F)|0x80);
		*(*as)++ =  (unsigned char)((c&0x3F)|0x80);
	}
	else if (c<(1<<21))
	{
		*(*as)++ = (unsigned char)(((c>>18))|0xF0);
		*(*as)++ = (unsigned char)(((c>>12)&0x3F)|0x80);
		*(*as)++ = (unsigned char)(((c>>6)&0x3F)|0x80);
		*(*as)++ = (unsigned char)((c&0x3F)|0x80);
	}
}
