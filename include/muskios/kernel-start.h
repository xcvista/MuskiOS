
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/cdefs.h>
#include <stdint.h>

__BEGIN_DECLS

extern void kernel_prep(uint32_t, void *);
extern void kernel_start(void) __attribute__((noreturn));
extern void _init(void);
extern void _fini(void);

__END_DECLS

#endif
