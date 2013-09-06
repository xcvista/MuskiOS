
#include <string.h>

size_t strlen(const char *s)
{
	size_t l = 0;
	
	for (const char *sp = s; *sp; sp++)
		l++;
	
	return l;
}

char *strcpy(char *d, const char *s)
{
	const char *sp;
	char *dp;
	
	for (sp = s, dp = d; *sp; sp++, dp++)
		*dp = *sp;
	*dp = 0;
	
	return d;
}

char *strcat(char *d, const char *s)
{
	const char *sp;
	char *dp;
	
	for (dp = d; *dp; dp++);
	for (sp = s; *sp; sp++, dp++)
		*dp = *sp;
	*dp = 0;
	
	return d;
}

void *memset(void *d, int n, size_t l)
{
	for (char *dp = (char *)d; dp - (char *)d < l; dp++)
		*dp = n;
	
	return d;
}

void *memcpy(void *d, const void *s, size_t l)
{
	const char *sp;
	char *dp;
	
	for (dp = (char *)d, sp = (const char *)s; sp - (const char *)s < l; dp++, sp++)
		*dp = *sp;
	
	return d;
}

void *memmove(void *d, const void *s, size_t l)
{
	const char *sp;
	char *dp;
	int direct = (d > s) ? 1 : -1;
	
	for (dp = (char *)d, sp = (const char *)s; sp - (const char *)s < l * direct; dp += direct, sp += direct)
		*dp = *sp;
	
	return d;
}
