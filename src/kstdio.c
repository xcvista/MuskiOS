
#include <muskios/kstdio.h>
#include <stdint.h>

int (*kputchar)(int);
int (*kgetchar)(void);

int __kputchar(int c)
{
	return EOF;
}

int __kgetchar(void)
{
	return EOF;
}

void __attribute__((constructor)) kstdio_init(void)
{
	kputchar = __kputchar;
	kgetchar = __kgetchar;
}

int kputs(const char *s)
{
	for (const char *sp = s; *sp; sp++)
		if (kputchar(*sp) == EOF)
			return EOF;
	if (kputchar('\n') == EOF)
		return EOF;
	
	return 0;
}

int kvprintf(const char *f, va_list args)
{
	int agg = 0;
	int mode = 0;
	int limit = 0;
	int length = 0;
	
	for (const char *fp = f; *fp; fp++)
	{
		switch (mode)
		{
			case 0: // Normal mode.
				if (*fp == '%')
				{
					limit = 0;
					length = 0;
					mode = 1;
				}
				else
					kputchar(*fp);
				break;
			
			case 1: // Percentage sign
				switch (*fp)
				{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					{
						limit = limit * 10 + (*fp - '0');
					}
					case 'h':
					case 'H':
					{
						if (length > -2)
							length--;
					}
					case 'l':
					case 'L':
					{
						if (length < 2)
							length++;
					}
					case '%':
					{
						kputchar('%');
						mode = 0;
						agg++;
						break;
					}
					case 's':
					case 'S':
					{
						const char *buf = va_arg(args, const char *);
						for (const char *p = buf; (!limit || (p - buf < limit)) && *p; p++)
							kputchar(*p);
						mode = 0;
						agg++;
						break;
					}
					case 'c':
					case 'C':
					{
						int c = va_arg(args, int);
						kputchar(c);
						mode = 0;
						agg++;
						break;
					}
					case 'd':
					case 'D':
					{
						int64_t d = 0;
						char rbuf[64];
						switch(length)
						{
							case -2:
								d = va_arg(args, signed int);
								break;
							case -1:
								d = va_arg(args, signed int);
								break;
							case 0:
								d = va_arg(args, signed int);
								break;
							case 1:
								d = va_arg(args, signed long);
								break;
							case 2:
								d = va_arg(args, signed long long);
								break;
						}
						
						if (d < 0)
						{
							d = -d;
							kputchar('-');
						}
						
						int idx = 0;
						while (d)
						{
							int i = d % 10;
							rbuf[idx++] = '0' + i;
							d /= 10;
						}
						
						for (--idx; idx > 0; --idx)
							kputchar(rbuf[idx]);
						
						mode = 0;
						agg++;
						break;
					}
					case 'u':
					case 'U':
					{
						uint64_t d = 0;
						char rbuf[64];
						switch(length)
						{
							case -2:
								d = va_arg(args, unsigned int);
								break;
							case -1:
								d = va_arg(args, unsigned int);
								break;
							case 0:
								d = va_arg(args, unsigned int);
								break;
							case 1:
								d = va_arg(args, unsigned long);
								break;
							case 2:
								d = va_arg(args, unsigned long long);
								break;
						}
						
						int idx = 0;
						while (d)
						{
							int i = d % 10;
							rbuf[idx++] = '0' + i;
							d /= 10;
						}
						
						for (--idx; idx > 0; --idx)
							kputchar(rbuf[idx]);
						
						mode = 0;
						agg++;
						break;
					}
					case 'x':
					case 'X':
					{
						uint64_t d = 0;
						char rbuf[64];
						switch(length)
						{
							case -2:
								d = va_arg(args, unsigned int);
								break;
							case -1:
								d = va_arg(args, unsigned int);
								break;
							case 0:
								d = va_arg(args, unsigned int);
								break;
							case 1:
								d = va_arg(args, unsigned long);
								break;
							case 2:
								d = va_arg(args, unsigned long long);
								break;
						}
						
						char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
						int idx = 0;
						while (d)
						{
							int i = d % 10;
							rbuf[idx++] = hex[i];
							d /= 10;
						}
						
						for (--idx; idx > 0; --idx)
							kputchar(rbuf[idx]);
						
						mode = 0;
						agg++;
						break;
					}
				}
				break;
			default:
				mode = 0;
		}
	}
	return agg;
}

int kprintf(const char *f, ...)
{
	va_list args;
	va_start(args, f);
	int rv = kvprintf(f, args);
	va_end(args);
	return rv;
}
