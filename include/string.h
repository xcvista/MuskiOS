
#ifndef _STRING_H_
#define _STRING_H_

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>

__BEGIN_DECLS

// String methods
extern size_t strlen(const char *) __attribute__((nonnull(1)));
extern char *strcpy(char *, const char *) __attribute__((nonnull(1, 2)));
extern char *strcat(char *, const char *) __attribute__((nonnull(1, 2)));

// Memory methods
extern void *memset(void *, int, size_t) __attribute__((nonnull(1)));
extern void *memcpy(void *, const void *, size_t) __attribute__((nonnull(1, 2)));
extern void *memmove(void *, const void *, size_t) __attribute__((nonnull(1, 2)));

__END_DECLS

#endif
